#include "sqapi.h"

namespace SqModule
{
	HSQUIRRELVM vm;
	HSQAPI api;

	void Initialize(HSQUIRRELVM vm, HSQAPI api) {
		SqModule::vm = vm;
		SqModule::api = api;

		Sqrat::DefaultVM::Set(vm);
	}

	void Print(const SQChar* msg) {
		const SQPRINTFUNCTION print = sq_getprintfunc(vm);
		print(vm, msg);
	}

	void Error(const SQChar* msg) {
		const SQPRINTFUNCTION error = sq_geterrorfunc(vm);
		error(vm, msg);
	}
}
