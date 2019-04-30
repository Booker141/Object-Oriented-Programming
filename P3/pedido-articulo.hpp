#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include "pedido.hpp"
#include "articulo.hpp"

class Articulo;
class Pedido;

using namespace std;

class LineaPedido {

	public:
		
		//CONSTRUCTOR DE LINEA PEDIDO

		explicit LineaPedido(const double precioV, const unsigned cantidad = 1);

		//OBSERVADORES

		double  precio_venta() const{return precioV_;}
		unsigned  cantidad() const{return cantidad_;}
	
		
	private:
		
		double precioV_;
		unsigned cantidad_;
		
};

//OPERADOR DE INSERCIÓN

ostream& operator <<(ostream& os, const LineaPedido& LP);

//CLASE ORDENA PEDIDOS

class OrdenaPedidos: public binary_function<Pedido*, Pedido*, bool> {
	
	public:
		
		bool operator()(Pedido* p1,  Pedido* p2) const;
		
};

//CLASE ORDENA ARTICULOS

class OrdenaArticulos: public binary_function<Articulo*, Articulo*,bool> {
	
	public:
		
		bool operator()( Articulo* a1, Articulo* a2) const;
		
};

class Pedido_Articulo {
	
	public:
		
		//DEFINICION DE TIPOS

		typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

		void pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad = 1);
		void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad = 1);
		ItemsPedido& detalle(Pedido& pedido);
		Pedidos ventas(Articulo& articulo);

		//OPERADORES

		ostream& mostrarDetallePedidos(ostream& os) const;
		ostream& mostrarVentasArticulos(ostream& os) const;
		
		
	private:
		
		map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoaArticulo;
		map<Articulo*, Pedidos, OrdenaArticulos> ArticuloaPedido;
		
};
	//OPERADORES DE INSERCION

	 ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& ItemsP);
	 ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& pedido);

#endif
