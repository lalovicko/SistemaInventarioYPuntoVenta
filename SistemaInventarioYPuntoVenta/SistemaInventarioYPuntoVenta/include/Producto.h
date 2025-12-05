#pragma once
#include "Prerequisites.h"

class Producto
{

protected:
	std::string nombre;
	int precio;
	int cantidad;
	std::string codigo;
	int stockMinimo = 5; // Valor mínimo de stock antes de lanzar alerta
public:
	Producto(const std::string& _nombre, int _precio, int _cantidad, const std::string& _codigo)
		: nombre(_nombre), precio(_precio), cantidad(_cantidad), codigo(_codigo) { 	// Constructor del producto
	}
	~Producto() = default;

	void mostrarInfo() const { // Muestra la información completa del producto
		std::cout << "Nombre" << ": " << nombre << ", Precio: " << precio << ", Cantidad: " << cantidad << ", Codigo: " << codigo << std::endl;
	}	

	// Métodos getter
	std::string getNombre() const { 
		return nombre; 
	}
	int getPrecio() const { 
		return precio; 
	}

	int getCantidad() const { 
		return cantidad; 
	}

	std::string getCodigo() const { 
		return codigo; 
	}

	// Setter para actualizar cantidad
	int setCantidad(int nuevaCantidad) {
		cantidad = nuevaCantidad;
		return cantidad;
	}

	// Getter y Setter para stockMinimo
	int getStockMinimo() const { 
		return stockMinimo; 
	}

	void setStockMinimo(int minimo) { 
		stockMinimo = minimo; 
	}


};

