#pragma once
#include "Prerequisites.h"
#include "Producto.h"

class FactoriaProductos
{
public:
	Producto crearProducto(const std::string& nombre, double precio, int cantidad, const std::string& codigo) {
		return Producto(nombre, precio, cantidad, codigo); // Crear y retornar un objeto Producto
	}
};

