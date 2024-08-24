//
// SqratAllocator: Custom Class Allocation/Deallocation
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

#if !defined(_SCRAT_ALLOCATOR_H_)
#define _SCRAT_ALLOCATOR_H_

#include <squirrel.h>
#include <string.h>

#include "sqratObject.h"
#include "sqratTypes.h"

namespace Sqrat {

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @cond DEV
/// utility taken from http://stackoverflow.com/questions/2733377/is-there-a-way-to-test-whether-a-c-class-has-a-default-constructor-other-than/2770326#2770326
/// may be obsolete in C++ 11
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
class is_default_constructible {
    template<int x>
    class receive_size{};

    template< class U >
    static int sfinae( receive_size< sizeof U() > * );

    template< class U >
    static char sfinae( ... );

public:
    enum { value = sizeof( sfinae<T>(0) ) == sizeof(int) };
};
/// @endcond

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DefaultAllocator is the allocator to use for Class that can both be constructed and copied
///
/// \tparam C Type of class
///
/// \remarks
/// There is mechanisms defined in this class that allow the Class::Ctor method to work properly (e.g. iNew).
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class DefaultAllocator {

    template <class T, bool b>
    struct NewC
    {
        T* p;
        NewC()
        {
            p = new T();
        }
    };

    template <class T>
    struct NewC<T, false>
    {
        T* p;
        NewC()
        {
            p = 0;
        }
    };

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
        SetInstance(vm, 1, NewC<C, is_default_constructible<C>::value >().p);
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @cond DEV
    /// following iNew functions are used only if constructors are bound via Ctor() in Sqrat::Class (safe to ignore)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<class... Args, std::size_t... idx>
    static inline void iNew_Instance(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        SetInstance(vm, 1, new C(Var<Args>(vm, idx + 2).value...));
    }

    template <class... Args>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
            iNew_Instance<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    /// @endcond
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SetInstance(vm, idx, new C(*static_cast<const C*>(value)));
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NoConstructor is the allocator to use for Class that can NOT be constructed or copied
///
/// \tparam C Type of class
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class NoConstructor {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instance));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class (not allowed in this allocator)
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" constructing is not allowed"))).c_str());
#else
        SQUNUSED(vm);
        return 0;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type (not used in this allocator)
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SQUNUSED(vm);
        SQUNUSED(idx);
        SQUNUSED(value);
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" cloning is not allowed"))).c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CopyOnly is the allocator to use for Class that can be copied but not constructed
///
/// \tparam C Type of class
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class CopyOnly {
public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class (not allowed in this allocator)
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
#if !defined (SCRAT_NO_ERROR_CHECKING)
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" constructing is not allowed"))).c_str());
#else
        SQUNUSED(vm);
        return 0;
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SetInstance(vm, idx, new C(*static_cast<const C*>(value)));
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// NoCopy is the allocator to use for Class that can be constructed but not copied
///
/// \tparam C Type of class
///
/// \remarks
/// There is mechanisms defined in this class that allow the Class::Ctor method to work properly (e.g. iNew).
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class C>
class NoCopy {

    template <class T, bool b>
    struct NewC
    {
        T* p;
        NewC()
        {
           p = new T();
        }
    };

    template <class T>
    struct NewC<T, false>
    {
        T* p;
        NewC()
        {
           p = 0;
        }
    };

public:

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Associates a newly created instance with an object allocated with the new operator (which is automatically deleted)
    ///
    /// \param vm  VM that has an instance object of the correct type at idx
    /// \param idx Index of the stack that the instance object is at
    /// \param ptr Should be the return value from a call to the new operator
    ///
    /// \remarks
    /// This function should only need to be used when custom constructors are bound with Class::SquirrelFunc.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetInstance(HSQUIRRELVM vm, SQInteger idx, C* ptr)
    {
        ClassData<C>* cd = ClassType<C>::getClassData(vm);
        sq_setinstanceup(vm, idx, new std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >(ptr, cd->instances));
        sq_setreleasehook(vm, idx, &Delete);
        sq_getstackobj(vm, idx, &((*cd->instances)[ptr]));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up an instance on the stack for the template class
    ///
    /// \param vm VM that has an instance object of the correct type at position 1 in its stack
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger New(HSQUIRRELVM vm) {
        SetInstance(vm, 1, NewC<C, is_default_constructible<C>::value >().p);
        return 0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @cond DEV
    /// following iNew functions are used only if constructors are bound via Ctor() in Sqrat::Class (safe to ignore)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename... Args, std::size_t... idx>
    static inline void iNew_Instance(HSQUIRRELVM vm, std::index_sequence<idx...>) {
        SetInstance(vm, 1, new C(Var<Args>(vm, idx + 2).value...));
    }

    template <typename... Args>
    static SQInteger iNew(HSQUIRRELVM vm) {
        SQTRY()
            iNew_Instance<Args...>(vm, std::make_index_sequence<sizeof...(Args)>{});
            SQCATCH_NOEXCEPT(vm) {
                return sq_throwerror(vm, SQWHAT_NOEXCEPT(vm));
            }
        SQCATCH(vm) {
            return sq_throwerror(vm, SQWHAT(vm));
        }
        return 0;
    }
    /// @endcond

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to set up the instance at idx on the stack as a copy of a value of the same type (not used in this allocator)
    ///
    /// \param vm    VM that has an instance object of the correct type at idx
    /// \param idx   Index of the stack that the instance object is at
    /// \param value A pointer to data of the same type as the instance object
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Copy(HSQUIRRELVM vm, SQInteger idx, const void* value) {
        SQUNUSED(vm);
        SQUNUSED(idx);
        SQUNUSED(value);
        return sq_throwerror(vm, (ClassType<C>::ClassName() + string(_SC(" cloning is not allowed"))).c_str());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Called by Sqrat to delete an instance's data
    ///
    /// \param ptr  Pointer to the data contained by the instance
    /// \param size Size of the data contained by the instance
    ///
    /// \return Squirrel error code
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static SQInteger Delete(SQUserPointer ptr, SQInteger size) {
        SQUNUSED(size);
        std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >* instance = reinterpret_cast<std::pair<C*, SharedPtr<typename unordered_map<C*, HSQOBJECT>::type> >*>(ptr);
        instance->second->erase(instance->first);
        delete instance->first;
        delete instance;
        return 0;
    }
};

}

#endif
