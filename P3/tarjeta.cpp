#include"tarjeta.hpp"

#include "tarjeta.hpp"
#include <cstring>
#include <iomanip>
#include<algorithm>


bool luhn(const Cadena& numero);

//CONSTRUCTOR DE TARJETA

Tarjeta::Tarjeta(Tarjeta::Tipo tipo, const Numero& numero, Usuario& titular, const Fecha& fecha_cad):
	tipo_(tipo), numero_(numero), titular_(&titular), fecha_cad_(fecha_cad) {
		
	Fecha hoy;
	
	if(fecha_cad < hoy)	throw Tarjeta::Caducada(fecha_cad);
	titular.es_titular_de(*this);
	nom_titular_ = titular.nombre();
	nom_titular_+= " ";
	nom_titular_ += titular.apellidos();
}


//OPERADOR DE INSERCION DE TAR

ostream& operator <<(ostream& os, const Tarjeta& tarjeta) {
	os << tarjeta.tipo() << endl;
	os << tarjeta.numero() << endl;
	os << tarjeta.titular_facial() << endl;
	os << "Caduca: " << setfill('0') << setw(2) << tarjeta.caducidad().mes() << "/" << tarjeta.caducidad().anno() % 100;
	return os;
}

//OPERADOR DE INSERCIÓN DE TIPO

ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo) {
	
	switch(tipo) {
		case Tarjeta::VISA:
			os << "VISA";
			break;
		case Tarjeta::Mastercard:
			os << "Mastercard";
			break;
		case Tarjeta::Maestro:
			os << "Maestro";
			break;
		case Tarjeta::JCB:
			os << "JCB";
			break;
		case Tarjeta::AmericanExpress:
			os << "AmericanExpress";
			break;
		default:
			os << "Error";
	}
	return os;
}

//OPERADOR <

bool operator <(const Tarjeta& t1, const Tarjeta& t2) {
	return t1.numero() < t2.numero();
}

//DESTRUCTOR

Tarjeta::~Tarjeta() {
	
	Usuario* usuario = const_cast<Usuario*>(titular_);
	
	if(usuario != nullptr)
	
		usuario->no_es_titular_de(*this);
		
}


bool luhn(const Cadena& numero);

bool EsBlanco::operator ()(char caracter) const {

	return isspace(caracter);

}
bool EsDigito::operator ()(char caracter) const {

	return isdigit(caracter);

}

//CONSTRUCTOR DE CADENA

Numero::Numero(const Cadena& cadena) {

	size_t tamano = cadena.length();
	char* aux = new char[tamano + 1];
	strcpy(aux, cadena.c_str());
	char* ini = aux;
	char* fin = aux + tamano;
	fin = remove_if(ini, fin, EsBlanco());
	*fin = '\0';
	tamano = strlen(aux);
	if(tamano < 13 || tamano > 19)

		throw Numero::Incorrecto(Numero::LONGITUD);

	if(find_if(ini, fin, not1(EsDigito())) != fin)

		throw Numero::Incorrecto(Numero::DIGITOS);

	if(!luhn(aux))

		throw Numero::Incorrecto(Numero::NO_VALIDO);

	numero_tr = aux;
	delete[] aux;
}

Numero::operator const char*() const {

	return numero_tr.c_str();

}

//OPERADOR <

bool operator <(const Numero& n1, const Numero& n2) {

	return strcmp(n1, n2) < 0;

}
