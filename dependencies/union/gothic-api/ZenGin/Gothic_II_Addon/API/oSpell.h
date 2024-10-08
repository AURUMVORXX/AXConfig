﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __OSPELL_H__VER3__
#define __OSPELL_H__VER3__

namespace Gothic_II_Addon {
  const int SPL_PALLIGHT             = 0;
  const int SPL_PALLIGHTHEAL         = 1;
  const int SPL_PALHOLYBOLT          = 2;
  const int SPL_PALMEDIUMHEAL        = 3;
  const int SPL_PALREPELEVIL         = 4;
  const int SPL_PALFULLHEAL          = 5;
  const int SPL_PALDESTROYEVIL       = 6;
  const int SPL_PALTELEPORTSECRET    = 7;
  const int SPL_TELEPORTSEAPORT      = 8;
  const int SPL_TELEPORTMONASTERY    = 9;
  const int SPL_TELEPORTFARM         = 10;
  const int SPL_TELEPORTXARDAS       = 11;
  const int SPL_TELEPORTPASSNW       = 12;
  const int SPL_TELEPORTPASSOW       = 13;
  const int SPL_TELEPORTOC           = 14;
  const int SPL_TELEPORT_1           = 15;
  const int SPL_TELEPORT_2           = 16;
  const int SPL_TELEPORT_3           = 17;
  const int SPL_LIGHT                = 18;
  const int SPL_FIREBOLT             = 19;
  const int SPL_ICEBOLT              = 20;
  const int SPL_LIGHTHEAL            = 21;
  const int SPL_SUMMONGOBLINSKELETON = 22;
  const int SPL_INSTANTFIREBALL      = 23;
  const int SPL_ZAP                  = 24;
  const int SPL_SUMMONWOLF           = 25;
  const int SPL_WINDFIST             = 26;
  const int SPL_SLEEP                = 27;
  const int SPL_MEDIUMHEAL           = 28;
  const int SPL_LIGHTNINGFLASH       = 29;
  const int SPL_CHARGEFIREBALL       = 30;
  const int SPL_SUMMONSKELETON       = 31;
  const int SPL_FEAR                 = 32;
  const int SPL_ICECUBE              = 33;
  const int SPL_THUNDERBALL          = 34;
  const int SPL_SUMMONGOLEM          = 35;
  const int SPL_DESTROYUNDEAD        = 36;
  const int SPL_PYROKINESIS          = 37;
  const int SPL_FIRESTORM            = 38;
  const int SPL_ICEWAVE              = 39;
  const int SPL_SUMMONDEMON          = 40;
  const int SPL_FULLHEAL             = 41;
  const int SPL_FIRERAIN             = 42;
  const int SPL_BREATHOFDEATH        = 43;
  const int SPL_MASSDEATH            = 44;
  const int SPL_ARMYOFDARKNESS       = 45;
  const int SPL_SHRINK               = 46;
  const int SPL_TRFSHEEP             = 47;
  const int SPL_TRFSCAVENGER         = 48;
  const int SPL_TRFGIANTRAT          = 49;
  const int SPL_TRFGIANTBUG          = 50;
  const int SPL_TRFWOLF              = 51;
  const int SPL_TRFWARAN             = 52;
  const int SPL_TRFSNAPPER           = 53;
  const int SPL_TRFWARG              = 54;
  const int SPL_TRFFIREWARAN         = 55;
  const int SPL_TRFLURKER            = 56;
  const int SPL_TRFSHADOWBEAST       = 57;
  const int SPL_TRFDRAGONSNAPPER     = 58;
  const int SPL_CHARM                = 59;
  const int SPL_MASTEROFDESASTER     = 60;
  const int SPL_DEATHBOLT            = 61;
  const int SPL_DEATHBALL            = 62;
  const int SPL_CONCUSSIONBOLT       = 63;
  const int SPL_RESERVED_64          = 64;
  const int SPL_RESERVED_65          = 65;
  const int SPL_RESERVED_66          = 66;
  const int SPL_RESERVED_67          = 67;
  const int SPL_RESERVED_68          = 68;
  const int SPL_RESERVED_69          = 69;
  const int SPL_THUNDERSTORM         = 70;
  const int SPL_WHIRLWIND            = 71;
  const int SPL_WATERFIST            = 72;
  const int SPL_ICELANCE             = 73;
  const int SPL_INFLATE              = 74;
  const int SPL_GEYSER               = 75;
  const int SPL_WATERWALL            = 76;
  const int SPL_RESERVED_77          = 77;
  const int SPL_RESERVED_78          = 78;
  const int SPL_RESERVED_79          = 79;
  const int SPL_PLAGUE               = 80;
  const int SPL_SUMMONSWARM          = 81;
  const int SPL_GREENTENTACLE        = 82;
  const int SPL_EARTHQUAKE           = 83;
  const int SPL_SUMMONGUARDIAN       = 84;
  const int SPL_BELIARSRAGE          = 85;
  const int SPL_SUCKENERGY           = 86;
  const int SPL_SKULL                = 87;
  const int SPL_SUMMONZOMBIE         = 88;
  const int SPL_RESERVED_89          = 89;
  const int SPL_RESERVED_90          = 90;
  const int SPL_RESERVED_91          = 91;
  const int SPL_RESERVED_92          = 92;
  const int SPL_RESERVED_93          = 93;
  const int SPL_RESERVED_94          = 94;
  const int SPL_RESERVED_95          = 95;
  const int SPL_RESERVED_96          = 96;
  const int SPL_RESERVED_97          = 97;
  const int SPL_RESERVED_98          = 98;
  const int SPL_RESERVED_99          = 99;
  const int SPL_MAX_SPELL            = 100;
  const int NUM_TARGET_TYPES         = 7;

