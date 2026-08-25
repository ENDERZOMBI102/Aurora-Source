//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#if defined( PLATFORM_WINDOWS )
	#include <sysinfoapi.h>
	#include <memoryapi.h>
	#define VA_COMMIT_FLAGS MEM_COMMIT
	#define VA_RESERVE_FLAGS MEM_RESERVE
#endif

#include "tier1/memstack.h"
#include "tier0/dbg.h"
#include "tier0/memdbgon.h"
#include "tier1/utlmap.h"

#if IsWindows()
	#pragma warning( disable : 4073 )
	#pragma init_seg( lib )
#endif


//-----------------------------------------------------------------------------

MEMALLOC_DEFINE_EXTERNAL_TRACKING( CMemoryStack );

//-----------------------------------------------------------------------------

CMemoryStack::CMemoryStack() = default;

//-------------------------------------

CMemoryStack::~CMemoryStack() {
	if ( m_pBase ) {
		Term();
	}
}

//-------------------------------------

bool CMemoryStack::Init( uint32 maxSize, uint32 commitSize, uint32 initialCommit, uint32 alignment ) {
	Assert( not m_pBase );

	m_maxSize = maxSize;
	m_alignment = AlignValue( alignment, 4 );

	Assert( m_alignment == alignment );
	Assert( m_maxSize > 0 );

	#if IsWindows()
		if ( commitSize != 0 ) {
			m_commitSize = commitSize;
		}

		SYSTEM_INFO sysInfo;
		GetSystemInfo( &sysInfo );
		Assert( not ( sysInfo.dwPageSize & (sysInfo.dwPageSize - 1) ) );
		uint32 pageSize = sysInfo.dwPageSize;

		if ( m_commitSize == 0 ) {
			m_commitSize = pageSize;
		} else {
			m_commitSize = AlignValue( m_commitSize, pageSize );
		}

		m_maxSize = AlignValue( m_maxSize, m_commitSize );

		Assert( m_maxSize % pageSize == 0 and m_commitSize % pageSize == 0 and m_commitSize <= m_maxSize );

		m_pBase = static_cast<byte*>( VirtualAlloc( nullptr, m_maxSize, VA_RESERVE_FLAGS, PAGE_NOACCESS ) );
		Assert( m_pBase );
		m_pCommitLimit = m_pNextAlloc = m_pBase;

		if ( initialCommit ) {
			initialCommit = AlignValue( initialCommit, m_commitSize );
			Assert( initialCommit < m_maxSize );
			if ( not VirtualAlloc( m_pCommitLimit, initialCommit, VA_COMMIT_FLAGS, PAGE_READWRITE ) ) {
				return false;
			}
			m_minCommit = initialCommit;
			m_pCommitLimit += initialCommit;
			MemAlloc_RegisterExternalAllocation( CMemoryStack, GetBase(), GetSize() );
		}
	#else
		m_pBase = static_cast<byte*>( MemAlloc_AllocAligned( m_maxSize, alignment ? alignment : 1 ) );
		m_pNextAlloc = m_pBase;
		m_pCommitLimit = m_pBase + m_maxSize;
	#endif

	m_pAllocLimit = m_pBase + m_maxSize;

	return m_pBase != nullptr;
}

//-------------------------------------

void CMemoryStack::Term() {
	FreeAll();
	if ( m_pBase ) {
		#if IsWindows()
			VirtualFree( m_pBase, 0, MEM_RELEASE );
		#else
			MemAlloc_FreeAligned( m_pBase );
		#endif
		m_pBase = nullptr;
	}
}

//-------------------------------------

int CMemoryStack::GetSize() {
	#if IsWindows()
		return m_pCommitLimit - m_pBase;
	#else
		return m_maxSize;
	#endif
}


//-------------------------------------

bool CMemoryStack::CommitTo( byte* pNextAlloc ) RESTRICT {
	#if IsWindows()
		byte* pNewCommitLimit = AlignValue( pNextAlloc, m_commitSize );
		const uint32 commitSize = pNewCommitLimit - m_pCommitLimit;

		if ( GetSize() ) {
			MemAlloc_RegisterExternalDeallocation( CMemoryStack, GetBase(), GetSize() );
		}

		if ( m_pCommitLimit + commitSize > m_pAllocLimit ) {
			return false;
		}

		if ( not VirtualAlloc( m_pCommitLimit, commitSize, VA_COMMIT_FLAGS, PAGE_READWRITE ) ) {
			Assert( 0 );
			return false;
		}
		m_pCommitLimit = pNewCommitLimit;

		if ( GetSize() ) {
			MemAlloc_RegisterExternalAllocation( CMemoryStack, GetBase(), GetSize() );
		}
		return true;
	#else
		Assert( 0 );
		return false;
	#endif
}

//-------------------------------------

void CMemoryStack::FreeToAllocPoint( MemoryStackMark_t mark, bool bDecommit ) {
	void* pAllocPoint = m_pBase + mark;
	Assert( pAllocPoint >= m_pBase and pAllocPoint <= m_pNextAlloc );

	if ( pAllocPoint >= m_pBase and pAllocPoint < m_pNextAlloc ) {
		if ( bDecommit ) {
			#if IsWindows()
				byte* pDecommitPoint = AlignValue( static_cast<byte*>( pAllocPoint ), m_commitSize );

				if ( pDecommitPoint < m_pBase + m_minCommit ) {
					pDecommitPoint = m_pBase + m_minCommit;
				}

				const uint32 decommitSize = m_pCommitLimit - pDecommitPoint;

				if ( decommitSize > 0 ) {
					MemAlloc_RegisterExternalDeallocation( CMemoryStack, GetBase(), GetSize() );

					VirtualFree( pDecommitPoint, decommitSize, MEM_DECOMMIT );
					m_pCommitLimit = pDecommitPoint;

					if ( mark > 0 ) {
						MemAlloc_RegisterExternalAllocation( CMemoryStack, GetBase(), GetSize() );
					}
				}
			#endif
		}
		m_pNextAlloc = static_cast<byte*>( pAllocPoint );
	}
}

//-------------------------------------

void CMemoryStack::FreeAll( bool bDecommit ) {
	if ( m_pBase and m_pCommitLimit - m_pBase > 0 ) {
		if ( bDecommit ) {
			#if IsWindows()
				MemAlloc_RegisterExternalDeallocation( CMemoryStack, GetBase(), GetSize() );

				VirtualFree( m_pBase, m_pCommitLimit - m_pBase, MEM_DECOMMIT );
				m_pCommitLimit = m_pBase;
			#endif
		}
		m_pNextAlloc = m_pBase;
	}
}

//-------------------------------------

void CMemoryStack::Access( void** ppRegion, uint32* pBytes ) {
	*ppRegion = m_pBase;
	*pBytes = m_pNextAlloc - m_pBase;
}

//-------------------------------------

void CMemoryStack::PrintContents() {
	Msg( "Total used memory:      %d\n", GetUsed() );
	Msg( "Total committed memory: %d\n", GetSize() );
}

//-----------------------------------------------------------------------------
