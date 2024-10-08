﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZMEMORY__WIN32_H__VER2__
#define __ZMEMORY__WIN32_H__VER2__

namespace Gothic_II_Classic {

  // sizeof 4D0h
  class zCMallocWin32Debug : public zCMalloc {
  public:
    zOPERATORS_DECLARATION()

    unsigned int RuntimeLine;          // sizeof 04h    offset 04h
    unsigned int RuntimeMemSize;       // sizeof 04h    offset 08h
    unsigned int RuntimeBlocks;        // sizeof 04h    offset 0Ch
    unsigned int RuntimeResultBlock;   // sizeof 04h    offset 10h
    unsigned int RuntimeResultMemSize; // sizeof 04h    offset 14h
    char RuntimeFilename[400];         // sizeof 190h   offset 18h
    char RuntimeName[400];             // sizeof 190h   offset 1A8h
    char Buffer[400];                  // sizeof 190h   offset 338h
    int ShowNoFilename;                // sizeof 04h    offset 4C8h
    int ShowNoName;                    // sizeof 04h    offset 4CCh

    zCMallocWin32Debug() : zCtor( zCMalloc ) {}

    // user API
    #include "zCMallocWin32Debug.inl"
  };

} // namespace Gothic_II_Classic

#endif // __ZMEMORY__WIN32_H__VER2__