//
// Created by ENDERZOMBI102 on 28/03/2024.
//
#pragma once
#include "tier0/dbg.h"
#include "tier1/utlvector.h"
#include "vstdlib/jobthread.h"


class CThreadPool : public CRefCounted1<IThreadPool> {
public:
	CThreadPool();
	~CThreadPool() override;
public:  // IThreadPool
	// Thread functions
	auto Start( const ThreadPoolStartParams_t& startParams = ThreadPoolStartParams_t{} ) -> bool override;
	auto Stop( int timeout = TT_INFINITE ) -> bool override;

	// Functions for any thread
	auto GetJobCount() -> unsigned override;
	auto NumThreads() -> int override;
	auto NumIdleThreads() -> int override;

	/**
	 * Pauses the execution/processing of jobs.
	 */
	auto SuspendExecution() -> int override;
	/**
	 * Resumes the execution/processing of jobs.
	 */
	auto ResumeExecution() -> int override;

	// Offer the current thread to the pool
	auto YieldWait( CThreadEvent** pEvents, int nEvents, bool bWaitAll = true, unsigned timeout = TT_INFINITE ) -> int override;
	auto YieldWait( CJob**, int nJobs, bool bWaitAll = true, unsigned timeout = TT_INFINITE ) -> int override;
	auto Yield( unsigned timeout ) -> void override;

	// Add a native job to the queue (master thread)
	auto AddJob( CJob* ) -> void override;

	// All threads execute pFunctor asap. Thread will either wake up
	//  and execute or execute pFunctor right after completing current job and
	//  before looking for another job.
	auto ExecuteHighPriorityFunctor( CFunctor* pFunctor ) -> void override;

	// Change the priority of an active job
	auto ChangePriority( CJob* p, JobPriority_t priority ) -> void override;

	// Bulk job manipulation (blocking)
	auto ExecuteToPriority( JobPriority_t toPriority, JobFilter_t pfnFilter = nullptr ) -> int override;
	auto AbortAll() -> int override;

	//-----------------------------------------------------
	auto Reserved1() -> void override { }
private:
	auto AddFunctorInternal( CFunctor*, CJob** = nullptr, const char* pszDescription = nullptr, unsigned flags = 0 ) -> void override;

	// Services for internal use by job instances
	friend class CJob;

	auto GetDummyJob() -> CJob* override;
public:
	auto Distribute( bool bDistribute = true, int* pAffinityTable = nullptr ) -> void override;

	auto Start( const ThreadPoolStartParams_t& startParams, const char* pszNameOverride ) -> bool override;
private:
	static auto PoolThreadFunc( void* pParam ) -> uint32;
private:
	enum State : intp {
		EXECUTING = 0,
		SUSPENDED
	};
	CInterlockedIntT<State> m_State{};

	CThread* m_CoordinatorThread{ nullptr };
	CThreadEvent m_JobAvailable{};
	CThreadEvent m_JobAccepted{};
	CThreadEvent m_Exit{ true };
	CInterlockedInt m_IdleCount{};

	CUtlLinkedList<CJob*> m_Queue{};
	// mutex for adding/removing items to/from the queue
	CThreadMutex m_Mutex{};
	CUtlVector<ThreadHandle_t> m_Threads{};
};

JOB_INTERFACE auto CreateThreadPool() -> IThreadPool*;
JOB_INTERFACE auto DestroyThreadPool( IThreadPool* pPool ) -> void;
JOB_INTERFACE auto RunThreadPoolTests() -> void;
JOB_INTERFACE IThreadPool* g_pThreadPool;
