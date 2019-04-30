#include"articulo.hpp"
#include<iomanip>
#include<iostream>

//CONSTRUCTOR DE ARTICULO

Articulo::Articulo(const Autores& aut, const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio): cod_ref(referencia),   titulo_(titulo), fech_public(fecha), precio_(precio),autor(aut) {

if(autor.empty())
	throw Autores_vacios();

}

//OPERADOR DE INSERCION

ostream& operator << (ostream& os, const Articulo& articulo) {

 		
   os << "[" << setw(3) << setfill('0') << articulo.referencia() << "] \"" << articulo.titulo() << "\", de ";
   auto autor = articulo.autores().begin();

      os << (*autor)->apellidos();

    for(++autor; autor != articulo.autores().end(); ++autor)
       os << ", " << (*autor)->apellidos();

    os << ". ";

    os << articulo.f_publi().anno() << ". "<< fixed << setprecision(2) << articulo.precio() << " €\n";

    os << '\t';
    articulo.impresion_especifica(os);
	    
       return os; 

}



