#ifndef _SQ_API_H_
#define _SQ_API_H_

#include <sqmodule.h>

namespace SqModule
{
	extern HSQUIRRELVM vm;
	extern HSQAPI api;

	void Initialize(HSQUIRRELVM vm, HSQAPI api);
	void Print(const SQChar* msg);
	void Error(const SQChar* msg);
}

#include "sqmacros.h"
#include <sqrat.h>

#endif