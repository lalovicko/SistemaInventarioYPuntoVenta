#include "Prerequisites.h"
#include "Inventario.h"
#include "FactoryMethod/FactoriaProductos.h"

int main() {

    FactoriaProductos factory;
    Inventario inv;
    ObserverConcreto observer;
    inv.agregarObserver(&observer);

    int opcion;

    inv.CargarDesdeJson("data/productos.json");

    do {
        std::cout << std::endl << "===== SISTEMA DE INVENTARIO =====" << std::endl;
        std::cout << "1. Mostrar inventario" << std::endl;
        std::cout << "2. Vender producto" << std::endl;
        std::cout << "3. Comprar producto" << std::endl;
        std::cout << "4. Agregar nuevo producto" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {

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

    } while (opcion != 5);

    return 0;
}