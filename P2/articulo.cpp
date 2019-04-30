#include"articulo.hpp"

Articulo::Articulo(const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio, unsigned ejemplares): cod_ref(referencia), titulo_(titulo), fech_public(fecha), precio_(precio), num_ejem(ejemplares) {}

//OPERADOR DE INSERCIÓN

ostream& operator << (ostream& os, const Articulo& articulo) {

	os<<"["<<articulo.referencia()<<"]";
	os<<"\""<<articulo.titulo()<< "\".";
	os<<articulo.f_publi()<<".";
	os<<articulo.precio()<<"euros";
	return os;

}



