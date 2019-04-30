#include "cadena.hpp"
#include "stdio.h"
#include <iomanip>
#include <stdlib.h>


using namespace std;

//IMPLEMENTACION CONSTRUCTORES

Cadena::Cadena(size_t tamano, char c){

	unsigned i;

	for(i=0; i<tamano; i++)

		s_[i] = c;

	s_[tamano] = '\0';

}

Cadena::Cadena(const Cadena& copia){

	unsigned i;

	for (i=0; i<tam_; i++)

		s_[i]=copia.s_[i];

	s_[tam_] = '\0';

}


//OPERADORES

Cadena operator+=( Cadena& c1, Cadena& c2){

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

istream& operator>>(istream& is,Cadena& cadena){
	
	char string[33], word[33];
	size_t i = 0, j = 0;
	is >> string;
	
	if (is)
	{
		while (string[i] == ' ')
			i++;
		while (string[i] != ' ' && string[i] != '\0')
		{
			word[j] = string[i];
			i++; j++;
		}
		word[j+1] = '\0';
		cadena = word;
	}
	return is;
	
	
}

char Cadena::at(size_t p) const
{
    if (p >= tam_||p<0) 
		throw out_of_range("No esta dentro del rango de tamaño de la cadena.\n");

	return s_[p];
}

char& Cadena::at(size_t p)
{
    if (p >= tam_||p<0)
		throw out_of_range("No esta dentro del rango de tamaño de la cadena.\n");

    return s_[p];
}

Cadena Cadena::substr(unsigned int indiceInic, unsigned int tamano) const{
	
	Cadena auxiliar(tamano);
	unsigned limite = indiceInic + tamano;
	
	if(indiceInic>tamano||limite<indiceInic||limite>tamano)
		throw out_of_range("No esta dentro del rango.\n");
	
	return auxiliar;
	
}


//DESTRUCTOR

Cadena::~Cadena(){

     delete[] s_;

}
