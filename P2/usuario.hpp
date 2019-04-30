#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include<map>
#include<unordered_map>
#include<unordered_set>
#include <unistd.h>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"


class Numero;

class Tarjeta;

class Clave{
	
	public:
		
		enum Razon{CORTA,ERROR_CRYPT};
		
		//CLASE DE EXCEPCIÓN: INCORRECTA

		class Incorrecta{
			public:
				
				Incorrecta(const Clave::Razon razon):razon_(razon){}
				Clave::Razon razon() const{return razon_;}
				
			private:
				Clave::Razon razon_;
		};
		
		//CONSTRUCTOR DE CLAVE

		Clave(const char* clave);

		//OBSERVADOR DE CLAVE

		Cadena clave() const {return cifrada_;}

		bool verifica(const char* claro) const;
		
		
	private:
		
		Cadena cifrada_;
		
};

class Usuario {

	public:
		
		//DEFINICIÓN DE TIPOS

		typedef map<Numero, Tarjeta*> Tarjetas;
		typedef unordered_map<Articulo* , unsigned int> Articulos;
		
		//CONSTRUCTOR DE USUARIO

		Usuario(const Cadena& identificador, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir_usuario, const Clave& contrasena);


		//CLASE DE EXCEPCIÓN: ID DUPLICADO

		class Id_duplicado {
			
			public:
				
				Id_duplicado(const Cadena& ident):ident_(ident){}
				Cadena idd() const{return ident_;}
				
			private:
				
				Cadena ident_;
		};

		//OBSERVADORES

		Cadena id() const {
			return identificador_;
		}
		Cadena nombre() const {
			return nombre_;
		}
		Cadena apellidos() const {
			return apellidos_;
		}
		Cadena direccion() const {
			return dir_usuario_;
		}
		const Tarjetas& tarjetas() const {
			return tarjetas_;
		}
		void es_titular_de(Tarjeta& tarjeta);
		void no_es_titular_de(Tarjeta& tarjeta);
		void compra(Articulo& articulo, const unsigned cant = 1);
		size_t n_articulos() const {
			return articulos_.size();
		}
		const Articulos& compra() const {
			return articulos_;
		}

		//OPERADORES DE INSERCIÓN

		friend ostream& operator<<(ostream& os, const Usuario& usuario);
		friend ostream& mostrar_carro(ostream& os, const Usuario& usuario);

		//DESTRUCTOR DE USUARIO

		~Usuario();
		
		//ELIMINACIÓN DEL CONSTRUCTOR DE COPIA Y OPERADOR DE ASIGNACIÓN
		Usuario(const Usuario& usuario) = delete;
		Usuario& operator =(const Usuario& usuario) = delete;

	private:

		Cadena identificador_, nombre_, apellidos_, dir_usuario_;
		Clave contrasena_;
		Articulos articulos_; 		//Tipo unordered_map
		Tarjetas tarjetas_;
		unordered_set<Cadena> registrados_ ;

};



#endif
