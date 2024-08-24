﻿// Supported with union (c) 2018-2023 Union team
// Licence: GNU General Public License

#ifndef __ZMENU__ITEM_H__VER0__
#define __ZMENU__ITEM_H__VER0__

#include "zOption.h"
#include "zViews.h"
#include "zVob.h"
#include "zMathTools.h"

namespace Gothic_I_Classic {
  const int MAX_ITEMS       = 150;
  const int MAX_EVENTS      = 10;
  const int MAX_SEL_ACTIONS = 5;
  const int MAX_USERVARS    = 4;
  const int MAX_USERSTRINGS = 10;

  enum zTMenuItem {
    MENU_ITEM_UNDEF,
    MENU_ITEM_TEXT,
    MENU_ITEM_SLIDER,
    MENU_ITEM_INPUT,
    MENU_ITEM_CURSOR,
    MENU_ITEM_CHOICEBOX,
    MENU_ITEM_BUTTON,
    MENU_ITEM_LISTBOX
  };

  enum zTMenuItemFlags {
    IT_UNDEF,
    IT_CHROMAKEYED,
    IT_TRANSPARENT,
    IT_SELECTABLE    = 4,
    IT_MOVEABLE      = 8,
    IT_TXT_CENTER    = 16,
    IT_DISABLED      = 32,
    IT_FADE          = 64,
    IT_EFFECTS_NEXT  = 128,
    IT_ONLY_OUT_GAME = 256,
    IT_ONLY_IN_GAME  = 512,
    IT_PERF_OPTION   = 1024,
    IT_MULTILINE     = 2048,
    IT_NEEDS_APPLY   = 4096,
    IT_NEEDS_RESTART = 8192,
    IT_EXTENDED_MENU = 16384
  };

  enum zTMenuItemEvent {
    EVENT_UNDEF,
    EVENT_EXECUTE,
    EVENT_CHANGED,
    EVENT_LEAVE,
    EVENT_TIMER,
    EVENT_CLOSE,
    EVENT_INIT,
    EVENT_SEL_PREV,
    EVENT_SEL_NEXT,
    EVENT_MAX
  };

  enum zTMenuItemSelAction {
    SEL_ACTION_UNDEF,
    SEL_ACTION_BACK,
    SEL_ACTION_STARTMENU,
    SEL_ACTION_STARTITEM,
    SEL_ACTION_CLOSE,
    SEL_ACTION_CONCOMMANDS,
    SEL_ACTION_PLAY_SOUND,
    SEL_ACTION_EXECCOMMANDS
  };

  // sizeof 3D4h
  class zCMenuItem : public zCView {
  public:
    zOPERATORS_DECLARATION()

