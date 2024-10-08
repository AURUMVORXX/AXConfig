//
// SqModule: API used to communicate with and register squirrel modules
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//

#if !defined(_SQ_MODULE_H_)
#define _SQ_MODULE_H_

#include "squirrel.h"

#ifdef __cplusplus
extern "C" {
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @cond DEV
    /// Allows modules to interface with Squirrel's C api without linking to the squirrel library
    /// If new functions are added to the Squirrel API, they should be added here too
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    typedef struct {
        /*vm*/
        HSQUIRRELVM     (*open)(SQInteger initialstacksize);
        HSQUIRRELVM     (*newthread)(HSQUIRRELVM friendvm, SQInteger initialstacksize);
        void            (*seterrorhandler)(HSQUIRRELVM v);
        void            (*close)(HSQUIRRELVM v);
        void            (*setforeignptr)(HSQUIRRELVM v,SQUserPointer p);
        SQUserPointer   (*getforeignptr)(HSQUIRRELVM v);
#if SQUIRREL_VERSION_NUMBER >= 300
        void            (*setprintfunc)(HSQUIRRELVM v, SQPRINTFUNCTION printfunc, SQPRINTFUNCTION);
#else
        void            (*setprintfunc)(HSQUIRRELVM v, SQPRINTFUNCTION printfunc);
#endif
        SQPRINTFUNCTION (*getprintfunc)(HSQUIRRELVM v);
        SQRESULT        (*suspendvm)(HSQUIRRELVM v);
        SQRESULT        (*wakeupvm)(HSQUIRRELVM v,SQBool resumedret,SQBool retval,SQBool raiseerror,SQBool throwerror);
        SQInteger       (*getvmstate)(HSQUIRRELVM v);

        /*compiler*/
        SQRESULT        (*compile)(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror);
        SQRESULT        (*compilebuffer)(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror);
        void            (*enabledebuginfo)(HSQUIRRELVM v, SQBool enable);
        void            (*notifyallexceptions)(HSQUIRRELVM v, SQBool enable);
        void            (*setcompilererrorhandler)(HSQUIRRELVM v,SQCOMPILERERROR f);

        /*stack operations*/
        void            (*push)(HSQUIRRELVM v,SQInteger idx);
        void            (*pop)(HSQUIRRELVM v,SQInteger nelemstopop);
        void            (*poptop)(HSQUIRRELVM v);
        void            (*remove)(HSQUIRRELVM v,SQInteger idx);
        SQInteger       (*gettop)(HSQUIRRELVM v);
        void            (*settop)(HSQUIRRELVM v,SQInteger newtop);
#if SQUIRREL_VERSION_NUMBER >= 300
        SQRESULT            (*reservestack)(HSQUIRRELVM v,SQInteger nsize);
#else
        void            (*reservestack)(HSQUIRRELVM v,SQInteger nsize);
#endif
        SQInteger       (*cmp)(HSQUIRRELVM v);
        void            (*move)(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx);

        /*object creation handling*/
        SQUserPointer   (*newuserdata)(HSQUIRRELVM v,SQUnsignedInteger size);
        void            (*newtable)(HSQUIRRELVM v);
        void            (*newarray)(HSQUIRRELVM v,SQInteger size);
        void            (*newclosure)(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars);
        SQRESULT        (*setparamscheck)(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask);
        SQRESULT        (*bindenv)(HSQUIRRELVM v,SQInteger idx);
        void            (*pushstring)(HSQUIRRELVM v,const SQChar *s,SQInteger len);
        void            (*pushfloat)(HSQUIRRELVM v,SQFloat f);
        void            (*pushinteger)(HSQUIRRELVM v,SQInteger n);
        void            (*pushbool)(HSQUIRRELVM v,SQBool b);
        void            (*pushuserpointer)(HSQUIRRELVM v,SQUserPointer p);
        void            (*pushnull)(HSQUIRRELVM v);
        SQObjectType    (*gettype)(HSQUIRRELVM v,SQInteger idx);
        SQInteger       (*getsize)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getbase)(HSQUIRRELVM v,SQInteger idx);
        SQBool          (*instanceof)(HSQUIRRELVM v);
#if SQUIRREL_VERSION_NUMBER >= 300
        SQRESULT            (*tostring)(HSQUIRRELVM v,SQInteger idx);
#else
        void            (*tostring)(HSQUIRRELVM v,SQInteger idx);
#endif
        void            (*tobool)(HSQUIRRELVM v, SQInteger idx, SQBool *b);
        SQRESULT        (*getstring)(HSQUIRRELVM v,SQInteger idx,const SQChar **c);
        SQRESULT        (*getinteger)(HSQUIRRELVM v,SQInteger idx,SQInteger *i);
        SQRESULT        (*getfloat)(HSQUIRRELVM v,SQInteger idx,SQFloat *f);
        SQRESULT        (*getbool)(HSQUIRRELVM v,SQInteger idx,SQBool *b);
        SQRESULT        (*getthread)(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread);
        SQRESULT        (*getuserpointer)(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p);
        SQRESULT        (*getuserdata)(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag);
        SQRESULT        (*settypetag)(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag);
        SQRESULT        (*gettypetag)(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag);
        void            (*setreleasehook)(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook);
        SQChar*         (*getscratchpad)(HSQUIRRELVM v,SQInteger minsize);
        SQRESULT        (*getclosureinfo)(HSQUIRRELVM v,SQInteger idx,SQInteger *nparams,SQInteger *nfreevars);
        SQRESULT        (*setnativeclosurename)(HSQUIRRELVM v,SQInteger idx,const SQChar *name);
        SQRESULT        (*setinstanceup)(HSQUIRRELVM v, SQInteger idx, SQUserPointer p);
        SQRESULT        (*getinstanceup)(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag, SQBool throwerror);
        SQRESULT        (*setclassudsize)(HSQUIRRELVM v, SQInteger idx, SQInteger udsize);
        SQRESULT        (*newclass)(HSQUIRRELVM v,SQBool hasbase);
        SQRESULT        (*createinstance)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*setattributes)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getattributes)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getclass)(HSQUIRRELVM v,SQInteger idx);
        void            (*weakref)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getdefaultdelegate)(HSQUIRRELVM v,SQObjectType t);

        /*object manipulation*/
        void            (*pushroottable)(HSQUIRRELVM v);
        void            (*pushregistrytable)(HSQUIRRELVM v);
        void            (*pushconsttable)(HSQUIRRELVM v);
        SQRESULT        (*setroottable)(HSQUIRRELVM v);
        SQRESULT        (*setconsttable)(HSQUIRRELVM v);
        SQRESULT        (*newslot)(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);
        SQRESULT        (*deleteslot)(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
        SQRESULT        (*set)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*get)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*rawget)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*rawset)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*rawdeleteslot)(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
        SQRESULT        (*arrayappend)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*arraypop)(HSQUIRRELVM v,SQInteger idx,SQBool pushval);
        SQRESULT        (*arrayresize)(HSQUIRRELVM v,SQInteger idx,SQInteger newsize);
        SQRESULT        (*arrayreverse)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*arrayremove)(HSQUIRRELVM v,SQInteger idx,SQInteger itemidx);
        SQRESULT        (*arrayinsert)(HSQUIRRELVM v,SQInteger idx,SQInteger destpos);
        SQRESULT        (*setdelegate)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getdelegate)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*clone)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*setfreevariable)(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
        SQRESULT        (*next)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*getweakrefval)(HSQUIRRELVM v,SQInteger idx);
        SQRESULT        (*clear)(HSQUIRRELVM v,SQInteger idx);

        /*calls*/
        SQRESULT        (*call)(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror);
        SQRESULT        (*resume)(HSQUIRRELVM v,SQBool retval,SQBool raiseerror);
        const SQChar*   (*getlocal)(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx);
        const SQChar*   (*getfreevariable)(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval);
        SQRESULT        (*throwerror)(HSQUIRRELVM v,const SQChar *err);
        void            (*reseterror)(HSQUIRRELVM v);
        void            (*getlasterror)(HSQUIRRELVM v);

        /*raw object handling*/
        SQRESULT        (*getstackobj)(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po);
        void            (*pushobject)(HSQUIRRELVM v,HSQOBJECT obj);
        void            (*addref)(HSQUIRRELVM v,HSQOBJECT *po);
        SQBool          (*release)(HSQUIRRELVM v,HSQOBJECT *po);
        void            (*resetobject)(HSQOBJECT *po);
        const SQChar*   (*objtostring)(const HSQOBJECT *o);
        SQBool          (*objtobool)(const HSQOBJECT *o);
        SQInteger       (*objtointeger)(const HSQOBJECT *o);
        SQFloat         (*objtofloat)(const HSQOBJECT *o);
        SQRESULT        (*getobjtypetag)(const HSQOBJECT *o,SQUserPointer * typetag);

        /*GC*/
        SQInteger       (*collectgarbage)(HSQUIRRELVM v);

        /*serialization*/
        SQRESULT        (*writeclosure)(HSQUIRRELVM vm,SQWRITEFUNC writef,SQUserPointer up);
        SQRESULT        (*readclosure)(HSQUIRRELVM vm,SQREADFUNC readf,SQUserPointer up);

        /*mem allocation*/
        void*           (*malloc)(SQUnsignedInteger size);
        void*           (*realloc)(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize);
        void            (*free)(void *p,SQUnsignedInteger size);

        /*debug*/
        SQRESULT        (*stackinfos)(HSQUIRRELVM v,SQInteger level,SQStackInfos *si);
        void            (*setdebughook)(HSQUIRRELVM v);
    
        /*missing vm*/
        void            (*setsharedforeignptr)(HSQUIRRELVM v, SQUserPointer p);
        SQUserPointer   (*getsharedforeignptr)(HSQUIRRELVM v);
        void            (*setvmreleasehook)(HSQUIRRELVM v, SQRELEASEHOOK hook);
        SQRELEASEHOOK   (*getvmreleasehook)(HSQUIRRELVM v);
        void            (*setsharedreleasehook)(HSQUIRRELVM v, SQRELEASEHOOK hook);
        SQRELEASEHOOK   (*getsharedreleasehook)(HSQUIRRELVM v);
        SQPRINTFUNCTION (*geterrorfunc)(HSQUIRRELVM v);
        SQInteger       (*getversion)();

        /*missing object creation handling*/
        void            (*newtableex)(HSQUIRRELVM v, SQInteger initialcapacity);
        SQRESULT        (*setclosureroot)(HSQUIRRELVM v, SQInteger idx);
        SQRESULT        (*getclosureroot)(HSQUIRRELVM v, SQInteger idx);
        void            (*pushthread)(HSQUIRRELVM v, HSQUIRRELVM thread);
        SQRESULT        (*type_of)(HSQUIRRELVM v, SQInteger idx);
        SQHash          (*gethash)(HSQUIRRELVM v, SQInteger idx);
        SQRELEASEHOOK   (*getreleasehook)(HSQUIRRELVM v, SQInteger idx);
        SQRESULT        (*getfunctioninfo)(HSQUIRRELVM v, SQInteger level, SQFunctionInfo* fi);
        SQRESULT        (*getclosurename)(HSQUIRRELVM v, SQInteger idx);
        SQRESULT        (*getmemberhandle)(HSQUIRRELVM v, SQInteger idx, HSQMEMBERHANDLE* handle);
        SQRESULT        (*getbyhandle)(HSQUIRRELVM v, SQInteger idx, const HSQMEMBERHANDLE* handle);
        SQRESULT        (*setbyhandle)(HSQUIRRELVM v, SQInteger idx, const HSQMEMBERHANDLE* handle);
    
        /*missing object manipulation*/
        SQRESULT        (*newmember)(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);
        SQRESULT        (*rawnewmember)(HSQUIRRELVM v, SQInteger idx, SQBool bstatic);

        /*missing calls*/
        SQRESULT        (*getcallee)(HSQUIRRELVM v);
        SQRESULT        (*throwobject)(HSQUIRRELVM v);

        /*missing raw object handling*/
        SQUnsignedInteger   (*getrefcount)(HSQUIRRELVM v, HSQOBJECT* po);
        SQUserPointer       (*objtouserpointer)(const HSQOBJECT* o);
        SQUnsignedInteger   (*getvmrefcount)(HSQUIRRELVM v, const HSQOBJECT* po);

        /*missing GC*/
        SQRESULT        (*resurrectunreachable)(HSQUIRRELVM v);

        /*missing debug*/
        void            (*setnativedebughook)(HSQUIRRELVM v, SQDEBUGHOOK hook);

        /*stdaux*/
        void            (*printcallstack)(HSQUIRRELVM v);
        SQRESULT        (*throwerrorf)(HSQUIRRELVM v, const SQChar* err, ...);

        /*stdblob*/
        SQUserPointer   (*createblob)(HSQUIRRELVM v, SQInteger size);
        SQRESULT        (*getblob)(HSQUIRRELVM v, SQInteger idx, SQUserPointer* ptr);
        SQInteger       (*getblobsize)(HSQUIRRELVM v, SQInteger idx);

        /*stdio*/
        SQUserPointer   (*fopen)(const SQChar*, const SQChar*);
        SQInteger       (*fread)(SQUserPointer, SQInteger, SQInteger, SQUserPointer);
        SQInteger       (*fwrite)(const SQUserPointer, SQInteger, SQInteger, SQUserPointer);
        SQInteger       (*fseek)(SQUserPointer, SQInteger, SQInteger);
        SQInteger       (*ftell)(SQUserPointer);
        SQInteger       (*fflush)(SQUserPointer);
        SQInteger       (*fclose)(SQUserPointer);
        SQInteger       (*feof)(SQUserPointer);
        SQRESULT        (*createfile)(HSQUIRRELVM v, SQUserPointer file, SQBool own);
        SQRESULT        (*getfile)(HSQUIRRELVM v, SQInteger idx, SQUserPointer* file);
        SQRESULT        (*loadfile)(HSQUIRRELVM v, const SQChar* filename, SQBool printerror);
        SQRESULT        (*dofile)(HSQUIRRELVM v, const SQChar* filename, SQBool retval, SQBool printerror);
        SQRESULT        (*writeclosuretofile)(HSQUIRRELVM v, const SQChar* filename);

        /*stdstring*/
        SQRESULT (*format)(HSQUIRRELVM v, SQInteger nformatstringidx, SQInteger* outlen, SQChar** output);
        void (*pushstringf)(HSQUIRRELVM v, const SQChar* s, ...);

    } sq_api;
    typedef sq_api* HSQAPI;
    /// @endcond

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_SQ_MODULE_H_*/
