#include "Prerequisites.h"
#include "Inventario.h"
#include "FactoryMethod/FactoriaProductos.h"
int main() {

    FactoriaProductos factory;
    Inventario inv;
	ObserverConcreto observer;
	inv.agregarObserver(&observer);

    inv.CargarDesdeJson("data/productos.json");
    inv.mostrarInventario();

	inv.venderProducto("LP1001", 2);
	inv.comprarProducto("MS2002", 5);
	Producto nuevoProducto = factory.crearProducto("Laptop Gamer", 1500.00, 10, "LP1002");
	inv.agregarProducto(nuevoProducto);
	inv.mostrarInventario();

    return 0;
}