﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZCOLLISION_DETECTOR_H__VER0__
#define __ZCOLLISION_DETECTOR_H__VER0__

namespace Gothic_I_Classic {
  const int zNUM_COLL_REPORTS = 16;

  // sizeof 34h
  class zCCollisionReport {
  public:
    zOPERATORS_DECLARATION()

    float m_fTimeStamp;                 // sizeof 04h    offset 04h
    zVEC3 m_oContactPoint;              // sizeof 0Ch    offset 08h
    zVEC3 m_oCollNormal0;               // sizeof 0Ch    offset 14h
    zVEC3 m_oCollNormal1;               // sizeof 0Ch    offset 20h
    zCCollisionObject* m_poCollObject0; // sizeof 04h    offset 2Ch
    zCCollisionObject* m_poCollObject1; // sizeof 04h    offset 30h

    void zCCollisionReport_OnInit() zCall( 0x00537FD0 );
    zCCollisionReport()             zInit( zCCollisionReport_OnInit() );
    virtual ~zCCollisionReport()    zCall( 0x00537FF0 );

    // user API
    #include "zCCollisionReport.inl"
  };

  // sizeof 0Ch
  class zCCollisionDetector {
  public:
    zOPERATORS_DECLARATION()


    zTStaticIntersectionTest** m_apStaticTestFuncMatrix;   // sizeof 04h    offset 04h
    zTDynamicIntersectionTest** m_apDynamicTestFuncMatrix; // sizeof 04h    offset 08h

    void zCCollisionDetector_OnInit()                                                                                                                                                                                        zCall( 0x00538060 );
    zCCollisionDetector()                                                                                                                                                                                                    zInit( zCCollisionDetector_OnInit() );
    int __fastcall GetTestFuncIndex( zCCollisionObjectDef*, zCCollisionObjectDef* )                                                                                                                                          zCall( 0x00538160 );
    int( __cdecl* __fastcall GetStaticTestFunc( zCCollisionObjectDef*, zCCollisionObjectDef* ))( float, zCCollisionObject*, zMAT4 const&, zCCollisionObject*, zMAT4 const&, zCCollisionReport** )                            zCall( 0x00538180 );
    int( __cdecl* __fastcall GetDynamicTestFunc( zCCollisionObjectDef*, zCCollisionObjectDef* ))( zCCollisionObject*, zCCollisionObject*, zCCollisionReport** )                                                              zCall( 0x005381A0 );
    void __fastcall DoDynamicIntersectionTests( zCCollisionObject*, zCArray<zCCollisionObject*>&, zCArray<zCCollisionReport*>& )                                                                                             zCall( 0x00538350 );
    void __fastcall DoStaticIntersectionTests( zCCollisionObject*, zCArray<zCCollisionObject*>&, zCArray<zCCollisionReport*>& )                                                                                              zCall( 0x00538500 );
    static void S_ResetFreeCollReportList()                                                                                                                                                                                  zCall( 0x00538260 );
    static zCCollisionReport* S_GetNextFreeCollReport()                                                                                                                                                                      zCall( 0x00538270 );
    virtual ~zCCollisionDetector()                                                                                                                                                                                           zCall( 0x00538130 );
    virtual void __fastcall DetectCollisions( zCCollisionObject*, zCArray<zCCollisionObject*> const&, zCArray<zCCollisionReport*>& )                                                                                         zCall( 0x005388C0 );
    virtual void __fastcall RegisterStaticIntersectionTest( zCCollisionObjectDef*, zCCollisionObjectDef*, int( __cdecl* )( float, zCCollisionObject*, zMAT4 const&, zCCollisionObject*, zMAT4 const&, zCCollisionReport** )) zCall( 0x005381C0 );
    virtual void __fastcall RegisterDynamicIntersectionTest( zCCollisionObjectDef*, zCCollisionObjectDef*, int( __cdecl* )( zCCollisionObject*, zCCollisionObject*, zCCollisionReport** ))                                   zCall( 0x005381F0 );
    virtual int __fastcall CanCollide( zCCollisionObjectDef*, zCCollisionObjectDef* )                                                                                                                                        zCall( 0x00538220 );

    // static properties
    static unsigned long& s_iCollisionDetectorFrameCtr;
    static int& s_iCurrentCollReport;
    static zCCollisionReport*& s_aoCollReportList;

    // user API
    #include "zCCollisionDetector.inl"
  };

} // namespace Gothic_I_Classic

#endif // __ZCOLLISION_DETECTOR_H__VER0__