﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZMEMORY__BASE_H__VER0__
#define __ZMEMORY__BASE_H__VER0__

namespace Gothic_I_Classic {

  enum zTMallocDumpHeapMode {
    zMALLOC_SORT_BY_BYTES_PER_LINE,
    zMALLOC_SORT_BY_BLOCKS_PER_LINE,
    zMALLOC_SORT_BY_CLASS,
    zMALLOC_SORT_BY_BLOCK_SIZE,
    zMALLOC_SORT_BY_FILE,
    zMALLOC_SORT_BY_TIME
  };

  enum zTMallocCheckPtrError {
    zMALLOC_CHECK_PTR_OK,
    zMALLOC_CHECK_PTR_INVALID_PTR,
    zMALLOC_CHECK_PTR_CORRUPTED_MEM,
    zMALLOC_CHECK_PTR_NOT_ACTIVATED,
    zMALLOC_CHECK_PTR_NULL_PTR
  };

  // sizeof 28h
  struct zTMallocStats {
    zOPERATORS_DECLARATION()

    int numBlocks;                  // sizeof 04h    offset 00h
    int numBlocksPeak;              // sizeof 04h    offset 04h
    int numBytesAllocated;          // sizeof 04h    offset 08h
    int numBytesAllocatedPeak;      // sizeof 04h    offset 0Ch
    int numAllocs;                  // sizeof 04h    offset 10h
    int numFrees;                   // sizeof 04h    offset 14h
    __int64 numBytesAllocatedTotal; // sizeof 08h    offset 18h
    __int64 numBytesFreedTotal;     // sizeof 08h    offset 20h

    zTMallocStats() {}

    // user API
    #include "zTMallocStats.inl"
  };

  // sizeof 0Ch
  struct zTMallocProcessStats {
    zOPERATORS_DECLARATION()

    unsigned long fixedMem; // sizeof 04h    offset 00h
    unsigned long freeMem;  // sizeof 04h    offset 04h
    unsigned long moveable; // sizeof 04h    offset 08h

    zTMallocProcessStats() {}

    // user API
    #include "zTMallocProcessStats.inl"
  };

  // sizeof 04h
  class zCMalloc {
  public:
    zOPERATORS_DECLARATION()


    zDefineInheritableCtor( zCMalloc ) {}
    zCMalloc() {}
    virtual ~zCMalloc()                                                 zCall( 0x0054EB50 );
    virtual void* Malloc( unsigned int )                                zPureCall;
    virtual void* Malloc( unsigned int, char const*, char const*, int ) zPureCall;
    virtual void* Realloc( void*, unsigned int )                        zPureCall;
    virtual void Free( void* )                                          zPureCall;
    virtual int GetStats( zTMallocStats& )                              zCall( 0x0054EB00 );
    virtual int GetProcessStats( zTMallocProcessStats& )                zCall( 0x0054EB10 );
    virtual int DumpHeap( zTMallocDumpHeapMode )                        zCall( 0x0054EB20 );
    virtual int CheckHeap()                                             zCall( 0x0054EB30 );
    virtual zTMallocCheckPtrError CheckPtr( void* )                     zCall( 0x0054EB40 );
    virtual int Init( int )                                             zPureCall;
    virtual int Shutdown()                                              zPureCall;

    // user API
    #include "zCMalloc.inl"
  };

} // namespace Gothic_I_Classic

#endif // __ZMEMORY__BASE_H__VER0__