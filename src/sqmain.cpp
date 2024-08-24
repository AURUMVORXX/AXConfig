#include <sqapi.h>
#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

using namespace Gothic_II_Addon;

extern "C" SQRESULT SQRAT_API sqmodule_load(HSQUIRRELVM vm, HSQAPI api)
{
	SqModule::Initialize(vm, api);

	sq_throwerror(vm, str);

	return SQ_OK;
}
