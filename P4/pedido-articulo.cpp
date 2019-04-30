#include "pedido-articulo.hpp"
#include <iomanip>

//OPERADOR LINEA PEDIDO

LineaPedido::LineaPedido(double precioV, unsigned cantidad): precioV_(precioV),
	cantidad_(cantidad) {}
	
//OPERADOR DE INSERCION

ostream& operator <<(ostream& os, const LineaPedido& LineaP) {
	os << fixed << setprecision(2) << LineaP.precio_venta() << " €\t" << LineaP.cantidad();
	return os;
}

bool OrdenaArticulos::operator()(Articulo* a1,  Articulo* a2) const {
	
	return a1->referencia() < a2->referencia();
	
}

bool OrdenaPedidos::operator()( Pedido* p1, Pedido* p2) const {
	
	return p1->numero() < p2->numero();
	
}

void Pedido_Articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad) {
	
	PedidoaArticulo[&pedido].insert(make_pair(&articulo, LineaPedido(precio, cantidad)));
	ArticuloaPedido[&articulo].insert(make_pair(&pedido, LineaPedido(precio, cantidad)));
	
}

void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad) {
	
	pedir(pedido, articulo, precio, cantidad);
	
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pedido) {
	
	return PedidoaArticulo.find(&pedido)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& articulo) {
	
	if(ArticuloaPedido.find(&articulo) == ArticuloaPedido.end()) {
		
		Pedido_Articulo::Pedidos vacio;
		return vacio;
		
	} else
	
		return ArticuloaPedido.find(&articulo)->second;
}

//OPERADOR MOSTRAR DETALLE PEDIDOS

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os){
	
	double precio = 0;
	
	map<Pedido*, Pedido_Articulo::ItemsPedido,
	    OrdenaPedidos>::const_iterator iter;
	    
	for(iter = PedidoaArticulo.begin() ; iter != PedidoaArticulo.end() ; iter ++) {
		
		os << "Pedido núm. " << iter->first->numero()<< endl;
		os << "\tCliente: " << iter->first->tarjeta()->titular()->nombre();
		os << "Fecha: " << iter->first->fecha() << "\n" << iter->second;
		precio = precio + iter->first->total();
	}
	os << fixed;
	os << "TOTAL VENTAS " << setprecision(2) << precio << " €" << endl;
	return os;
}

//OPERADOR MOSTRAR VENTAS ARTICULOS

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os){
	
	map<Articulo*, Pedido_Articulo::Pedidos, OrdenaArticulos>::const_iterator iterador;
	
	for(iterador = ArticuloaPedido.begin() ; iterador != ArticuloaPedido.end() ; iterador ++) {
		
		os << "Ventas de " << "[" << iterador->first->referencia() << "] ";
		os << "\"" << iterador->first->titulo() << "\" \n" << endl;
		os << iterador->second << endl;
		   
	}
	
	return os;
	
}

//OPERADOR DE INSERCION ITEMS PEDIDO

ostream& operator<<(ostream& os, const Pedido_Articulo::ItemsPedido& ItemsP) {
	
	double precio = 0;
	Pedido_Articulo::ItemsPedido::const_iterator i;
	os << "====================================================" << endl;
	os << " PVP \t Cantidad. \t Articulo \n";
	os << "====================================================" << endl;
	
	for(i = ItemsP.begin(); i != ItemsP.end(); ++i) {
		
		os << " " << i->second.precio_venta() << " €\t";
		os << i->second.cantidad() << "\t";
		os << "[" << i->first->referencia() << "] ";
		os << "\"" << i->first->titulo() << "\" " << endl;
		precio = precio + i->second.precio_venta() * i->second.cantidad();
		
	}
	
	os << "===================================================" << endl;
	os << fixed;
	os << "Total"<< setprecision(2) << precio << " €" << endl;
	return os;
}

//OPERADOR DE INSERCION PEDIDO

ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& pedido) {
	
	double precio = 0;
	unsigned total = 0;
	Pedido_Articulo::Pedidos::const_iterator i;

	os << "[Pedidos: " << pedido.size() << "]" << endl;
	os << "====================================================" << endl;
	os << " PVP \t Cant. \t Fecha venta \n";
	os << "====================================================" << endl;
	
	for(i = pedido.begin(); i != pedido.end(); ++i) {
		
		os << " " << i->second.precio_venta() << " €\t";
		os << i->second.cantidad() << "\t";
		os << i->first->fecha() << endl;
		precio = precio + i->second.precio_venta() * i->second.cantidad();
		total = total + i->second.cantidad();
	}
	
	os << "====================================================" << endl;
	os << fixed;
	os << setprecision(2) << precio << " €\t" << total <<endl ;
	return os;
	
}
