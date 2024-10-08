﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZSKY_H__VER3__
#define __ZSKY_H__VER3__

#include "zParticle.h"
#include "zSky_Outdoor.h"

namespace Gothic_II_Addon {

  enum zTWeather {
    zTWEATHER_SNOW,
    zTWEATHER_RAIN
  };

  // sizeof C4h
  class zCUnderwaterPFX : public zCParticleFX {
  public:
    zOPERATORS_DECLARATION()

    zVEC3 camPosLastFrame; // sizeof 0Ch    offset B8h

    zCUnderwaterPFX() : zCtor( zCParticleFX ) {}
    void ProcessParticles()                zCall( 0x005E08F0 );
    void CreateParticles()                 zCall( 0x005E0CF0 );
    virtual ~zCUnderwaterPFX()             zCall( 0x005DFF10 );
    virtual int Render( zTRenderContext& ) zCall( 0x005E08D0 );

    // user API
    #include "zCUnderwaterPFX.inl"
  };

  // sizeof 4Ch
  class zCSkyControler : public zCObject {
  public:
    zCLASS_DECLARATION( zCSkyControler )

    enum zTCamLocationHint {
      zCAM_OUTSIDE_SECTOR,
      zCAM_INSIDE_SECTOR_CANT_SEE_OUTSIDE,
      zCAM_INSIDE_SECTOR_CAN_SEE_OUTSIDE
    };

    zCOLOR* polyLightCLUTPtr;     // sizeof 04h    offset 24h
    float cloudShadowScale;       // sizeof 04h    offset 28h
    int m_bColorChanged;          // sizeof 04h    offset 2Ch
    zTWeather m_enuWeather;       // sizeof 04h    offset 30h
    zCOLOR backgroundColor;       // sizeof 04h    offset 34h
    int fillBackground;           // sizeof 04h    offset 38h
    zCTexture* backgroundTexture; // sizeof 04h    offset 3Ch
    int relightCtr;               // sizeof 04h    offset 40h
    float lastRelightTime;        // sizeof 04h    offset 44h
    float m_fRelightTime;         // sizeof 04h    offset 48h

    zDefineInheritableCtor( zCSkyControler ) : zCtor( zCObject ) {}
    void zCSkyControler_OnInit()                            zCall( 0x005DF6B0 );
    zCSkyControler() : zCtor( zCObject )                    zInit( zCSkyControler_OnInit() );
    void ClearBackground( zCOLOR )                          zCall( 0x005DF930 );
    virtual zCClassDef* _GetClassDef() const                zCall( 0x005DF6A0 );
    virtual ~zCSkyControler()                               zCall( 0x005DF8C0 );
    virtual void SetTime( float )                           zPureCall;
    virtual float GetTime() const                           zPureCall;
    virtual void ResetTime()                                zPureCall;
    virtual void SetFarZ( float )                           zPureCall;
    virtual float GetFarZ() const                           zPureCall;
    virtual void SetFarZScalability( float )                zPureCall;
    virtual float GetFarZScalability() const                zPureCall;
    virtual void SetBackgroundColor( zCOLOR )               zPureCall;
    virtual zCOLOR GetBackgroundColor() const               zPureCall;
    virtual zCOLOR GetBackgroundColorDef() const            zPureCall;
    virtual void SetOverrideColor( zVEC3 )                  zPureCall;
    virtual void SetOverrideColorFlag( int )                zPureCall;
    virtual float GetCloudShadowScale() const               zCall( 0x005DF420 );
    virtual void SetCloudShadowScale( float )               zCall( 0x005DF430 );
    virtual void SetFillBackground( int )                   zCall( 0x005DF440 );
    virtual int GetFillBackground() const                   zCall( 0x005DF450 );
    virtual void SetUnderwaterFX( int )                     zPureCall;
    virtual int GetUnderwaterFX() const                     zPureCall;
    virtual void UpdateWorldDependencies()                  zPureCall;
    virtual void SetLightDirty()                            zCall( 0x005DF460 );
    virtual void SetRelightTime( float )                    zCall( 0x005DF470 );
    virtual int GetRelightCtr()                             zCall( 0x005DF480 );
    virtual zCOLOR GetDaylightColorFromIntensity( int )     zCall( 0x005DF490 );
    virtual void RenderSkyPre()                             zPureCall;
    virtual void RenderSkyPost( int )                       zPureCall;
    virtual int GetGlobalWindVec( zVEC3&, zTAnimationMode ) zCall( 0x005DF4B0 );
    virtual void SetGlobalSkyScale( float )                 zCall( 0x005DF4C0 );
    virtual float GetGlobalSkyScale() const                 zCall( 0x005DF4D0 );
    virtual int GetGlobalSkyScaleChanged() const            zCall( 0x005DF4E0 );
    virtual void SetCameraLocationHint( zTCamLocationHint ) zCall( 0x005DF4F0 );
    virtual void SetWeatherType( zTWeather )                zCall( 0x005DF500 );
    virtual zTWeather GetWeatherType() const                zCall( 0x005DF510 );

    // static properties
    static zCSkyControler*& s_activeSkyControler;
    static int& s_skyEffectsEnabled;

    // user API
    #include "zCSkyControler.inl"
  };

  // sizeof 7Ch
  class zCSkyControler_Mid : public zCSkyControler {
  public:
    zCLASS_DECLARATION( zCSkyControler_Mid )