  enum {
    SPL_STATUS_DONTINVEST           = 0,
    SPL_STATUS_CANINVEST            = 1,
    SPL_STATUS_CAST                 = 2,
    SPL_STATUS_STOP                 = 3,
    SPL_STATUS_NEXTLEVEL            = 4,
    SPL_STATUS_CANINVEST_NO_MANADEC = 8,
    SPL_STATUS_FORCEINVEST          = 1 << 16
  };

  enum {
    SPL_CAT_GOOD,
    SPL_CAT_NEUTRAL,
    SPL_CAT_BAD
  };

  enum {
    TARGET_COLLECT_NONE,
    TARGET_COLLECT_CASTER,
    TARGET_COLLECT_FOCUS,
    TARGET_COLLECT_ALL,
    TARGET_COLLECT_FOCUS_FALLBACK_NONE,
    TARGET_COLLECT_FOCUS_FALLBACK_CASTER,
    TARGET_COLLECT_ALL_FALLBACK_NONE,
    TARGET_COLLECT_ALL_FALLBACK_CASTER
  };

  enum {
    TARGET_FLAG_NONE,
    TARGET_FLAG_ALL,
    TARGET_FLAG_ITEMS,
    TARGET_FLAG_NPCS   = 4,
    TARGET_FLAG_ORCS   = 8,
    TARGET_FLAG_HUMANS = 16,
    TARGET_FLAG_UNDEAD = 32,
    TARGET_FLAG_LIVING = 64
  };

  // sizeof B0h
  class oCSpell : public zCObject {
  public:
    zCLASS_DECLARATION( oCSpell )

    int keyNo;                         // sizeof 04h    offset 24h
    oCVisualFX* effect;                // sizeof 04h    offset 28h
    oCVisualFX* controlWarnFX;         // sizeof 04h    offset 2Ch
    zCVob* spellCaster;                // sizeof 04h    offset 30h
    oCNpc* spellCasterNpc;             // sizeof 04h    offset 34h
    zCVob* spellTarget;                // sizeof 04h    offset 38h
    oCNpc* spellTargetNpc;             // sizeof 04h    offset 3Ch
    oCNpc* saveNpc;                    // sizeof 04h    offset 40h
    float manaTimer;                   // sizeof 04h    offset 44h
    int manaInvested;                  // sizeof 04h    offset 48h
    int spellLevel;                    // sizeof 04h    offset 4Ch
    int spellStatus;                   // sizeof 04h    offset 50h
    int spellID;                       // sizeof 04h    offset 54h
    int spellInfo;                     // sizeof 04h    offset 58h
    int spellEnabled;                  // sizeof 04h    offset 5Ch
    int spellInitDone;                 // sizeof 04h    offset 60h
    int timerEffect;                   // sizeof 04h    offset 64h
    int canBeDeleted;                  // sizeof 04h    offset 68h
    float up;                          // sizeof 04h    offset 6Ch
    float hoverY;                      // sizeof 04h    offset 70h
    float hoverOld;                    // sizeof 04h    offset 74h
    float hoverDir;                    // sizeof 04h    offset 78h
    int spellEnergy;                   // sizeof 04h    offset 7Ch
    struct {
      float manaInvestTime;            // sizeof 04h    offset 80h
      int damagePerLevel;              // sizeof 04h    offset 84h
      int damageType;                  // sizeof 04h    offset 88h
      int spellType;                   // sizeof 04h    offset 8Ch
      int canTurnDuringInvest;         // sizeof 04h    offset 90h
      int canChangeTargetDuringInvest; // sizeof 04h    offset 94h
      int isMultiEffect;               // sizeof 04h    offset 98h
      int targetCollectAlgo;           // sizeof 04h    offset 9Ch
      int targetCollectType;           // sizeof 04h    offset A0h
      int targetCollectRange;          // sizeof 04h    offset A4h
      int targetCollectAzi;            // sizeof 04h    offset A8h
      int targetCollectElev;           // sizeof 04h    offset ACh
    };

