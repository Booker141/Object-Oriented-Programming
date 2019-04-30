#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
#include<set>
#include<iostream>
using namespace std;

class Autor{

public:

    //CONSTRUCTOR AUTOR

    Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept: nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

    //OBSERVADORES

    const Cadena& nombre() const noexcept { return nombre_; }
    const Cadena& apellidos() const noexcept { return apellidos_; }
    const Cadena& direccion() const noexcept { return direccion_; }

private:

    Cadena nombre_, apellidos_, direccion_;

};

class Articulo{

public:
	
	//DEFINICION DE TIPO

	typedef set<Autor*> Autores;

	//Clase de excepcion Autores_vacios

	class Autores_vacios{};

	//CONSTRUCTOR DE ARTICULO

	Articulo(const Autores& autor, const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio);

	//OBSERVADORES

	const Cadena& referencia() const{return cod_ref;}
	const Cadena& titulo() const{return titulo_;}
	const Fecha& f_publi() const{return fech_public;}
	const Autores& autores() const { return autor;}

	double precio() const noexcept{return precio_;}
	double& precio() noexcept{return precio_;}
	
	//DESTRUCTOR

	virtual ~Articulo(){}

	//OPERADORES DE INSERCION

	virtual void impresion_especifica(ostream& os) const noexcept = 0;
	
private:

	Cadena cod_ref, titulo_;
	Fecha fech_public;
	double precio_;
	Autores autor;
		
		
};

ostream& operator <<(ostream& os, const Articulo& articulo);

class ArticuloAlmacenable : public Articulo{

public:

    //CONSTRUCTOR DE ARTICULO ALMACENABLE

    ArticuloAlmacenable(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned stock=0): Articulo(autor, referencia, titulo, fecha, precio), stock_(stock) {}

    //OBSERVADORES

    unsigned stock() const noexcept { return stock_; }
    unsigned& stock() noexcept { return stock_;}

protected:

    unsigned stock_;

};

class Libro : public ArticuloAlmacenable{

public:

    //CONSTRUCTOR DE LIBRO

    Libro(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned numPag, unsigned stock=0): ArticuloAlmacenable(autor, referencia, titulo, fecha, precio, stock), num_pag(numPag) {}

    //OBSERVADOR

    unsigned n_pag() const noexcept { return num_pag; }
    void impresion_especifica(ostream& os) const noexcept;

private:

    const unsigned num_pag;

};

class Cederron : public ArticuloAlmacenable{

public:

   //CONSTRUCTOR DE CEDERRON

  Cederron(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned MB, unsigned stock): ArticuloAlmacenable(autor, referencia, titulo, fecha, precio, stock), tamano(MB) {}
  
   //OBSERVADOR

  unsigned tam() const noexcept { return tamano; }
  void impresion_especifica(ostream& os) const noexcept;

private:

   unsigned tamano;

};

class LibroDigital : public Articulo{

public:

    //CONSTRUCTOR DE LIBRO DIGITAL

    LibroDigital(const Autores& autor, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& fechaExp): Articulo(autor, referencia, titulo, fecha, precio), fecha_expiracion(fechaExp) {}

     //OBSERVADOR

    const Fecha& f_expir() const noexcept { return fecha_expiracion; }
   void impresion_especifica(ostream& os) const noexcept;

private:

    const Fecha fecha_expiracion;

};

inline void Libro::impresion_especifica(ostream& os) const noexcept{

    os << num_pag << " págs., " << stock_ << " unidades.";

}

inline void Cederron::impresion_especifica(ostream& os) const noexcept{

    os << tamano << " MB, " << stock_ << " unidades.";

}

inline void LibroDigital::impresion_especifica(ostream& os) const noexcept{

    os  << "A la venta hasta el " << fecha_expiracion << '.';

}



#endif
