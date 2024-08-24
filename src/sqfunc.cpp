
#include <sqapi.h>
#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#include "sqfunc.h"

using Gothic_II_Addon::zSTRING, Gothic_II_Addon::zoptions;

SQInteger sq_axc_readvalue(HSQUIRRELVM vm)
{
	const SQChar* param;
	const SQChar* section;

	sq_getstring(vm, 2, &param);
	sq_getstring(vm, 3, &section);

	zSTRING value = zoptions->ReadString(section, param, "");

	sq_pushstring(vm, value, -1);

	return 1;
};

SQInteger sq_axc_writevalue(HSQUIRRELVM vm)
{
	const SQChar* param;
	const SQChar* value;
	const SQChar* section;

	sq_getstring(vm, 2, &param);
	sq_getstring(vm, 3, &value);
	sq_getstring(vm, 4, &section);

	int result = zoptions->WriteString(section, param, value, FALSE);

	sq_pushbool(vm, bool(result));

	return 1;
};