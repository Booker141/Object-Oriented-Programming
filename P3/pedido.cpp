#include "pedido.hpp"
#include <iomanip>

unsigned Pedido::numero_pedidos = 0;

//CONSTRUCTOR DE PEDIDO

Pedido::Pedido(Usuario_Pedido& usuario_p, Pedido_Articulo& pedido_art, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha): tarjeta_pago(&tarjeta), fecha_pedido(fecha) {

	if(usuario.compra().empty())
	
		throw Pedido::Vacio(&usuario);
		
	if(tarjeta.titular() != &usuario)
	
		throw Pedido::Impostor(&usuario);
		
	if(tarjeta.caducidad() < fecha)
	
		throw Tarjeta::Caducada(tarjeta.caducidad());
		
	for(Usuario::Articulos::const_iterator iter = usuario.compra().begin(); iter != usuario.compra().end() ; iter ++) {
		
		if(iter->second > iter->first->stock()) {
			const_cast<Usuario::Articulos&>(usuario.compra()).clear();
			throw Pedido::SinStock(iter->first);
			
		}
	}
	
	usuario_p.asocia(*this, usuario);
	total_ = 0;
	for(Usuario::Articulos::const_iterator iter = usuario.compra().begin(); iter != usuario.compra().end() ; iter ++) {
		
		total_ += iter->second * iter->first->precio();
		pedido_art.pedir(*iter->first, *this, iter->first->precio(), iter->second);
		
		iter->first->stock() -= iter->second;
	}
	
	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	numero_ = ++ numero_pedidos;
}

//OPERADOR DE INSERCIÓN
ostream& operator <<(ostream& os, const Pedido& pedido) {
	
	os << "Num. pedido: " << pedido.numero() << endl;
	os << "Fecha: " << pedido.fecha() << endl;
	os << "Pagado con: " << *pedido.tarjeta() << endl;
	os << "Importe: " << fixed << setprecision(2) << pedido.total()
	   << " euros";
	return os;
}


