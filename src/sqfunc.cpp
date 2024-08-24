
#include <sqapi.h>
#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>
#include <string>

#include "sqfunc.h"

using Gothic_II_Addon::zSTRING, Gothic_II_Addon::zoptions;

static std::string currentSection{ "G2O" };

SQInteger sq_axc_readvalue(HSQUIRRELVM vm)
{
	const SQChar* param;
	const SQChar* section{ currentSection.c_str()};

	sq_getstring(vm, 2, &param);

	if (sq_gettop(vm) == 3 && sq_gettype(vm, 3) == OT_STRING)
		sq_getstring(vm, 3, &section);

	zSTRING value = zoptions->ReadString(section, param, "");

	sq_pushstring(vm, value, -1);

	return 1;
};

SQInteger sq_axc_writevalue(HSQUIRRELVM vm)
{
	const SQChar* param;
	const SQChar* value;
	const SQChar* section{ currentSection.c_str() };

	sq_getstring(vm, 2, &param);
	sq_getstring(vm, 3, &value);

	if(sq_gettop(vm) == 4 && sq_gettype(vm, 4) == OT_STRING)
		sq_getstring(vm, 4, &section);

	int result = zoptions->WriteString(section, param, value, FALSE);

	sq_pushbool(vm, bool(result));

	return 1;
};

SQInteger sq_axc_setsection(HSQUIRRELVM vm)
{
	const SQChar* value;

	sq_getstring(vm, 2, &value);

	currentSection = value;

	return 1;
};

SQInteger sq_axc_getsection(HSQUIRRELVM vm)
{
	sq_pushstring(vm, currentSection.c_str(), -1);
	return 1;
};