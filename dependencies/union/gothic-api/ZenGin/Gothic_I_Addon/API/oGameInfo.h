﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __OGAME_INFO_H__VER1__
#define __OGAME_INFO_H__VER1__

#include "zGameInfo.h"

namespace Gothic_I_Addon {

  // sizeof 18h
  class oCGameInfo : public zCGameInfo {
  public:
    zOPERATORS_DECLARATION()


    void oCGameInfo_OnInit()                      zCall( 0x00425B90 );
    oCGameInfo() : zCtor( zCGameInfo )            zInit( oCGameInfo_OnInit() );
    virtual ~oCGameInfo()                         zCall( 0x00425D60 );
    virtual void Init()                           zCall( 0x00425D70 );
    virtual void Pack( zCBuffer&, unsigned char ) zCall( 0x00425E30 );
    virtual void Unpack( zCBuffer& )              zCall( 0x00425E50 );

    // user API
    #include "oCGameInfo.inl"
  };

} // namespace Gothic_I_Addon

#endif // __OGAME_INFO_H__VER1__