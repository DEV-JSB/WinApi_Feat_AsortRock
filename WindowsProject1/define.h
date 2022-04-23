#pragma once

#include<Windows.h>

#define SINGLE(type) public:\
					static type* GetInst()\
					{\
					 	static type mgr;\
						return &mgr;\
					}