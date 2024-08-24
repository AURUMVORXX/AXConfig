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

#include <gtest/gtest.h>
#include <sqrat.h>
#include "Fixture.h"

using namespace Sqrat;

class Speaker {
public:
    int Echo() {
        return 0;
    }
    int Echo(int val) {
        return val;
    }
};

int GlobalEcho() {
    return 0;
}
int GlobalEcho(int val) {
    return val;
}


class StaticTestClass
{
public:
    static int i1, i2;
    
    static void set(int a1) { i1 = a1; }
    static void set(int a1, int a2) { i1 = a1; i2 = a2; }
    static int get_i1() { return i1; }
    static int get_i2() { return i2; }
};

int StaticTestClass::i1 = -1;
int StaticTestClass::i2 = -1;

TEST_F(SqratTest, OverloadedMemberFunction) {
    DefaultVM::Set(vm);

    // Member function overloads
    RootTable().Bind(_SC("Speaker"),
                     Class<Speaker>(vm, _SC("Speaker"))
                     .Overload<int (Speaker::*)()>(_SC("Echo"), &Speaker::Echo)
                     .Overload<int (Speaker::*)(int)>(_SC("Echo"), &Speaker::Echo)
                    );
    // static Member function overloads
    RootTable().Bind(_SC("StaticTestClass"),
                     Class<StaticTestClass>(vm, _SC("StaticTestClass"))
                     .StaticOverload<void (*)(int)>(_SC("set"), &StaticTestClass::set)
                     .StaticOverload<void (*)(int, int)>(_SC("set"), &StaticTestClass::set)
                     .StaticFunc(_SC("get_i1"), &StaticTestClass::get_i1)
                     .StaticFunc(_SC("get_i2"), &StaticTestClass::get_i2)
                     );

    // Global Function overloads
    RootTable().Overload<int (*)()>(_SC("GlobalEcho"), &GlobalEcho);
    RootTable().Overload<int (*)(int)>(_SC("GlobalEcho"), &GlobalEcho);

    Script script;
    script.CompileString(_SC(" \
        s <- Speaker(); \
        \
        gTest.EXPECT_INT_EQ(0, s.Echo()); \
        gTest.EXPECT_INT_EQ(1, s.Echo(1)); \
        gTest.EXPECT_INT_EQ(0, GlobalEcho()); \
        gTest.EXPECT_INT_EQ(1, GlobalEcho(1)); \
        "));
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Compile Failed: ") << Sqrat::Error::Message(vm);
    }

    script.Run();
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Run Failed: ") << Sqrat::Error::Message(vm);
    }

    script.CompileString(_SC(" \
        s <- StaticTestClass(); \
        \
        gTest.EXPECT_INT_EQ(-1, s.get_i1()); \
        gTest.EXPECT_INT_EQ(-1, s.get_i2()); \
        s.set(2); \
        gTest.EXPECT_INT_EQ(2, s.get_i1()); \
        gTest.EXPECT_INT_EQ(-1, s.get_i2()); \
        s.set(4, 6); \
        gTest.EXPECT_INT_EQ(4, s.get_i1()); \
        gTest.EXPECT_INT_EQ(6, s.get_i2()); \
        "));
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Compile Failed: ") << Sqrat::Error::Message(vm);
    }

    script.Run();
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Run Failed: ") << Sqrat::Error::Message(vm);
    }
}

//
// Overload test with const functions, based on scenario provided by emeyex
//

class Entity {
public:
    unsigned int QueryEnumValue( unsigned int enumKey, unsigned int enumValueDefault ) const {
        return enumKey;
    }
    unsigned int QueryEnumValue( unsigned int enumKey ) const {
        return QueryEnumValue( enumKey, 0 );
    }
};

TEST_F(SqratTest, ConstOverloadTest) {
    DefaultVM::Set(vm);

    // Member function overloads
    RootTable().Bind(_SC("Entity"),
                     Class<Entity>(vm, _SC("Entity"))
                     .Overload<unsigned int (Entity::*)(unsigned int, unsigned int) const>(_SC("QueryEnumValue"), &Entity::QueryEnumValue)
                     .Overload<unsigned int (Entity::*)(unsigned int) const>(_SC("QueryEnumValue"), &Entity::QueryEnumValue)
                    );

    Script script;
    script.CompileString(_SC(" \
        e <- Entity(); \
        \
        gTest.EXPECT_INT_EQ(1, e.QueryEnumValue(1, 0)); \
        gTest.EXPECT_INT_EQ(2, e.QueryEnumValue(2)); \
        "));
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Compile Failed: ") << Sqrat::Error::Message(vm);
    }

    script.Run();
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Run Failed: ") << Sqrat::Error::Message(vm);
    }
}



