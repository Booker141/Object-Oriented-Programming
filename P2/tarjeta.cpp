#include "tarjeta.hpp"
#include <cstring>
#include <iomanip>


bool luhn(const Cadena& numero);

//CONSTRUCTOR

Tarjeta::Tarjeta( Tarjeta::Tipo tipo, const Numero& numero,  Usuario& titular, const Fecha& fecha_cad):
	tipo_(tipo), numero_(numero), titular_(&titular), fecha_cad_(fecha_cad) {
		
	Fecha hoy;
	
	if(fecha_cad < hoy)	throw Tarjeta::Caducada(fecha_cad);
	titular.es_titular_de(*this);
	nom_titular_ = titular.nombre();
	nom_titular_ += " ";
	nom_titular_+= titular.apellidos();
}

//OPERADOR DE INSERCIÓN: TARJETA

ostream& operator <<(ostream& os, const Tarjeta& tarjeta) {
	os << tarjeta.tipo() << endl;
	os << tarjeta.numero() << endl;
	os << tarjeta.titular_facial() << endl;
	os << "Caduca: " << setfill('0') << setw(2) << tarjeta.caducidad().mes() << "/" << tarjeta.caducidad().anno() % 100;
	return os;
}

//OPERADOR DE INSERCIÓN: TIPO

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

//CONSTRUCTOR DE NUMERO

Numero::Numero(const Cadena& cadena) {

	unsigned digitos=0;
	Cadena::const_iterator iterador = cadena.begin();

	while(iterador != cadena.end()){

		if(*iterador!= ' '){

			if(*iterador < 48 || *iterador > 57)
				throw Numero::Incorrecto(Numero::DIGITOS);

			else

				digitos++;

		}

		iterador++;

	}
	
	if(digitos < 13 || digitos>19)
		throw Numero::Incorrecto(Numero::LONGITUD);

	char* numero = new char[digitos];
	unsigned i = 0;
	iterador = cadena.begin();

	while(iterador != cadena.end()){

		if(*iterador != ' '){

			numero[i] = *iterador;
			i++;

		}

		iterador++;

	}

	if(!luhn(numero))
		throw Numero::Incorrecto(Numero::NO_VALIDO);

	numero_tr = numero;
	delete[] numero;

}

Numero::operator const char*() const {

	return numero_tr.c_str();

}

//OPERADOR <

bool operator <(const Numero& n1, const Numero& n2) {

	return strcmp(n1, n2) < 0;

}
