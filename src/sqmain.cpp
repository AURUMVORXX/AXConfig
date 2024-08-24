#include <sqapi.h>
#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#include "sqfunc.h"

using namespace Gothic_II_Addon;

extern "C" SQRESULT SQRAT_API sqmodule_load(HSQUIRRELVM vm, HSQAPI api)
{
	SqModule::Initialize(vm, api);

	Sqrat::RootTable roottable(vm);

	roottable.SquirrelFunc("axc_readvalue", sq_axc_readvalue, -2, ".ss");
	roottable.SquirrelFunc("axc_writevalue", sq_axc_writevalue, -3, ".sss");

	return SQ_OK;
}
