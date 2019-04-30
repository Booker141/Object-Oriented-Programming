#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"


class Articulo{
public:
	
	//CONSTRUCTOR

	Articulo(const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio, unsigned ejemplares);

	//OBSERVADORES

	Cadena referencia() const{return cod_ref;}
	Cadena titulo() const{return titulo_;}
	Fecha f_publi() const{return fech_public;}
	double& precio(){return precio_;}
	double precio() const{return precio_;}
	unsigned stock() const{return num_ejem;}
	unsigned& stock() {return num_ejem;}
	
	//OPERADOR DE INSERCIÓN

	friend ostream& operator<<(ostream& os,const Articulo& articulo);
	
private:

	Cadena cod_ref, titulo_;
	Fecha fech_public;
	double precio_;
	unsigned num_ejem;	
		
};

#endif
