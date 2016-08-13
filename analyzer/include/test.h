// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef TEST_H
#define TEST_H

#include "analyzer_global.h"
#include "single_task.h"
#include "Matrix.h"


class __declspec(dllexport) Test
{
public:
	Test();
	~Test();

    // method for access from python
	static void hello(const char* fileName);

};

//class ANALYZERSHARED_EXPORT Test;

#endif // TEST_H
