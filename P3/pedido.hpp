#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_

#include<iostream>

#include "tarjeta.hpp"
#include "fecha.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"


class Tarjeta;
class Usuario_Pedido;
class Pedido_Articulo;



class Pedido{
	
	public:
		

		//CONSTRUCTOR DE PEDIDO

		Pedido(Usuario_Pedido& usuario_p, Pedido_Articulo& pedido_art, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha = Fecha());
		
		//CLASE DE EXCEPCIÓN: VACIO

		class Vacio{
			
			public:
				
				Vacio(Usuario* usuario):usuario_(usuario){}
				Usuario const& usuario() const{return *usuario_;}
				
			private:
				
				Usuario* usuario_;
				
		};
		
		//CLASE DE EXCEPCIÓN: IMPOSTOR

		class Impostor{
			
			public:
				
				Impostor(Usuario* usuario):usuario_(usuario){}
				Usuario const& usuario() const{return *usuario_;}
	
			private:
				
				Usuario* usuario_;
				
		};
		
		//CLASE DE EXCEPCIÓN: SINSTOCK

		class SinStock{
			
			public:
				
				SinStock(Articulo* articulo):articulo_(articulo){}
				Articulo const& articulo() const {return *articulo_;}
					
			private:
				
				Articulo* articulo_;
			
		};
		
		//OBSERVADORES

		unsigned numero() const{return numero_;}
		Tarjeta const* tarjeta() const { return tarjeta_pago;}
		Fecha fecha() const {return fecha_pedido;}
		double total() const{return total_;}
		static unsigned n_total_pedidos() {return numero_pedidos;}

		//OPERADOR DE INSERCIÓN

		friend ostream& operator <<(ostream& os, const Pedido& pedido);		
		
			
	private:
		
		unsigned numero_;
		const Tarjeta* tarjeta_pago;
		Fecha fecha_pedido;
		double total_;
		static unsigned numero_pedidos;
		
};

#endif
