#pragma once
#include "Prerequisites.h"

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void actualizar(const std::string& mensaje) = 0;
private:

};

class ObserverConcreto : public Observer
{
	public:
	void actualizar(const std::string& mensaje) override
	{
		std::cout << "[notificacion]" << mensaje << std::endl;
	}
};