﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZTEX_CONVERT_H__VER0__
#define __ZTEX_CONVERT_H__VER0__

#include "zRenderer.h"
#include "z3d.h"

namespace Gothic_I_Classic {

  // sizeof 04h
  struct RGBPIXEL {
  public:
    zOPERATORS_DECLARATION()

    unsigned char b; // sizeof 01h    offset 00h
    unsigned char g; // sizeof 01h    offset 01h
    unsigned char r; // sizeof 01h    offset 02h
    unsigned char a; // sizeof 01h    offset 03h
  };

  // sizeof 33Ch
  class zCTexConGeneric : public zCTextureConvert {
  public:
    zOPERATORS_DECLARATION()

    zCTextureInfo texinfo;            // sizeof 1Ch    offset 04h
    char* tempptr;                    // sizeof 04h    offset 20h
    char pal[256* 3];                 // sizeof 300h   offset 24h
    zCTextureFileFormatInternal* ffi; // sizeof 04h    offset 324h
    int alpha;                        // sizeof 04h    offset 328h
    zCOLOR average;                   // sizeof 04h    offset 32Ch
    zTTexLockMode lockMode;           // sizeof 04h    offset 330h
    int modified;                     // sizeof 04h    offset 334h
    int detailTextureMode;            // sizeof 04h    offset 338h

    void zCTexConGeneric_OnInit()                            zCall( 0x00722B70 );
    zCOLOR GetAverageColor()                                 zCall( 0x00722B10 );
    zCTexConGeneric() : zCtor( zCTextureConvert )            zInit( zCTexConGeneric_OnInit() );
    virtual ~zCTexConGeneric()                               zCall( 0x00722C00 );
    virtual int Lock( int )                                  zCall( 0x00722C70 );
    virtual int Unlock()                                     zCall( 0x00722C90 );
    virtual int SetTextureInfo( zCTextureInfo const& )       zCall( 0x007225E0 );
    virtual void* GetPaletteBuffer()                         zCall( 0x007226C0 );
    virtual int GetTextureBuffer( int, void*&, int& )        zCall( 0x007226E0 );
    virtual zCTextureInfo GetTextureInfo()                   zCall( 0x007226A0 );
    virtual int CopyPaletteDataTo( void* )                   zCall( 0x00722AE0 );
    virtual int CopyTextureDataTo( int, void*, int )         zCall( 0x007228B0 );
    virtual int HasAlpha()                                   zCall( 0x00722B20 );
    virtual int ConvertTextureFormat( zCTextureInfo const& ) zCall( 0x00720DC0 );
    virtual void SetDetailTextureMode( int )                 zCall( 0x00722BD0 );

    // user API
    #include "zCTexConGeneric.inl"
  };

} // namespace Gothic_I_Classic

#endif // __ZTEX_CONVERT_H__VER0__