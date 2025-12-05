#pragma once
#include "Prerequisites.h"

class 
	IPagosStrategy{
public:
	virtual ~IPagosStrategy() = default;

	virtual bool pagar(double monto) = 0;

};

