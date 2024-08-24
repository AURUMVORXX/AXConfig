//
// SqratMemberMethods: Member Methods
//

//
// Copyright (c) 2009 Brandon Jones
// Copyright 2011 Li-Cheng (Andy) Tai
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

#if !defined(_SCRAT_MEMBER_METHODS_H_)
#define _SCRAT_MEMBER_METHODS_H_

#include <squirrel.h>
#include "sqratTypes.h"

namespace Sqrat {

/// @cond DEV

//
// Squirrel Global Functions
//

template <class C, class R>
class SqMember {
public:

    template<class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + 2)... };
    }

    template <bool overloaded, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = R(C::*)(Args...);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R ret = std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
                return (ptr->*method)(arg.value...);
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

    template <bool overloaded, class... Args>
    static SQInteger FuncC(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = R(C::*)(Args...) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R ret = std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
                return (ptr->*method)(arg.value...);
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

template <class C, class R>
class SqMember<C, R&> {
public:

    template<class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + 2)... };
    }

    template <bool overloaded, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = R&(C::*)(Args...);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R& ret = std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
                return (ptr->*method)(arg.value...);
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

    template <bool overloaded, class... Args>
    static SQInteger FuncC(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = R&(C::*)(Args...) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            R& ret = std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
                return (ptr->*method)(arg.value...);
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

template <class C>
class SqMember<C, void> {
public:

    template<class... Args, std::size_t... idx>
    static inline std::tuple<Var<Args>...> Func_Args(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        return std::tuple<Var<Args>...> { Var<Args>(vm, idx + 2)... };
    }

    template <bool overloaded, class... Args>
    static SQInteger Func(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = void(C::*)(Args...);
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
                (ptr->*method)(arg.value...);
            }, args);
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }

    template <bool overloaded, class... Args>
    static SQInteger FuncC(HSQUIRRELVM vm) {

#if !defined (SCRAT_NO_ERROR_CHECKING)
        if (!SQRAT_CONST_CONDITION(overloaded) && sq_gettop(vm) != sizeof...(Args) + 2) {
            return sq_throwerror(vm, _SC("wrong number of parameters"));
        }
#endif
        using M = void(C::*)(Args...) const;
        M* methodPtr;
        sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
        M method = *methodPtr;

        C* ptr;
        SQTRY()
            ptr = Var<C*>(vm, 1).value;
            SQCATCH_NOEXCEPT(vm) {
                SQCLEAR(vm); // clear the previous error
                assert(0); // may fail because C is not a type bound in the VM
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            assert(0); // may fail because C is not a type bound in the VM
            return sq_throwerror(vm, SQWHAT(vm));
        }

        SQTRY()
            auto args = Func_Args<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
            std::apply([&ptr, &method](auto&&... arg) -> decltype(auto) {
            (ptr->*method)(arg.value...);
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
// Member Function Resolvers
//

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(Args...)) {
    return &SqMember<C, R>::template Func<false, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberFunc(R (C::* /*method*/)(Args...) const) {
    return &SqMember<C, R>::template FuncC<false, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(Args...)) {
    return &SqMember<C, R&>::template Func<false, Args...>;
}

template <class C, class R, class... Args>
inline SQFUNCTION SqMemberFunc(R& (C::* /*method*/)(Args...) const) {
    return &SqMember<C, R&>::template FuncC<false, Args...>;
}

//
// Variable Get
//

template <class C, class V>
inline SQInteger sqDefaultGet(HSQUIRRELVM vm) {
    C* ptr;
    SQTRY()
    ptr = Var<C*>(vm, 1).value;
    SQCATCH_NOEXCEPT(vm) {
        SQCLEAR(vm); // clear the previous error
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    typedef V C::*M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    PushVarR(vm, ptr->*member);

    return 1;
}

template <class C, class V>
inline SQInteger sqStaticGet(HSQUIRRELVM vm) {
    typedef V *M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    PushVarR(vm, *member);

    return 1;
}

inline SQInteger sqVarGet(HSQUIRRELVM vm) {
    // Find the get method in the get table
    sq_push(vm, 2);
#if !defined (SCRAT_NO_ERROR_CHECKING)
    if (SQ_FAILED(sq_rawget(vm, -2))) {
#if (SQUIRREL_VERSION_NUMBER>= 200) && (SQUIRREL_VERSION_NUMBER < 300) // Squirrel 2.x
        return sq_throwerror(vm, _SC("member variable not found"));
#else // Squirrel 3.x
        sq_pushnull(vm);
        return sq_throwobject(vm);
#endif
    }
#else
    sq_rawget(vm, -2);
#endif

    // push 'this'
    sq_push(vm, 1);

    // Call the getter
#if !defined (SCRAT_NO_ERROR_CHECKING)
    SQRESULT result = sq_call(vm, 1, true, ErrorHandling::IsEnabled());
    if (SQ_FAILED(result)) {
        return sq_throwerror(vm, LastErrorString(vm).c_str());
    }
#else
    sq_call(vm, 1, true, ErrorHandling::IsEnabled());
#endif

    return 1;
}


//
// Variable Set
//

template <class C, class V>
inline SQInteger sqDefaultSet(HSQUIRRELVM vm) {
    C* ptr;
    SQTRY()
    ptr = Var<C*>(vm, 1).value;
    SQCATCH_NOEXCEPT(vm) {
        SQCLEAR(vm); // clear the previous error
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    typedef V C::*M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    SQTRY()
    if (is_pointer<V>::value || is_reference<V>::value) {
        ptr->*member = Var<V>(vm, 2).value;
    } else {
        ptr->*member = Var<const V&>(vm, 2).value;
    }
    SQCATCH_NOEXCEPT(vm) {
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    return 0;
}

template <class C, class V>
inline SQInteger sqStaticSet(HSQUIRRELVM vm) {
    typedef V *M;
    M* memberPtr = NULL;
    sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
    M member = *memberPtr;

    SQTRY()
    if (is_pointer<V>::value || is_reference<V>::value) {
        *member = Var<V>(vm, 2).value;
    } else {
        *member = Var<const V&>(vm, 2).value;
    }
    SQCATCH_NOEXCEPT(vm) {
        return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
    }
    SQCATCH(vm) {
        return sq_throwerror(vm, SQWHAT(vm));
    }

    return 0;
}

inline SQInteger sqVarSet(HSQUIRRELVM vm) {
    // Find the set method in the set table
    sq_push(vm, 2);
#if !defined (SCRAT_NO_ERROR_CHECKING)
    if (SQ_FAILED(sq_rawget(vm, -2))) {
#if (SQUIRREL_VERSION_NUMBER>= 200) && (SQUIRREL_VERSION_NUMBER < 300) // Squirrel 2.x
        return sq_throwerror(vm, _SC("member variable not found"));
#else // Squirrel 3.x
        sq_pushnull(vm);
        return sq_throwobject(vm);
#endif
    }
#else
    sq_rawget(vm, -2);
#endif

    // push 'this'
    sq_push(vm, 1);
    sq_push(vm, 3);

    // Call the setter
#if !defined (SCRAT_NO_ERROR_CHECKING)
    SQRESULT result = sq_call(vm, 2, false, ErrorHandling::IsEnabled());
    if (SQ_FAILED(result)) {
        return sq_throwerror(vm, LastErrorString(vm).c_str());
    }
#else
    sq_call(vm, 2, false, ErrorHandling::IsEnabled());
#endif

    return 0;
}

/// @endcond

}

#endif
