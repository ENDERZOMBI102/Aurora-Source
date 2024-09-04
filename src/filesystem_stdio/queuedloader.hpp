//
// Created by ENDERZOMBI102 on 03/09/2024.
//
#pragma once
#include "filesystem/IQueuedLoader.h"


class CQueuedLoader : public IQueuedLoader {
public:  // IAppSystem
	bool Connect( CreateInterfaceFn factory ) override;
	void Disconnect() override;

	// Here's where systems can access other interfaces implemented by this object
	// Returns NULL if it doesn't implement the requested interface
	void* QueryInterface( const char* pInterfaceName ) override;

	// Init, shutdown
	InitReturnVal_t Init() override;
	void Shutdown() override;
public:  // IQueuedLoader
	void InstallLoader( ResourcePreload_t type, IResourcePreload * pLoader ) override;
	void InstallProgress( ILoaderProgress * pProgress ) override;

	// Set bOptimizeReload if you want appropriate data (such as static prop lighting)
	// to persist - rather than being purged and reloaded - when going from map A to map A.
	bool BeginMapLoading( const char* pMapName, bool bLoadForHDR, bool bOptimizeMapReload ) override;
	void EndMapLoading( bool bAbort ) override;
	bool AddJob( const LoaderJob_t* pLoaderJob ) override;

	// injects a resource into the map's reslist, rejected if not understood
	void AddMapResource( const char* pFilename ) override;

	// dynamically load a map resource
	void DynamicLoadMapResource( const char* pFilename, DynamicResourceCallback_t pCallback, void* pContext, void* pContext2 ) override;
	void QueueDynamicLoadFunctor( CFunctor * pFunctor ) override;
	bool CompleteDynamicLoad() override;

	// callback is asynchronous
	bool ClaimAnonymousJob( const char* pFilename, QueuedLoaderCallback_t pCallback, void* pContext, void* pContext2 = nullptr ) override;
	// provides data if loaded, caller owns data
	bool ClaimAnonymousJob( const char* pFilename, void** pData, int* pDataSize, LoaderError_t* pError = nullptr ) override;

	bool IsMapLoading() const override;
	bool IsSameMapLoading() const override;
	bool IsFinished() const override;

	// callers can expect that jobs are not immediately started when batching
	bool IsBatching() const override;

	bool IsDynamic() const override;

	// callers can conditionalize operational spew
	int GetSpewDetail() const override;

	void PurgeAll() override;
};