    void oCSpell_OnInit()                       zCall( 0x00483C20 );
    void oCSpell_OnInit( int )                  zCall( 0x00483DD0 );
    oCSpell() : zCtor( zCObject )               zInit( oCSpell_OnInit() );
    oCSpell( int a0 ) : zCtor( zCObject )       zInit( oCSpell_OnInit( a0 ));
    void InitValues( int )                      zCall( 0x00484020 );
    zSTRING GetSpellInstanceName( int ) const   zCall( 0x00484150 );
    oCVisualFX* CreateEffect()                  zCall( 0x004842E0 );
    void InitByScript( zSTRING const& )         zCall( 0x00484550 );
    void SetEnabled( int )                      zCall( 0x004847F0 );
    int GetEnabled()                            zCall( 0x00484920 );
    void Setup( zCVob*, zCVob*, int )           zCall( 0x00484930 );
    int Invest()                                zCall( 0x004850D0 );
    int Cast()                                  zCall( 0x00485360 );
    int Stop()                                  zCall( 0x00485510 );
    int Kill()                                  zCall( 0x00485700 );
    void Open()                                 zCall( 0x004858A0 );
    void Close()                                zCall( 0x004859A0 );
    void Reset()                                zCall( 0x00485B00 );
    void StopTargetEffects( zCVob* )            zCall( 0x00485C40 );
    void CallScriptInvestedMana()               zCall( 0x00485D30 );
    int IsValidTarget( zCVob* )                 zCall( 0x004861D0 );
    zCVob* GetVob()                             zCall( 0x00486470 );
    int GetSpellID()                            zCall( 0x00486480 );
    int GetEnergyType()                         zCall( 0x00486490 );
    int GetCategory()                           zCall( 0x004864A0 );
    zSTRING GetName()                           zCall( 0x004864B0 );
    int GetLevel()                              zCall( 0x00486620 );
    int IsInvestSpell()                         zCall( 0x00486630 );
    void SetInvestedMana( int )                 zCall( 0x00486640 );
    int GetSpellStatus()                        zCall( 0x00486660 );
    void SetReleaseStatus()                     zCall( 0x00486670 );
    void SetSpellInfo( int )                    zCall( 0x00486940 );
    void DoLogicInvestEffect()                  zCall( 0x00486950 );
    int CastSpecificSpell()                     zCall( 0x00486960 );
    void EndTimedEffect()                       zCall( 0x00486E10 );
    void DoTimedEffect()                        zCall( 0x00487280 );
    int CanBeDeleted()                          zCall( 0x00487310 );
    int DeleteCaster()                          zCall( 0x00487320 );
    static int IsTargetTypeValid( zCVob*, int ) zCall( 0x00485FC0 );
    static zCObject* _CreateNewInstance()       zCall( 0x00487550 );
    virtual zCClassDef* _GetClassDef() const    zCall( 0x00483D90 );
    virtual void Archive( zCArchiver& )         zCall( 0x00487340 );
    virtual void Unarchive( zCArchiver& )       zCall( 0x00487350 );
    virtual ~oCSpell()                          zCall( 0x00483F50 );

    // user API
    #include "oCSpell.inl"
  };

} // namespace Gothic_II_Addon

#endif // __OSPELL_H__VER3__