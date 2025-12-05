#pragma once
#include "Prerequisites.h"
#include "IPagosStrategy.h"

class PagoTarjeta : public IPagosStrategy
{
public:
	PagoTarjeta() = default;
	~PagoTarjeta() = default;
   
    bool pagar(double total) override {
        std::string numero;
		std::cout << "Ingrese numero de tarjeta: " << std::endl;
        std::cin >> numero;

        std::cout << "Procesando pago con tarjeta" << std::endl;
        return true;
    }
};