    zSTRING m_parFontName;                       // sizeof 14h    offset FCh
    zSTRING m_parText[MAX_USERSTRINGS];          // sizeof C8h    offset 110h
    zSTRING m_parBackPic;                        // sizeof 14h    offset 1D8h
    zSTRING m_parAlphaMode;                      // sizeof 14h    offset 1ECh
    int m_parAlpha;                              // sizeof 04h    offset 200h
    int m_parType;                               // sizeof 04h    offset 204h
    int m_parOnSelAction[MAX_SEL_ACTIONS];       // sizeof 14h    offset 208h
    zSTRING m_parOnSelAction_S[MAX_SEL_ACTIONS]; // sizeof 64h    offset 21Ch
    zSTRING m_parOnChgSetOption;                 // sizeof 14h    offset 280h
    zSTRING m_parOnChgSetOptionSection;          // sizeof 14h    offset 294h
    int m_parOnEventAction[MAX_EVENTS];          // sizeof 28h    offset 2A8h
    int m_parPosX;                               // sizeof 04h    offset 2D0h
    int m_parPosY;                               // sizeof 04h    offset 2D4h
    int m_parDimX;                               // sizeof 04h    offset 2D8h
    int m_parDimY;                               // sizeof 04h    offset 2DCh
    float m_parSizeStartScale;                   // sizeof 04h    offset 2E0h
    int m_parItemFlags;                          // sizeof 04h    offset 2E4h
    float m_parOpenDelayTime;                    // sizeof 04h    offset 2E8h
    float m_parOpenDuration;                     // sizeof 04h    offset 2ECh
    float m_parUserFloat[MAX_USERVARS];          // sizeof 10h    offset 2F0h
    zSTRING m_parUserString[MAX_USERVARS];       // sizeof 50h    offset 300h
    int m_parFrameSizeX;                         // sizeof 04h    offset 350h
    int m_parFrameSizeY;                         // sizeof 04h    offset 354h
    int m_iRefCtr;                               // sizeof 04h    offset 358h
    zCView* m_pInnerWindow;                      // sizeof 04h    offset 35Ch
    zCFont* m_pFont;                             // sizeof 04h    offset 360h
    zCFont* m_pFontHi;                           // sizeof 04h    offset 364h
    zCFont* m_pFontSel;                          // sizeof 04h    offset 368h
    zCFont* m_pFontDis;                          // sizeof 04h    offset 36Ch
    int m_bViewInitialized;                      // sizeof 04h    offset 370h
    int m_bLeaveItem;                            // sizeof 04h    offset 374h
    int m_bVisible;                              // sizeof 04h    offset 378h
    zCArray<zSTRING>m_listLines;                 // sizeof 0Ch    offset 37Ch
    zSTRING id;                                  // sizeof 14h    offset 388h
    int inserted;                                // sizeof 04h    offset 39Ch
    int changed;                                 // sizeof 04h    offset 3A0h
    int active;                                  // sizeof 04h    offset 3A4h
    int open;                                    // sizeof 04h    offset 3A8h
    int close;                                   // sizeof 04h    offset 3ACh
    int opened;                                  // sizeof 04h    offset 3B0h
    int closed;                                  // sizeof 04h    offset 3B4h
    int disabled;                                // sizeof 04h    offset 3B8h
    zCView* orgWin;                              // sizeof 04h    offset 3BCh
    float fxTimer;                               // sizeof 04h    offset 3C0h
    float openDelayTimer;                        // sizeof 04h    offset 3C4h
    float activeTimer;                           // sizeof 04h    offset 3C8h
    int registeredCPP;                           // sizeof 04h    offset 3CCh
    int firstTimeInserted;                       // sizeof 04h    offset 3D0h

    zDefineInheritableCtor( zCMenuItem ) : zCtor( zCView ) {}
    void zCMenuItem_OnInit( zSTRING const& )            zCall( 0x004D1F90 );
    void zCMenuItem_OnInit()                            zCall( 0x004D2160 );
    zCMenuItem* GetSelItem()                            zCall( 0x004D1930 );
    zCMenuItem( zSTRING const& a0 ) : zCtor( zCView )   zInit( zCMenuItem_OnInit( a0 ));
    zCMenuItem() : zCtor( zCView )                      zInit( zCMenuItem_OnInit() );
    void Init()                                         zCall( 0x004D2500 );
    void SetByScript( zSTRING& )                        zCall( 0x004D2840 );
    int GetDimX( int )                                  zCall( 0x004D3150 );
    int GetDimY( int )                                  zCall( 0x004D3250 );
    void InitView()                                     zCall( 0x004D3340 );
    void Close()                                        zCall( 0x004D34D0 );
    zTMenuItem GetType()                                zCall( 0x004D3520 );
    void SetName( zSTRING const& )                      zCall( 0x004D3600 );
    zSTRING& GetName()                                  zCall( 0x004D3740 );
    void GetCoords( int&, int&, int&, int& )            zCall( 0x004D3750 );
    zTMenuItemSelAction GetSelActionType( int )         zCall( 0x004D3760 );
    zSTRING& GetSelActionString( int )                  zCall( 0x004D3770 );
    void SetName( zSTRING& )                            zCall( 0x004D3790 );
    void Register()                                     zCall( 0x004D38F0 );
    void Unregister()                                   zCall( 0x004D3AB0 );
    int IsRegistered()                                  zCall( 0x004D3BE0 );
    void UpdateSize()                                   zCall( 0x004D42B0 );
    int GetEventFunc( zTMenuItemEvent )                 zCall( 0x004D4C40 );
    void SetIsActive( int )                             zCall( 0x004D4C50 );
    void SetIsSelectable( int )                         zCall( 0x004D4D60 );
    int GetIsSelectable()                               zCall( 0x004D4DB0 );
    void SetIsDisabled( int )                           zCall( 0x004D4E20 );
    int GetIsDisabled()                                 zCall( 0x004D4E30 );
    void SetIsVisible( int )                            zCall( 0x004D4E70 );
    int GetIsVisible()                                  zCall( 0x004D4E80 );
    static int CompareNames( void const*, void const* ) zCall( 0x004D15A0 );
    static void Startup()                               zCall( 0x004D1610 );
    static void Shutdown()                              zCall( 0x004D1690 );
    static zCMenuItem* GetByName( zSTRING const& )      zCall( 0x004D17A0 );
    static zCMenuItem* Create( zSTRING const& )         zCall( 0x004D1970 );
    /* for zCViewBase num : 32*/
    virtual ~zCMenuItem()                               zCall( 0x004D22E0 );
    virtual void DrawItems()                            zCall( 0x004D4A80 );
    virtual void InitMenuItem()                         zCall( 0x004D32B0 );
    virtual int ToggleValue( int, int )                 zCall( 0x004D34F0 );
    virtual int Run()                                   zCall( 0x004D45A0 );
    virtual zSTRING GetText( int )                      zCall( 0x004D3530 );
    virtual void SetText( zSTRING const&, int, int )    zCall( 0x004D3C80 );
    virtual void SetText( zCArray<zSTRING>, int )       zCall( 0x004D4380 );
    virtual void SetMinValue( float )                   zCall( 0x004D1EF0 );
    virtual void SetMaxValue( float )                   zCall( 0x004D1F00 );
    virtual void Enter()                                zCall( 0x004D4540 );
    virtual void Leave()                                zCall( 0x004D4550 );
    virtual void Draw()                                 zCall( 0x004D4940 );
    virtual void DrawFront()                            zCall( 0x004D4950 );
    virtual int Show()                                  zCall( 0x004D3420 );
    virtual int Hide()                                  zCall( 0x004D3460 );
    virtual int HasBeenCanceled()                       zCall( 0x004D1F10 );
    virtual void Open()                                 zCall( 0x004D34A0 );
    virtual int Input( int, zSTRING& )                  zCall( 0x004D4600 );
    virtual void InsertInWin( zCView* )                 zCall( 0x004D2B40 );
    virtual void RemoveFromWin()                        zCall( 0x004D30F0 );
    virtual void UpdateContent()                        zCall( 0x004D4AA0 );
    virtual void UpdateFX()                             zCall( 0x004D4AB0 );
    /* for zCInputCallback num : 1*/
    virtual int HandleEvent( int )                      zCall( 0x004D4560 );

