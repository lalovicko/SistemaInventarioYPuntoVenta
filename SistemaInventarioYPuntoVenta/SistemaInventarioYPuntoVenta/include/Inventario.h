#pragma once
#include "Prerequisites.h"
#include "json.hpp"
#include "Producto.h"
#include "Observer/Observer.h"
using json = nlohmann::json;

class Inventario
{
public:
	Inventario()  = default;
	void CargarDesdeJson(const std::string& rutaArchivo) {
		std::ifstream archivo(rutaArchivo);
		if (!archivo.is_open()) {
			std::cout << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
			return;
		}

		json data;
		archivo >> data;

		productos.clear();
		for (const auto& item : data) {
			Producto p(
				item["nombre"].get<std::string>(),
				item["precio"].get<double>(),
				item["cantidad"].get<int>(),
				item["codigo"].get<std::string>()
			);
			productos.push_back(p);
			notificarObservers("Producto cargado desde JSON: " + p.getNombre());
		}
		archivo.close();
		std::cout << "Inventario cargado desde " << rutaArchivo << std::endl;
	}

	void mostrarInventario() const {
		std::cout << "Inventario de Productos:" << std::endl;
		for (const auto& producto : productos) {
			producto.mostrarInfo();
		}
	}

	bool venderProducto(const std::string& codigo, int cantidad) {
		for (auto& producto : productos) {
			if (producto.getCodigo() == codigo) {
				if (producto.getCantidad() >= cantidad) {
					producto.setCantidad(producto.getCantidad() - cantidad);
					notificarObservers("Venta realizada: " + std::to_string(cantidad) + " unidades de " + producto.getNombre());

					if (producto.getCantidad() == 0)
						notificarObservers("Producto agotado: " + producto.getNombre());
					else if (producto.getCantidad() <= producto.getStockMinimo())
						notificarObservers("ALERTA: Stock bajo de " + producto.getNombre() + ". Quedan " + std::to_string(producto.getCantidad()) + " unidades.");

					return true;
				}
				else {
					notificarObservers("No hay suficiente stock de: " + producto.getNombre());
					return false;
				}
			}
		}
		notificarObservers("Producto con código " + codigo + " no encontrado.");
		return false;
	}

	void comprarProducto(const std::string& codigo, int cantidad) {
		for (auto& producto : productos) {
			if (producto.getCodigo() == codigo) {
				producto.setCantidad(producto.getCantidad()+cantidad);
				std::cout << "Compra realizada: " << cantidad << " unidades de " << producto.getNombre() << std::endl;
				return;
			}
		}
		std::cout << "Producto con codigo " << codigo << " no encontrado." << std::endl;
	}

	void agregarProducto(Producto producto) {
		productos.push_back(producto);
		std::cout << "Producto agregado: " << producto.getNombre() << std::endl;
	}

	void guardarEnJson(const std::string& rutaArchivo) const {
		json data = json::array();
		for (const auto& producto : productos) {
			data.push_back({
				{"nombre", producto.getNombre()},
				{"precio", producto.getPrecio()},
				{"cantidad", producto.getCantidad()},
				{"codigo", producto.getCodigo()}
			});
		}
		std::ofstream archivo(rutaArchivo);
		if (!archivo.is_open()) {
			std::cout << "No se pudo abrir el archivo para guardar: " << std::endl;
			return;
		}
		archivo << data.dump(4);
		archivo.close();
		std::cout << "Inventario guardado en " << rutaArchivo << std::endl;
	}

	void agregarObserver(Observer* observer) {
		observers.push_back(observer);
	}	

	void notificarObservers(const std::string& mensaje) {
		for (auto* observer : observers) {
			observer->actualizar(mensaje);
		}
	}

private:
	std::vector<Producto> productos;
	std::vector<Observer*> observers;
};

