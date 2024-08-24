//
// SqratOverloadMethods: Overload Methods
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

#if !defined(_SQRAT_OVERLOAD_METHODS_H_)
#define _SQRAT_OVERLOAD_METHODS_H_

#include <squirrel.h>
#include <sstream>
#include "sqratTypes.h"
#include "sqratUtil.h"
#include "sqratGlobalMethods.h"
#include "sqratMemberMethods.h"

namespace Sqrat {

/// @cond DEV

//
// Overload name generator
//

class SqOverloadName {
public:

    static string Get(const SQChar* name, SQInteger args) {
        std::basic_stringstream<SQChar> overloadName;
        overloadName << _SC("__overload_") << name << args;

        return overloadName.str();
    }
};


//
// Squirrel Overload Functions
//

template <class R>
class SqOverload {
public:

    static SQInteger Func(HSQUIRRELVM vm) {
        // Get the arg count
        SQInteger argCount = sq_gettop(vm) - 2;

        const SQChar* funcName;
        sq_getstring(vm, -1, &funcName); // get the function name (free variable)

        string overloadName = SqOverloadName::Get(funcName, argCount);

        sq_pushstring(vm, overloadName.c_str(), -1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, 1))) { // Lookup the proper overload
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#else
        sq_get(vm, 1);
#endif

        // Push the args again
        for (int i = 1; i <= argCount + 1; ++i) {
            sq_push(vm, i);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, argCount + 1, true, ErrorHandling::IsEnabled());
        if (SQ_FAILED(result)) {
            return sq_throwerror(vm, LastErrorString(vm).c_str());
        }
#else
        sq_call(vm, argCount + 1, true, ErrorHandling::IsEnabled());
#endif

        return 1;
    }
};


//
// void return specialization
//

template <>
class SqOverload<void> {
public:

    static SQInteger Func(HSQUIRRELVM vm) {
        // Get the arg count
        SQInteger argCount = sq_gettop(vm) - 2;

        const SQChar* funcName;
        sq_getstring(vm, -1, &funcName); // get the function name (free variable)

        string overloadName = SqOverloadName::Get(funcName, argCount);

        sq_pushstring(vm, overloadName.c_str(), -1);

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (SQ_FAILED(sq_get(vm, 1))) { // Lookup the proper overload
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#else
        sq_get(vm, 1);
#endif

        // Push the args again
        for (int i = 1; i <= argCount + 1; ++i) {
            sq_push(vm, i);
        }

#if !defined (SCRAT_NO_ERROR_CHECKING)
        SQRESULT result = sq_call(vm, argCount + 1, false, ErrorHandling::IsEnabled());
        if (SQ_FAILED(result)) {
            return sq_throwerror(vm, LastErrorString(vm).c_str());
        }
#else
        sq_call(vm, argCount + 1, false, ErrorHandling::IsEnabled());
#endif

        return 0;
    }
};


//
// Global Overloaded Function Resolvers
//

template <class R, class... Args>
SQFUNCTION SqGlobalOverloadedFunc(R (* /*method*/)(Args...)) {
    return &SqGlobal<R>::template Func<true, 2, Args...>;
}

template <class R, class... Args>
SQFUNCTION SqGlobalOverloadedFunc(R& (* /*method*/)(Args...)) {
    return &SqGlobal<R&>::template Func<true, 2, Args...>;
}

//
// Member Global Overloaded Function Resolvers
//

template <class R, class... Args>
SQFUNCTION SqMemberGlobalOverloadedFunc(R (* /*method*/)(Args...)) {
    return &SqGlobal<R>::template Func<true, 1, Args...>;
}

template <class R, class... Args>
SQFUNCTION SqMemberGlobalOverloadedFunc(R& (* /*method*/)(Args...)) {
    return &SqGlobal<R&>::template Func<true, 1, Args...>;
}

//
// Member Overloaded Function Resolvers
//

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(Args...)) {
    return &SqMember<C, R>::template Func<true, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberOverloadedFunc(R (C::* /*method*/)(Args...) const) {
    return &SqMember<C, R>::template FuncC<true, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(Args...)) {
    return &SqMember<C, R&>::template Func<true, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberOverloadedFunc(R& (C::* /*method*/)(Args...) const) {
    return &SqMember<C, R&>::template FuncC<true, Args...>;
}

//
// Overload handler resolver
//

template <class R, class... Args>
inline SQFUNCTION SqOverloadFunc(R (* /*method*/)(Args...)) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(Args...)) {
    return &SqOverload<R>::Func;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqOverloadFunc(R (C::* /*method*/)(Args...) const ) {
    return &SqOverload<R>::Func;
}

//
// Query argument count
//

template <class R, class... Args>
inline int SqGetArgCount(R (* /*method*/)(Args...)) {
    return sizeof...(Args);
}

//
// Query member function argument count
//

template <class C, class R, class... Args>
inline int SqGetArgCount(R (C::* /*method*/)(Args...)) {
    return sizeof...(Args);
}

//
// Query const member function argument count
//

// Arg Count 1
template <class C, class R, class... Args>
inline int SqGetArgCount(R (C::* /*method*/)(Args...) const) {
    return sizeof...(Args);
}

/// @endcond

}

#endif
