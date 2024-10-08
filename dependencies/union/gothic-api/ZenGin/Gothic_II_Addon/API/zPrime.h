﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZPRIME_H__VER3__
#define __ZPRIME_H__VER3__

namespace Gothic_II_Addon {

  // sizeof 01h
  class zCPrime {
  public:
    zOPERATORS_DECLARATION()


    zCPrime() {}
    static int IsPrime( unsigned long )             zCall( 0x005BFBB0 );
    static unsigned short PrimeNo( unsigned short ) zCall( 0x005BFC80 );
    static unsigned long NextPrime( unsigned long ) zCall( 0x005BFD90 );

    // user API
    #include "zCPrime.inl"
  };

} // namespace Gothic_II_Addon

#endif // __ZPRIME_H__VER3__