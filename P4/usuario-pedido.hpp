#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include "usuario.hpp"
#include "pedido.hpp"

#include <set>
#include <map>

class Pedido;
class Usuario;

class Usuario_Pedido {
	
	public:
		
		//DEFINICION DE TIPO

		typedef set<Pedido*> Pedidos;

		void asocia(Usuario& usuario, Pedido& pedido);
		void asocia(Pedido& pedido, Usuario& usuario);
		Pedidos& pedidos(Usuario& usuario);
		Usuario* cliente(Pedido& pedido);
		
	private:
		
		map<Usuario*, Pedidos> UsuarioP;
		map<Pedido*, Usuario*> PedidoU;
};

inline void Usuario_Pedido::asocia(Usuario& usuario, Pedido& pedido) {
	
	UsuarioP[&usuario].insert(&pedido);
	PedidoU[&pedido] = &usuario;
	
}

inline void Usuario_Pedido::asocia(Pedido& pedido, Usuario& usuario) {
	
	asocia(usuario, pedido);
	
}

inline Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& usuario) {
	
	return UsuarioP.find(&usuario)->second;
	
}

inline Usuario* Usuario_Pedido::cliente(Pedido& pedido) {
	
	return PedidoU.find(&pedido)->second;
	
}

#endif