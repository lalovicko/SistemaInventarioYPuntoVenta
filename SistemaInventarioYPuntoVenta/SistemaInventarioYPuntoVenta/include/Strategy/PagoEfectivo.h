#pragma once
#include "Prerequisites.h"
#include "IPagosStrategy.h"

class PagoEfectivo : public IPagosStrategy
{
public:
	PagoEfectivo()  = default;
	~PagoEfectivo() = default;

	bool pagar(double monto) override {
		double recibido;
		std::cout << "Ingrese el monto en efectivo: " << std::endl;
		std::cin >> recibido;
		if (recibido >= monto) {
			double cambio = recibido - monto;
			std::cout << "Pago exitoso. Su cambio es: " << cambio << std::endl;
			return true;
		} else {
			std::cout << "Monto insuficiente. Pago fallido." << std::endl;
			return false;
		}
	}
};
