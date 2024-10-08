﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZVOB_IDENTIFIER_H__VER3__
#define __ZVOB_IDENTIFIER_H__VER3__

namespace Gothic_II_Addon {
  const unsigned long zVOB_ID_UNDEFINED = 0;

  // sizeof 04h
  class zCVobIdentifier {
  public:
    zOPERATORS_DECLARATION()

    unsigned long id; // sizeof 04h    offset 00h

    zCVobIdentifier() {}

    // user API
    #include "zCVobIdentifier.inl"
  };

} // namespace Gothic_II_Addon

#endif // __ZVOB_IDENTIFIER_H__VER3__