#include"usuario.hpp"
#include<iomanip>

unordered_set<Cadena> Usuario::registrados_;

//CONSTRUCTOR DE USUARIO

Usuario::Usuario(const Cadena& identificador, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir_usuario, const Clave& contrasena):
	identificador_(identificador), nombre_(nombre), apellidos_(apellidos), dir_usuario_(dir_usuario), contrasena_(contrasena) {

	if((Usuario::registrados_.insert(identificador)).second == false) 
		throw Usuario::Id_duplicado(identificador);

}

void Usuario::es_titular_de(Tarjeta& tarjeta) {
	
	if(this == tarjeta.titular())
	
		tarjetas_.insert(make_pair(tarjeta.numero(), &tarjeta));
}
void Usuario::no_es_titular_de(Tarjeta& tarjeta) {

	tarjetas_.erase(tarjeta.numero());
	
}

//DESTRUCTOR

Usuario::~Usuario() {
	
	Usuario::Tarjetas::iterator iterador = tarjetas_.begin();
	while(iterador != tarjetas_.end()){

		iterador->second->anula_titular();
		iterador++;

	}
	
	Usuario::registrados_.erase(identificador_);
	
}

void Usuario::compra(Articulo& articulo, unsigned cant) {
	
	if(cant != 0)
		articulos_[&articulo] = cant;
	else
		articulos_.erase(&articulo);
		
}

//MÉTODO INSERCIÓN

ostream& operator <<(ostream& os, const Usuario& usuario) {
	
	os << usuario.id() << " [" << usuario.contrasena_.clave().c_str() << "] " << usuario.nombre() << " " << usuario.apellidos() << endl;
	os << usuario.direccion() << endl;
	os << "Tarjetas: " << endl;
	Usuario::Tarjetas::const_iterator iterador = usuario.tarjetas().begin();
	while(iterador != usuario.tarjetas().end()) {
		os << *iterador->second << endl;
		iterador ++;
	}
	return os;
}

//OPERADOR MOSTRAR_CARRO: INSERCIÓN DE FLUJO

ostream& mostrar_carro(ostream& os, const Usuario& usuario) {
	
	os << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << endl;
	os << " Cant. Artículo" << endl;
	os << "==================================================" << endl;
	
	for(auto iterador = usuario.compra().begin(); iterador != usuario.compra().end(); iterador++){
		if( iterador != usuario.compra().begin())
			os << "\n";
		
		os << setw(4) << iterador->second << "   " << "[" << iterador->first->referencia() << "] \"" << iterador->first->titulo() << "\", " << iterador->first->f_publi().anno() << ". " << fixed << setprecision(2) << iterador->first->precio() << " €" << endl;
	}

	return os;
 
}

//CONSTRUCTOR DE CLAVE

Clave::Clave(const char *clave) {
	
	if(strlen(clave)< 5) 
		throw Clave::Incorrecta(Clave::CORTA);
	const char* caracteres = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char salt[3];
	salt[0] = caracteres[rand() % 62];
	salt[1] = caracteres[rand() % 62];
	salt[2] = '\0';
	if(crypt(clave, salt) == NULL) throw Clave::Incorrecta(Clave::ERROR_CRYPT);
	cifrada_ = crypt(clave, salt);
}

bool Clave::verifica(const char* claro) const {
	return strcmp(crypt(claro, cifrada_.c_str()), cifrada_.c_str()) == 0;
}



