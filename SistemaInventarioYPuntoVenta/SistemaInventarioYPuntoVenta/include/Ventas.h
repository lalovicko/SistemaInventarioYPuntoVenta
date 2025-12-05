#pragma once
#include "Prerequisites.h"
#include "Inventario.h"
#include "Strategy/IPagosStrategy.h"
#include "Strategy/PagoEfectivo.h"
#include "Strategy/PagoTarjeta.h"

class SistemaVender
{

public:
    SistemaVender(Inventario& inv) : inventario(inv) {}

    void vender() {
        std::string codigo;
        int cantidad;
        std::string correo;
		std::cout << "Favor de ingresar correo electronico" << std::endl;
		std::cin >> correo;
        std::cout << "Codigo del producto: " << std::endl;
        std::cin >> codigo;
        std::cout << "Cantidad a comprar: " << std::endl;
        std::cin >> cantidad;

        // Buscar producto
        Producto* prod = inventario.buscarProducto(codigo);
        if (!prod) {
            std::cout << "Producto no encontrado." << std::endl;
            return;
        }

        double total = prod->getPrecio() * cantidad;
        std::cout << "Total a pagar: $" << total << std::endl << std::endl;

        // Elegir método de pago
        int metodo;
        std::cout << "Metodo de pago:" << std::endl;
        std::cout << "1. Efectivo" << std::endl;
        std::cout << "2. Tarjeta" << std::endl;
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

        // Actualizar inventario
        inventario.venderProducto(codigo, cantidad);

        // Generar ticket
        std::ofstream ticket("ticket.txt");

        ticket << "====== TICKET DE COMPRA ======" << std::endl;
        ticket << "Producto: " << prod->getNombre() << std::endl;
        ticket << "Cantidad: " << cantidad << std::endl;
        ticket << "Total pagado: $" << total << std::endl;
        ticket << "Metodo de pago: " << (metodo == 1 ? "Efectivo" : "Tarjeta") << std::endl;
        ticket << "Fecha: " << __DATE__ << " " << __TIME__ << std::endl;

        ticket.close();

		std::cout << "Ticket enviado a " << correo << std::endl;

        delete pago;
    }

private:
    Inventario& inventario;

};
