﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __OVIEW_PROGRESSBAR_H__VER3__
#define __OVIEW_PROGRESSBAR_H__VER3__

#include "zViewProgressbar.h"

namespace Gothic_II_Addon {

  // sizeof 138h
  class oCViewGothicProgressBar : public zCViewProgressBar {
  public:
    zOPERATORS_DECLARATION()

    int progressbar_sizex; // sizeof 04h    offset 130h

    oCViewGothicProgressBar() : zCtor( zCViewProgressBar ) {}
    /* for zCViewBase num : 15*/
    virtual ~oCViewGothicProgressBar() zCall( 0x006C2610 );
    virtual void Init()                zCall( 0x0043D2B0 );
    virtual void HandleChange()        zCall( 0x0043D2F0 );
    /* for zCInputCallback num : 1*/

    // user API
    #include "oCViewGothicProgressBar.inl"
  };

} // namespace Gothic_II_Addon

#endif // __OVIEW_PROGRESSBAR_H__VER3__