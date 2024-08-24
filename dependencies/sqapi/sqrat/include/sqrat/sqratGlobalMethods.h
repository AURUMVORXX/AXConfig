//
// SqratGlobalMethods: Global Methods
//

//
// Copyright (c) 2009 Brandon Jones
// Copyirght 2011 Li-Cheng (Andy) Tai
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

#if !defined(_SCRAT_GLOBAL_METHODS_H_)
#define _SCRAT_GLOBAL_METHODS_H_

#include <squirrel.h>
#include "sqratTypes.h"

namespace Sqrat {

/// @cond DEV

//
// Squirrel Global Functions
//
template <class R>
class SqGlobal {
public:

    template<SQInteger startIdx, class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + startIdx)... };
    }

    template <bool overloaded, SQInteger startIdx, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + sizeof...(Args)) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        using M = R(*)(Args...);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
            auto args = Func_Args<startIdx, Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R ret = std::apply([&method](auto&&... arg) -> decltype(auto) {
                return (*method)(arg.value...);
            }, args);
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            PushVar(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }
};


//
// reference return specialization
//

template <class R>
class SqGlobal<R&> {
public:

    template<SQInteger startIdx, class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + startIdx)... };
    }

    template <bool overloaded, SQInteger startIdx, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + sizeof...(Args)) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        using M = R&(*)(Args...);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
            auto args = Func_Args<startIdx, Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R& ret = std::apply([&method](auto&&... arg) -> decltype(auto) {
                return (*method)(arg.value...);
            }, args);
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            PushVarR(vm, ret);
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 1;
    }
};


//
// void return specialization
//

template <>
class SqGlobal<void> {
public:

    template<SQInteger startIdx, class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + startIdx)... };
    }

    template <bool overloaded, SQInteger startIdx, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != startIdx + sizeof...(Args)) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif

        using M = void(*)(Args...);
        M* method;
        sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

        SQTRY()
            auto args = Func_Args<startIdx, Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            std::apply([&method](auto&&... arg) -> decltype(auto) {
                (*method)(arg.value...);
            }, args);
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
        }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
};


//
// Global Function Resolvers
//

template <class R, class... Args>
SQFUNCTION SqGlobalFunc(R (* /*method*/)(Args...)) {
    return &SqGlobal<R>::template Func<false, 2, Args...>;
}

template <class R, class... Args>
SQFUNCTION SqGlobalFunc(R& (* /*method*/)(Args...)) {
    return &SqGlobal<R&>::template Func<false, 2, Args...>;
}

//
// Member Global Function Resolvers
//

template <class R, class... Args>
SQFUNCTION SqMemberGlobalFunc(R (* /*method*/)(Args...)) {
    return &SqGlobal<R>::template Func<false, 1, Args...>;
}

template <class R, class... Args>
SQFUNCTION SqMemberGlobalFunc(R& (* /*method*/)(Args...)) {
    return &SqGlobal<R&>::template Func<false, 1, Args...>;
}

/// @endcond

}

#endif