    // static properties
    static zCArraySort<zCMenuItem*>& itemList;
    static zCMenuItem*& tmp;

    // user API
    #include "zCMenuItem.inl"
  };

  // sizeof 3F0h
  class zCMenuItemInput : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    zSTRING value;         // sizeof 14h    offset 3D4h
    unsigned short curPos; // sizeof 02h    offset 3E8h
    int canceled;          // sizeof 04h    offset 3ECh

    zCMenuItemInput() : zCtor( zCMenuItem ) {}
    void zCMenuItemInput_OnInit( zSTRING const& )                       zCall( 0x004D4EC0 );
    zCMenuItemInput( zSTRING const& a0 ) : zCtor( zCMenuItem )          zInit( zCMenuItemInput_OnInit( a0 ));
    void SetValue( zSTRING )                                            zCall( 0x004D5120 );
    zSTRING GetValue()                                                  zCall( 0x004D51A0 );
    /* for zCViewBase num : 32*/
    virtual ~zCMenuItemInput()                                          zCall( 0x004D5070 );
    virtual void InitMenuItem()                                         zCall( 0x004D51C0 );
    virtual int Run()                                                   zCall( 0x004D53A0 );
    virtual void Enter()                                                zCall( 0x004D1F20 );
    virtual void Leave()                                                zCall( 0x004D1F30 );
    virtual int HasBeenCanceled()                                       zCall( 0x004D1F50 );
    virtual void InsertInWin( zCView* )                                 zCall( 0x004D5370 );
    /* for zCInputCallback num : 1*/
    virtual int HandleEvent( int )                                      zCall( 0x004D1F40 );

