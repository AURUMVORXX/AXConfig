﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZNET_SESSION_H__VER0__
#define __ZNET_SESSION_H__VER0__

#include "zNetHost.h"

namespace Gothic_I_Classic {

  // sizeof 2Ch
  class zCNetSession {
  public:
    zOPERATORS_DECLARATION()

    unsigned short protocol;          // sizeof 02h    offset 04h
    zTNetAddress listenPacketAddress; // sizeof 10h    offset 08h
    zTNetAddress listenStreamAddress; // sizeof 10h    offset 18h
    int valid;                        // sizeof 04h    offset 28h

    zCNetSession() {}
    void zCNetSession_OnInit( unsigned short ) zCall( 0x00457FE0 );
    zCNetSession( unsigned short a0 )          zInit( zCNetSession_OnInit( a0 ));
    void Reset()                               zCall( 0x00458080 );
    virtual ~zCNetSession()                    zCall( 0x004580A0 );

    // user API
    #include "zCNetSession.inl"
  };

} // namespace Gothic_I_Classic

#endif // __ZNET_SESSION_H__VER0__