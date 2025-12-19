//
// Created by ENDERZOMBI102 on 19/12/2025.
//
#include "tier0/mem.h"
#include <iterator>


// Scratch buffer is probably something akin to a stack,
// why else would it not accept a `void*` to the memory being freed?
namespace {
	constexpr uintp BUFFER_SIZE{ 0x100000 };
	uintp s_UsedSize{};
	uint8* s_Buffer{};
	int32 s_Layer{};
	int32 s_AllocStack[128] { };  // should go in the `.bss` section
}

auto MemAllocScratch( const int32 pMemSize ) -> void* {
	// check that we're not overflowing the allocation stack array
	if ( s_Layer == std::size( s_AllocStack ) ) {
		// can't alloc more!
		return nullptr;
	}
	const uintp requiredSize{ s_UsedSize + static_cast<uintp>( pMemSize ) };

	// was the buffer allocated?
	if ( s_Buffer == nullptr ) {
		// nope, allocate it
		const auto ptr{ static_cast<uint8*>( malloc( BUFFER_SIZE ) ) };
		if ( ptr == nullptr ) {
			// out of memory... what a bummer!
			return nullptr;
		}
		s_Buffer = ptr;
	} else if ( BUFFER_SIZE < requiredSize ) {  // check we're not overflowing the buffer
		// out of buffer space... what a bummer!
		return nullptr;
	}

	uint8* const res{ &s_Buffer[ s_UsedSize ] };

	// lets save the allocation size
	s_UsedSize += pMemSize;
	s_AllocStack[s_Layer] = pMemSize;
	s_Layer += 1;

	return res;
}
void MemFreeScratch() {
	// let us avoid underflowing the stack
	if ( s_Layer == 0 ) {
		return;
	}

	s_Layer -= 1;
	const int32 size{ s_AllocStack[s_Layer] };
	s_UsedSize -= size;
}

#if IsLinux()
	void ZeroMemory( void* pMem, const size_t pLength ) {  // why is this a function, memset exists??
		memset( pMem, 0, pLength );
	}
#endif