    // user API
    #include "zCMenuItemInput.inl"
  };

  // sizeof 400h
  class zCMenuItemText : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    enum zCMenuItemTextEnum3 {
      MODE_SIMPLE,
      MODE_ENUM,
      MODE_MULTILINE
    };

    zCMenuItemTextEnum3 m_mode; // sizeof 04h    offset 3D4h
    zSTRING m_fullText;         // sizeof 14h    offset 3D8h
    int m_numOptions;           // sizeof 04h    offset 3ECh
    int m_topLine;              // sizeof 04h    offset 3F0h
    int m_viewLines;            // sizeof 04h    offset 3F4h
    int m_numLines;             // sizeof 04h    offset 3F8h
    int m_unformated;           // sizeof 04h    offset 3FCh

    zCMenuItemText() : zCtor( zCMenuItem ) {}
    void zCMenuItemText_OnInit( zSTRING const& )                           zCall( 0x004D56D0 );
    zCMenuItemText( zSTRING const& a0 ) : zCtor( zCMenuItem )              zInit( zCMenuItemText_OnInit( a0 ));
    void FormatMultiline()                                                 zCall( 0x004D5850 );
    void DrawMultiline()                                                   zCall( 0x004D5BD0 );
    /* for zCViewBase num : 33*/
    virtual ~zCMenuItemText()                                              zCall( 0x004D57A0 );
    virtual void InitMenuItem()                                            zCall( 0x004D5F40 );
    virtual void SetText( zSTRING const&, int, int )                       zCall( 0x004D6430 );
    virtual void SetText( zCArray<zSTRING>, int )                          zCall( 0x004D66F0 );
    virtual void DrawFront()                                               zCall( 0x004D5810 );
    virtual void SetEnum( zSTRING const& )                                 zCall( 0x004D6100 );
    /* for zCInputCallback num : 1*/
    virtual int HandleEvent( int )                                         zCall( 0x004D6280 );

    // user API
    #include "zCMenuItemText.inl"
  };

  // sizeof 3E8h
  class zCMenuItemSlider : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    zCViewWindow* slider; // sizeof 04h    offset 3D4h
    int slideStep;        // sizeof 04h    offset 3D8h
    float sliderValue;    // sizeof 04h    offset 3DCh
    int sliderDimX;       // sizeof 04h    offset 3E0h
    int sliderPos;        // sizeof 04h    offset 3E4h

    zCMenuItemSlider() : zCtor( zCMenuItem ) {}
    void zCMenuItemSlider_OnInit( zSTRING const& )                       zCall( 0x004D6750 );
    zCMenuItemSlider( zSTRING const& a0 ) : zCtor( zCMenuItem )          zInit( zCMenuItemSlider_OnInit( a0 ));
    void SetValue( float )                                               zCall( 0x004D6E20 );
    float GetValue()                                                     zCall( 0x004D6EA0 );
    /* for zCViewBase num : 33*/
    virtual ~zCMenuItemSlider()                                          zCall( 0x004D67F0 );
    virtual void InitMenuItem()                                          zCall( 0x004D6AF0 );
    virtual int ToggleValue( int, int )                                  zCall( 0x004D6810 );
    virtual void InsertInWin( zCView* )                                  zCall( 0x004D6BB0 );
    virtual void RemoveFromWin()                                         zCall( 0x004D6D90 );
    virtual void SetIsActive( int )                                      zCall( 0x004D1F60 );
    /* for zCInputCallback num : 1*/
    virtual int HandleEvent( int )                                       zCall( 0x004D1F80 );

    // user API
    #include "zCMenuItemSlider.inl"
  };

  // sizeof 3ECh
  class zCMenuItemButton : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    zSTRING pic; // sizeof 14h    offset 3D4h
    int active;  // sizeof 04h    offset 3E8h

    zCMenuItemButton() : zCtor( zCMenuItem ) {}
    void zCMenuItemButton_OnInit( zSTRING const& )                       zCall( 0x004D8090 );
    zCMenuItemButton( zSTRING const& a0 ) : zCtor( zCMenuItem )          zInit( zCMenuItemButton_OnInit( a0 ));
    void Toggle()                                                        zCall( 0x004D84C0 );
    /* for zCViewBase num : 32*/
    virtual ~zCMenuItemButton()                                          zCall( 0x004D8240 );
    virtual void InitMenuItem()                                          zCall( 0x004D82F0 );
    virtual int Run()                                                    zCall( 0x004D86C0 );
    virtual void InsertInWin( zCView* )                                  zCall( 0x004D8930 );
    virtual void RemoveFromWin()                                         zCall( 0x004D8970 );
    /* for zCInputCallback num : 1*/

    // user API
    #include "zCMenuItemButton.inl"
  };

  // sizeof 3E4h
  class zCMenuItemChoice : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    zCView* winCursor; // sizeof 04h    offset 3D4h
    int option;        // sizeof 04h    offset 3D8h
    int optionStart;   // sizeof 04h    offset 3DCh
    int curStep;       // sizeof 04h    offset 3E0h

    zCMenuItemChoice() : zCtor( zCMenuItem ) {}
    void zCMenuItemChoice_OnInit( zSTRING const& )                       zCall( 0x004D6EB0 );
    zCMenuItemChoice( zSTRING const& a0 ) : zCtor( zCMenuItem )          zInit( zCMenuItemChoice_OnInit( a0 ));
    int SetOptionByString( zSTRING )                                     zCall( 0x004D7140 );
    zSTRING GetStringByOption()                                          zCall( 0x004D7510 );
    void Resize()                                                        zCall( 0x004D7900 );
    int GetNumOptions()                                                  zCall( 0x004D7C10 );
    /* for zCViewBase num : 32*/
    virtual ~zCMenuItemChoice()                                          zCall( 0x004D6F10 );
    virtual void InitMenuItem()                                          zCall( 0x004D7F70 );
    virtual int ToggleValue( int, int )                                  zCall( 0x004D6F30 );
    virtual zSTRING GetText( int )                                       zCall( 0x004D7DF0 );
    virtual void Draw()                                                  zCall( 0x004D79D0 );
    virtual void DrawFront()                                             zCall( 0x004D79E0 );
    virtual void InsertInWin( zCView* )                                  zCall( 0x004D76A0 );
    virtual void RemoveFromWin()                                         zCall( 0x004D7870 );
    /* for zCInputCallback num : 1*/

    // user API
    #include "zCMenuItemChoice.inl"
  };

  // sizeof 2Ch
  struct zTMenuItemListElement {
    zOPERATORS_DECLARATION()

    zSTRING title;             // sizeof 14h    offset 00h
    zSTRING content;           // sizeof 14h    offset 14h
    zCMenuItem* contentViewer; // sizeof 04h    offset 28h

    void zTMenuItemListElement_OnInit() zCall( 0x004D9FE0 );
    ~zTMenuItemListElement()            zCall( 0x00475490 );
    zTMenuItemListElement()             zInit( zTMenuItemListElement_OnInit() );

    // user API
    #include "zTMenuItemListElement.inl"
  };

  // sizeof 3F4h
  class zCMenuItemList : public zCMenuItem {
  public:
    zOPERATORS_DECLARATION()

    zCArray<zTMenuItemListElement> m_list; // sizeof 0Ch    offset 3D4h
    int m_cur_element;                     // sizeof 04h    offset 3E0h
    int m_top_element;                     // sizeof 04h    offset 3E4h
    zCView* m_pInnerWindow2;               // sizeof 04h    offset 3E8h
    zCView* m_pViewArrowUp;                // sizeof 04h    offset 3ECh
    zCView* m_pViewArrowDn;                // sizeof 04h    offset 3F0h

    zCMenuItemList() : zCtor( zCMenuItem ) {}
    void zCMenuItemList_OnInit( zSTRING const& )                       zCall( 0x004D8A30 );
    zCMenuItemList( zSTRING const& a0 ) : zCtor( zCMenuItem )          zInit( zCMenuItemList_OnInit( a0 ));
    void DeleteContent()                                               zCall( 0x004D8C80 );
    void InsertEnd( zTMenuItemListElement& )                           zCall( 0x004D8CD0 );
    void InsertFront( zTMenuItemListElement& )                         zCall( 0x004D8EE0 );
    void ShowContent()                                                 zCall( 0x004D98A0 );
    void JumpToNextEntry()                                             zCall( 0x004D9A50 );
    void JumpToPrevEntry()                                             zCall( 0x004D9A70 );
    void JumpToTopEntry()                                              zCall( 0x004D9A90 );
    void JumpToLastEntry()                                             zCall( 0x004D9AB0 );
    /* for zCViewBase num : 32*/
    virtual ~zCMenuItemList()                                          zCall( 0x004D8AB0 );
    virtual void InitMenuItem()                                        zCall( 0x004D8BE0 );
    virtual int Run()                                                  zCall( 0x004D8B50 );
    virtual void Enter()                                               zCall( 0x004D9300 );
    virtual void Leave()                                               zCall( 0x004D9310 );
    virtual void DrawFront()                                           zCall( 0x004D9330 );
    virtual int Show()                                                 zCall( 0x004D8BF0 );
    virtual int Hide()                                                 zCall( 0x004D8C40 );
    virtual void InsertInWin( zCView* )                                zCall( 0x004D90D0 );
    virtual void RemoveFromWin()                                       zCall( 0x004D9250 );
    virtual void UpdateContent()                                       zCall( 0x004D9320 );
    /* for zCInputCallback num : 1*/
    virtual int HandleEvent( int )                                     zCall( 0x004D9640 );

    // user API
    #include "zCMenuItemList.inl"
  };

} // namespace Gothic_I_Classic

#endif // __ZMENU__ITEM_H__VER0__