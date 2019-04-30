#ifndef _TARJETA_HPP_
#define _TARJETA_HPP_

#include"cadena.hpp"
#include"fecha.hpp"
#include"usuario.hpp"

class Usuario;

class Numero{
	
	public:
		
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
		
		//CLASE DE EXCEPCIÓN: INCORRECTO

		class Incorrecto{
			
			public:
				
				Incorrecto(Razon razon):razon_(razon){}
				Numero::Razon razon() const{return razon_;}
				
			private:
				
				Numero::Razon razon_;
			
			};
		
		//CONSTRUCTOR DE NUMERO

		Numero(const Cadena& cadena);

		operator const char*() const;
		friend bool operator < (const Numero& n1, const Numero& n2);
		
	private:

		Cadena numero_tr;
		
};


class Tarjeta{
	
	public:
		
		enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
		
		//CLASE DE EXCEPCIÓN: CADUCADA

		class Caducada{
			
			public:
			
				Caducada(const Fecha& fecha_caducada):fecha_caducada_(fecha_caducada){}
				Fecha cuando() const{return fecha_caducada_;}
			
			private:
				
				Fecha fecha_caducada_;
		};
		
		//CONSTRUCTOR DE TARJETA

		Tarjeta(Tipo tipo, const Numero& numero, Usuario& titular, const Fecha& fecha_cad);

		//ELIMINACIÓN DEL CONSTRUCTOR DE COPIA Y EL OPERADOR DE ASIGNACIÓN
		Tarjeta(const Tarjeta& tarjeta) = delete;
		Tarjeta& operator =(const Tarjeta& tarjeta) = delete;
		
		//OBSERVADORES
		
		Tipo tipo() const{return tipo_;}
		Numero numero() const{return numero_;}
		const Usuario* titular() const{return titular_;}
		Fecha caducidad() const{return fecha_cad_;}
		Cadena titular_facial() const{return nom_titular_;}	
		
		void anula_titular(){
			titular_ = nullptr;
		}
		
		//OPERADORES DE INSERCIÓN

		friend ostream& operator <<(ostream& os, const Tarjeta& tarjeta);
		friend ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo);
		friend bool operator <(const Tarjeta& t1, const Tarjeta& t2);
		
		//DESTRUCTOR
	
		~Tarjeta();
		
	private:
		
		Tipo tipo_;
		Numero numero_;
		const Usuario* titular_;
		Fecha fecha_cad_;
		Cadena nom_titular_;
	
	
	
};

#endif

