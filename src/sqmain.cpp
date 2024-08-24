#include <sqapi.h>
#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#include "sqfunc.h"

using namespace Gothic_II_Addon;

extern "C" SQRESULT SQRAT_API sqmodule_load(HSQUIRRELVM vm, HSQAPI api)
{
	SqModule::Initialize(vm, api);

	Sqrat::RootTable roottable(vm);

	roottable.SquirrelFunc("axc_readvalue", sq_axc_readvalue, -2, ".s.");
	roottable.SquirrelFunc("axc_writevalue", sq_axc_writevalue, -3, ".ss.");
	roottable.SquirrelFunc("axc_getsection", sq_axc_getsection, 1, ".");
	roottable.SquirrelFunc("axc_setsection", sq_axc_setsection, -1, ".s");

	return SQ_OK;
}
