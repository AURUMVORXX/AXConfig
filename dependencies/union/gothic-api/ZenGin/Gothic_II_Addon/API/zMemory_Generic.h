﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZMEMORY__GENERIC_H__VER3__
#define __ZMEMORY__GENERIC_H__VER3__

#include "zMemory_Base.h"

namespace Gothic_II_Addon {

  // sizeof 04h
  class zCMallocGeneric : public zCMalloc {
  public:
    zOPERATORS_DECLARATION()


    void zCMallocGeneric_OnInit()                                       zCall( 0x00565F20 );
    zCMallocGeneric() : zCtor( zCMalloc )                               zInit( zCMallocGeneric_OnInit() );
    virtual ~zCMallocGeneric()                                          zCall( 0x00565EA0 );
    virtual void* Malloc( unsigned int )                                zCall( 0x00565FD0 );
    virtual void* Malloc( unsigned int, char const*, char const*, int ) zCall( 0x00565FE0 );
    virtual void* Realloc( void*, unsigned int )                        zCall( 0x00565FF0 );
    virtual void Free( void* )                                          zCall( 0x00566010 );
    virtual int GetStats( zTMallocStats& )                              zCall( 0x00566020 );
    virtual int Init( int )                                             zCall( 0x00566040 );
    virtual int Shutdown()                                              zCall( 0x00566050 );

    // user API
    #include "zCMallocGeneric.inl"
  };

} // namespace Gothic_II_Addon

#endif // __ZMEMORY__GENERIC_H__VER3__