class D
{
private:
    int value;
public:
    D(): value(-1) {}
    
    int set(int v)
    {
        return value = v;
    }
    int get()
    {
        //std::cout << "B's address is " << (long) this << std::endl;
        return value;
    }
    
    static string shared;
    static int sharedInt;
};

    
static D& getD(D &d)
{
    return d;
}

static D& getD2(D* d, int, char *)
{
    return *d;
}

static D& getD4(D& d, D* , const D, int)
{
    return d;
}

static D* getDPtr(D *d)
{
    return d;
}

string D::shared ;
int D::sharedInt = -1;

TEST_F(SqratTest, FunctionReturningReferencesToClassesWithStaticMembers) {
    DefaultVM::Set(vm);

    Class<D> _D(vm, _SC("D"));
    _D
    .Func(_SC("set"), &D::set)
    .Func(_SC("get"), &D::get)
    .StaticVar(_SC("shared"), &D::shared)
    .StaticVar(_SC("sharedInt"), &D::sharedInt);
    
    RootTable().Bind(_SC("D"), _D);
    RootTable().Func(_SC("getD"), &getD);
    RootTable().Func(_SC("getD2"), &getD2);
    RootTable().Func(_SC("getD4"), &getD4);
    RootTable().Func(_SC("getDPtr"), &getDPtr);
    
    Script script;
    script.CompileString(_SC(" \
        d <- D();\
        dd <- D(); \
        \
        gTest.EXPECT_INT_EQ(d.get(), -1); \
        gTest.EXPECT_INT_EQ(dd.sharedInt, -1); \
        gTest.EXPECT_INT_EQ(d.sharedInt, -1); \
        d.set(12);\
        d.shared = \"a long string\"; \
        d.sharedInt = 1234; \
        gTest.EXPECT_STR_EQ(dd.shared, \"a long string\"); \
        gTest.EXPECT_STR_EQ(d.shared, \"a long string\"); \
        gTest.EXPECT_INT_EQ(dd.sharedInt, 1234); \
        gTest.EXPECT_INT_EQ(d.get(), 12); \
        local d1 = getDPtr(d);\
        d.set(20);\
        gTest.EXPECT_INT_EQ(d1.get(), 20); \
        local d2 = getD(d);\
        d.set(40);\
        gTest.EXPECT_INT_EQ(d1.get(), 40); \
        gTest.EXPECT_INT_EQ(d2.get(), 40); \
        local d3 = getD2(d, 12, \"test\");\
        d.set(60);\
        gTest.EXPECT_INT_EQ(d2.get(), 60); \
        gTest.EXPECT_INT_EQ(d3.get(), 60); \
        local d4 = getD4(d, d, d, 33);\
        d.set(80);\
        gTest.EXPECT_INT_EQ(d3.get(), 80); \
        gTest.EXPECT_INT_EQ(d4.get(), 80); \
        \
        dd.shared = \"short str\"; \
        gTest.EXPECT_STR_EQ(d2.shared, \"short str\"); \
        gTest.EXPECT_STR_EQ(d3.shared, \"short str\"); \
        gTest.EXPECT_STR_EQ(d.shared, \"short str\"); \
        gTest.EXPECT_STR_EQ(d1.shared, \"short str\"); \
        gTest.EXPECT_STR_EQ(d4.shared, \"short str\"); \
        gTest.EXPECT_INT_EQ(d.sharedInt, 1234); \
        gTest.EXPECT_INT_EQ(d1.sharedInt, 1234); \
        gTest.EXPECT_INT_EQ(d2.sharedInt, 1234); \
        gTest.EXPECT_INT_EQ(d3.sharedInt, 1234); \
        gTest.EXPECT_INT_EQ(d4.sharedInt, 1234); \
        d4.shared = \"abcde\"; \
        d4.sharedInt = 9999; \
        gTest.EXPECT_STR_EQ(dd.shared, \"abcde\"); \
        gTest.EXPECT_INT_EQ(dd.sharedInt, 9999); \
        gTest.EXPECT_INT_EQ(d1.sharedInt, 9999); \
        "));
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Compile Failed: ") << Sqrat::Error::Message(vm);
    }

    script.Run();
    if (Sqrat::Error::Occurred(vm)) {
        FAIL() << _SC("Run Failed: ") << Sqrat::Error::Message(vm);
    }
    
}

