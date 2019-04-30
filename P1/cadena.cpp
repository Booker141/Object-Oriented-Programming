#include "cadena.hpp"
#include "stdio.h"
#include <iomanip>
#include <stdlib.h>


using namespace std;

//IMPLEMENTACION CONSTRUCTORES

Cadena::Cadena(unsigned int tamano, char c):s_(new char[tamano + 1]), tam_(tamano){

	for(unsigned i=0; i<tamano; i++)

		s_[i] = c;

	s_[tamano] = '\0';

}

Cadena::Cadena(const Cadena& copia):s_(new char[copia.tam_ + 1]),tam_(copia.tam_){

	for (unsigned i=0; i<tam_; i++)

		s_[i]=copia.s_[i];

	s_[tam_] = '\0';

}

// CONSTRUCTOR DE MOVIMIENTO

Cadena::Cadena(Cadena&& cadena): s_(cadena.s_), tam_(cadena.tam_){

	cadena.tam_ = 0;
	cadena.s_ = nullptr;

}


Cadena::Cadena(const char* cadena): tam_(strlen(cadena)) {

	s_ = new char[tam_ + 1];
	strcpy(s_, cadena);

}

//OPERADORES

Cadena operator+=( Cadena& c1, const Cadena& c2){

	c1= c1 + c2;
	return c1;

}

Cadena operator+(const Cadena& c1,const Cadena& c2) {
	
	Cadena aux (c1.tam_ + c2.tam_);
	strcpy(aux.s_, c1.s_);
    	strcat(aux.s_,c2.s_);
   	return aux;

}

bool operator==(const Cadena& c1,const Cadena& c2) 
{
	unsigned i;

    if (c1.length() != c2.length())

    	return false;

    for (i=0; i<c1.length(); i++)

        if (c1[i] != c2[i])

        	return false;

    return true;
}

bool operator!=(const Cadena& c1,const Cadena& c2) {

	return !(c1 == c2);

}

bool operator<(const Cadena& c1,const Cadena& c2){

    return (strcmp(c1.s_,c2.s_)<0);

}


bool operator>(const Cadena& c1,const Cadena& c2){

	return (c2 < c1);

}

bool operator<=(const Cadena& c1,const Cadena& c2) {

	return !(c1 > c2);

}

bool operator>=(const Cadena& c1,const Cadena& c2){

	return !(c1 < c2);

}

Cadena& Cadena::operator=(const Cadena& cadena)
{
	if (this == &cadena)
		return *this;

	if (tam_ != cadena.tam_)
	{
        delete[] s_;

        tam_ = cadena.tam_;
        s_ = new char[tam_ + 1];
    }

	for(size_t i = 0; i < tam_; i++)
        	s_[i] = cadena.s_[i];

	s_[tam_] = '\0';

    return *this;
}

Cadena& Cadena::operator=(const char* caracter)
{
	if(tam_ != strlen(caracter))
	{
		delete[] s_;

		tam_ = strlen(caracter);

		s_ = new char[tam_ + 1];
	}

	strcpy(s_, caracter);

	return *this;
}

Cadena& Cadena::operator =(Cadena&& cadena)
{
  if(this!=&cadena){
    delete[] s_;

    tam_ = cadena.tam_;
    s_= cadena.s_;

    cadena.s_ = nullptr;
    cadena.tam_ = 0;
  }
  
    return *this;
}

char Cadena::operator[](size_t tamano) const noexcept{

	return s_[tamano];

}

char& Cadena::operator[](size_t tamano) noexcept{

	return s_[tamano];

}

ostream& operator<<(ostream& os,const Cadena& cadena)
{
	os << cadena.c_str();

	return os;
}

istream& operator>>(istream& is,  Cadena& cadena){
	
	char string[33] = { 0 };

	if(is >> ws >> setw(33) >> string)
		cadena = Cadena(string);
	else
		cadena = Cadena();
	return is;

}

char Cadena::at(unsigned long p) const
{
    if (p >= tam_) 
		throw out_of_range("No esta dentro del rango de tamano de la cadena.\n");

	return s_[p];
}

char& Cadena::at(unsigned long p)
{
    if (p >= tam_)
		throw out_of_range("No esta dentro del rango de tamano de la cadena.\n");

    return s_[p];
}

Cadena Cadena::substr(unsigned int indiceInic, unsigned int tamano) const{

	unsigned limite = indiceInic + tamano;
	
	if(indiceInic>tamano||limite<indiceInic||limite>tam_|| indiceInic> INT_MAX || tamano > INT_MAX)

		throw out_of_range("No esta dentro del rango.\n");

	else{

		Cadena auxiliar(tamano);

		for( unsigned int i = indiceInic; i< limite; i++)
			auxiliar.s_[i- indiceInic] = s_[i];
	
		return auxiliar;
	}
}


//DESTRUCTOR

Cadena::~Cadena(){

     delete[] s_;

}
