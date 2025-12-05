#include "Prerequisites.h"
#include "Inventario.h"
#include "FactoryMethod/FactoriaProductos.h"
#include "Ventas.h"
#include "Facade/GasolineraFacade.h"

int main() {

    FactoriaProductos factory;
    Inventario inv;
    ObserverConcreto observer;
    SistemaVender ventas(inv);
	GasolineraFacade gasolinera;
    inv.agregarObserver(&observer);
    std::string cont = "Churros";
    int posicion;
    int opcionInv;
    int opCliente;

    inv.CargarDesdeJson("data/productos.json");

    std::cout << "Bienvenido al sistema de la gasolineria Churro's, eliga una opcion: " << std::endl;
    std::cout << "1-Cliente" << std::endl;
    std::cout << "2-Empleado" << std::endl;
    std::cin >> posicion;
    if (posicion == 1) {
        do {
            std::cout << "===== MENU CLIENTE =====" << std::endl;
            std::cout << "1. Ver productos disponibles" << std::endl;
            std::cout << "2. Comprar un producto" << std::endl;
            std::cout << "3. Recargar gasolina" << std::endl;
            std::cout << "4. Salir" << std::endl;
            std::cin >> opCliente;
            switch (opCliente) {
            case 1:
                inv.mostrarInventario();
                break;
            case 2:
                ventas.vender();
                break;

            case 3:
				gasolinera.venderGasolina();

            }
        } while (opCliente != 4);
    }

    else if (posicion == 2) {
        std::cout << "Por favor ingrese la contraseña" << std::endl;
		std::cin >> cont;
        if (cont == "Churros") {
            do {
                std::cout << std::endl << "===== SISTEMA DE INVENTARIO =====" << std::endl;
                std::cout << "1. Mostrar inventario" << std::endl;
                std::cout << "2. Vender producto" << std::endl;
                std::cout << "3. Comprar producto" << std::endl;
                std::cout << "4. Agregar nuevo producto" << std::endl;
                std::cout << "5. Salir" << std::endl;
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionInv;

                switch (opcionInv) {

                case 1:
                    std::cout << std::endl;
                    inv.mostrarInventario();
                    break;

                case 2: {
                    std::string codigo;
                    int cantidad;
                    std::cout << "Codigo del producto: ";
                    std::cin >> codigo;
                    std::cout << "Cantidad a vender: ";
                    std::cin >> cantidad;

                    inv.venderProducto(codigo, cantidad);
                    inv.guardarEnJson("data/productos.json");
                    std::cout << "Venta guardada automaticamente." << std::endl;
                } break;

                case 3: {
                    std::string codigo;
                    int cantidad;
                    std::cout << "Codigo del producto: ";
                    std::cin >> codigo;
                    std::cout << "Cantidad a ingresar: ";
                    std::cin >> cantidad;

                    inv.comprarProducto(codigo, cantidad);
                    inv.guardarEnJson("data/productos.json");
                    std::cout << "Compra guardada automaticamente." << std::endl;
                } break;

                case 4: {
                    std::string nombre, codigo;
                    double precio;
                    int cantidad;

                    std::cout << "Nombre del producto: ";
                    std::cin.ignore();
                    std::getline(std::cin, nombre);

                    std::cout << "Precio: ";
                    std::cin >> precio;
                    std::cout << "Cantidad inicial: ";
                    std::cin >> cantidad;
                    std::cout << "Codigo unico del producto: ";
                    std::cin >> codigo;

                    Producto nuevo = factory.crearProducto(nombre, precio, cantidad, codigo);
                    inv.agregarProducto(nuevo);
                    inv.guardarEnJson("data/productos.json");

                    std::cout << "Producto agregado y guardado automaticamente." << std::endl;
                } break;


                case 5:
                    std::cout << "Saliendo del sistema..." << std::endl;
                    break;

                default:
                    std::cout << "Opcion invalida." << std::endl;
                }

            } while (opcionInv != 5);
  
        }
        else {
            std::cout << "Contraseña incorrecta" << std::endl;
		}
    }


    return 0;
}