    int underwaterFX;                      // sizeof 04h    offset 4Ch
    zCOLOR underwaterColor;                // sizeof 04h    offset 50h
    float underwaterFarZ;                  // sizeof 04h    offset 54h
    float underwaterStartTime;             // sizeof 04h    offset 58h
    float oldFovX;                         // sizeof 04h    offset 5Ch
    float oldFovY;                         // sizeof 04h    offset 60h
    zCVob* vobUnderwaterPFX;               // sizeof 04h    offset 64h
    zCPolygon* scrPoly;                    // sizeof 04h    offset 68h
    zCMesh* scrPolyMesh;                   // sizeof 04h    offset 6Ch
    int scrPolyAlpha;                      // sizeof 04h    offset 70h
    zCOLOR scrPolyColor;                   // sizeof 04h    offset 74h
    zTRnd_AlphaBlendFunc scrPolyAlphaFunc; // sizeof 04h    offset 78h

    zDefineInheritableCtor( zCSkyControler_Mid ) : zCtor( zCSkyControler ) {}
    void zCSkyControler_Mid_OnInit()                     zCall( 0x005DFBF0 );
    zCSkyControler_Mid() : zCtor( zCSkyControler )       zInit( zCSkyControler_Mid_OnInit() );
    void InitUnderwaterPFX()                             zCall( 0x005DFC90 );
    void InitScreenBlend()                               zCall( 0x005E0310 );
    void RenderScreenBlend()                             zCall( 0x005E0430 );
    void SetScreenBlendAlpha( int )                      zCall( 0x005E05F0 );
    void SetScreenBlendColor( zCOLOR const& )            zCall( 0x005E0610 );
    void SetScreenBlendAlphaFunc( zTRnd_AlphaBlendFunc ) zCall( 0x005E0620 );
    virtual zCClassDef* _GetClassDef() const             zCall( 0x005DF520 );
    virtual ~zCSkyControler_Mid()                        zCall( 0x005DFF20 );
    virtual void SetTime( float )                        zPureCall;
    virtual float GetTime() const                        zPureCall;
    virtual void ResetTime()                             zPureCall;
    virtual void SetFarZ( float )                        zPureCall;
    virtual float GetFarZ() const                        zPureCall;
    virtual void SetFarZScalability( float )             zPureCall;
    virtual float GetFarZScalability() const             zPureCall;
    virtual void SetBackgroundColor( zCOLOR )            zPureCall;
    virtual zCOLOR GetBackgroundColor() const            zPureCall;
    virtual zCOLOR GetBackgroundColorDef() const         zPureCall;
    virtual void SetOverrideColor( zVEC3 )               zPureCall;
    virtual void SetOverrideColorFlag( int )             zPureCall;
    virtual void SetUnderwaterFX( int )                  zCall( 0x005DFFE0 );
    virtual int GetUnderwaterFX() const                  zCall( 0x005E0050 );
    virtual void UpdateWorldDependencies()               zPureCall;
    virtual void RenderSkyPre()                          zCall( 0x005E0060 );
    virtual void RenderSkyPost( int )                    zCall( 0x005E0130 );

    // user API
    #include "zCSkyControler_Mid.inl"
  };

  // sizeof 88h
  class zCSkyControler_Indoor : public zCSkyControler_Mid {
  public:
    zCLASS_DECLARATION( zCSkyControler_Indoor )

    float userFarZ;            // sizeof 04h    offset 7Ch
    float userFarZScalability; // sizeof 04h    offset 80h
    float time;                // sizeof 04h    offset 84h

    void zCSkyControler_Indoor_OnInit()                   zCall( 0x005E0630 );
    zCSkyControler_Indoor() : zCtor( zCSkyControler_Mid ) zInit( zCSkyControler_Indoor_OnInit() );
    static zCObject* _CreateNewInstance()                 zCall( 0x005DF340 );
    virtual zCClassDef* _GetClassDef() const              zCall( 0x005DF550 );
    virtual ~zCSkyControler_Indoor()                      zCall( 0x005DF5E0 );
    virtual void SetTime( float )                         zCall( 0x005E06D0 );
    virtual float GetTime() const                         zCall( 0x005DF560 );
    virtual void ResetTime()                              zCall( 0x005DF570 );
    virtual void SetFarZ( float )                         zCall( 0x005E0770 );
    virtual float GetFarZ() const                         zCall( 0x005E0780 );
    virtual void SetFarZScalability( float )              zCall( 0x005E0790 );
    virtual float GetFarZScalability() const              zCall( 0x005E07E0 );
    virtual void SetBackgroundColor( zCOLOR )             zCall( 0x005E07F0 );
    virtual zCOLOR GetBackgroundColor() const             zCall( 0x005E0800 );
    virtual zCOLOR GetBackgroundColorDef() const          zCall( 0x005E0810 );
    virtual void SetOverrideColor( zVEC3 )                zCall( 0x005DF580 );
    virtual void SetOverrideColorFlag( int )              zCall( 0x005DF590 );
    virtual void UpdateWorldDependencies()                zCall( 0x005DF5A0 );
    virtual void RenderSkyPre()                           zCall( 0x005E0820 );
    virtual void RenderSkyPost( int )                     zCall( 0x005E08C0 );

    // user API
    #include "zCSkyControler_Indoor.inl"
  };

} // namespace Gothic_II_Addon

#endif // __ZSKY_H__VER3__