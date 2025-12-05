#pragma once
#include "Prerequisites.h"
#include "Strategy/IPagosStrategy.h"
#include "Strategy/PagoEfectivo.h"
#include "Strategy/PagoTarjeta.h"

class Gasolinera
{
private:
    double precioMagna = 23.0;
    double precioPremium = 25.5;
    double precioDiesel = 24.0;

public:
    double calcularMonto(double litros, const std::string& tipo) {
        if (tipo == "magna")   return litros * precioMagna;
        if (tipo == "premium") return litros * precioPremium;
        if (tipo == "diesel")  return litros * precioDiesel;
        return 0.0;
    }

    void vender() {
        std::string correo;
        std::string tipo;
        double litros;
        int metodo;

        std::cout << "Favor de ingresar correo electronico:" << std::endl;
        std::cin >> correo;

        std::cout << "Litros a cargar:" << std::endl;
        std::cin >> litros;

        std::cout << "Tipo (magna/premium/diesel):" << std::endl;
        std::cin >> tipo;

        // Ahora sí, calcula el total
        double total = calcularMonto(litros, tipo);
        std::cout << "Total a pagar: $" << total << std::endl;

        std::cout << "Metodo de pago (1 efectivo, 2 tarjeta):" << std::endl;
        std::cin >> metodo;

        IPagosStrategy* pago = nullptr;

        if (metodo == 1) pago = new PagoEfectivo();
        else if (metodo == 2) pago = new PagoTarjeta();
        else {
            std::cout << "Metodo invalido." << std::endl;
            return;
        }

        if (!pago->pagar(total)) {
            std::cout << "Pago rechazado." << std::endl;
            delete pago;
            return;
        }

        // Crear ticket
        std::ofstream ticket("ticket_gasolina.txt");

        ticket << "====== TICKET DE GASOLINA ======" << std::endl;
        ticket << "Correo: " << correo << std::endl;
        ticket << "Tipo de combustible: " << tipo << std::endl;
        ticket << "Litros cargados: " << litros << std::endl;
        ticket << "Total pagado: $" << total << std::endl;
        ticket << "Metodo de pago: " << (metodo == 1 ? "Efectivo" : "Tarjeta") << std::endl;
        ticket << "Fecha: " << __DATE__ << " " << __TIME__ << std::endl;

        ticket.close();

        std::cout << "Ticket generado (ticket_gasolina.txt)" << std::endl;
        std::cout << "Ticket enviado al correo: " << correo << std::endl;

        delete pago;
    }
};
