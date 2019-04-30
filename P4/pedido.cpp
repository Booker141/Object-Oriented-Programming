#include "pedido.hpp"
#include <iomanip>

int Pedido::numero_pedidos = 1;

//CONSTRUCTOR DE PEDIDO

Pedido::Pedido(Usuario_Pedido& usuario_p, Pedido_Articulo& pedido_art, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha):numero_(numero_pedidos), tarjeta_pago(&tarjeta), fecha_pedido(fecha){

	if(usuario.compra().empty())
	
		throw Pedido::Vacio(&usuario);
		
	if(tarjeta.titular() != &usuario)
	
		throw Pedido::Impostor(&usuario);
		
	if(tarjeta.caducidad() < fecha)
	
		throw Tarjeta::Caducada(tarjeta.caducidad());
	
	auto carro = usuario.compra();
		
	for(auto iterador = carro.begin() ; iterador != carro.end() ; iterador ++) {

		if(ArticuloAlmacenable* ArtAlm = dynamic_cast<ArticuloAlmacenable*>(iterador->first)) {

			if(iterador->second > ArtAlm->stock()) {

				for(auto iterador = carro.begin() ; iterador != carro.end() ; iterador ++)
					usuario.compra(*iterador->first, 0);
				throw SinStock(iterador->first);
			}

		} else if(LibroDigital* LibDig = dynamic_cast<LibroDigital*>(iterador->first)) {

			if(LibDig->f_expir() < fecha)
				usuario.compra(*iterador->first, 0);
		}
	}

	if(usuario.compra().empty())
		throw Vacio(&usuario);

	usuario_p.asocia(*this, usuario);
	carro = usuario.compra();
	total_ = 0;
	for(auto iterador = carro.begin() ; iterador != carro.end() ; iterador ++) {

		total_ += iterador->first->precio() * iterador->second;
		pedido_art.pedir(*iterador->first, *this, iterador->first->precio(), iterador->second);
		if(ArticuloAlmacenable* ArtAlm = dynamic_cast<ArticuloAlmacenable*>(iterador->first))
			ArtAlm->stock() -= iterador->second;
	}

	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	numero_ =  numero_pedidos++;

}

//OPERADOR DE INSERCION

ostream& operator <<(ostream& os, const Pedido& pedido) {
	
	os << "Núm. pedido: " << pedido.numero() << endl;
	os << "Fecha:       " << pedido.fecha() << endl;
	os << "Pagado con:  " << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << endl;
	os << "Importe:     " << pedido.total() << " €";
	return os;
}


