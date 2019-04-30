#include "fecha.hpp"

#include <cstdio>
#include<stddef.h>


using namespace std;

//OBSERVADORES

inline int Fecha::dia() const {return dia_;}
inline int Fecha::mes() const {return mes_;}
inline int Fecha::anno() const {return anno_;}

//IMPLEMENTACIÓN DE CONSTRUCTORES

time_t Fecha::Ssince1900() const noexcept
{
	tm ds = { 0 };

	ds.tm_year = anno_ - 1900;
	ds.tm_mon = mes_ - 1;
	ds.tm_mday = dia_;

	return mktime(&ds);
}

tm Fecha::fsince1900(int dias) const noexcept
{
	time_t segs = Ssince1900() + dias * 86400;

	return *localtime(&segs);
}

void Fecha::valida() const
{
	tm hoy = fsince1900();

	if (dia_ != hoy.tm_mday)
		throw Fecha::Invalida("Error en el dia.\n");

	if (mes_ != hoy.tm_mon + 1)
		throw Fecha::Invalida("Error en el mes.\n");

	if (anno_ != hoy.tm_year + 1900)
		throw Fecha::Invalida("Error en el ano.\n");

	if (anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
		throw Fecha::Invalida("Error de rango de ano\n");
}

Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a){

		if(d==0||m==0||a==0){

			time_t tiempo_cal = time(nullptr);
			tm* tiempo_desc = localtime(&tiempo_cal);

			if(d==0)
				dia_ = tiempo_desc->tm_mday;
			if(m==0)
				mes_ = tiempo_desc->tm_mon + 1;
			if(a==0)
				anno_ = tiempo_desc->tm_year + 1900;

 		}

	valida();

}


bool operator ==(const Fecha& f1,const Fecha& f2) {

	return (f1.dia()==f2.dia()&&f1.mes()==f2.mes()&&f1.anno()==f2.anno());

}

Fecha& Fecha::operator ++() {

	return (*this+=1);
}

Fecha Fecha::operator ++(const int){

	Fecha aux=*this;
	*this += 1;
	return aux;

}

Fecha& Fecha::operator --() {

	return (*this += -1);

}

Fecha Fecha::operator -- (const int i){

	Fecha aux = *this;
	*this += (-1);
	return aux;


}

Fecha Fecha::operator -( int i) const {

	Fecha aux;
	aux = *this;
	aux += -i;
	return aux;


}

//Operador+

Fecha Fecha::operator +( int i) const{

	Fecha aux = *this;
	aux += i;
	return aux;

}

//Operador +=

Fecha& Fecha::operator +=(const int i) {

	tm f = {};
	f.tm_mday = dia_ + i;
	f.tm_mon = mes_ - 1;
	f.tm_year = anno_ - 1900;

	mktime(&f);

	dia_ = f.tm_mday;
	mes_ = f.tm_mon + 1;
	anno_ = f.tm_year + 1900;

	valida();

	return *this;


}

//Operador-=

Fecha& Fecha::operator -=(const int i) {

	return (*this += -i);

}

//Operador <

bool operator <(const Fecha& f1,const Fecha& f2){

	bool menor = false;

	if(f1.anno()< f2.anno())
		menor = true;
	else if(f1.anno() == f2.anno()){
		if(f1.mes() < f2.mes())
			menor = true;
		else if(f1.mes() == f2.mes()){
			if(f1.dia() < f2.dia())
				menor = true;
		}
	}
	return menor;
}

//Operador >

bool operator >(const Fecha& f1,const Fecha& f2){

	return (f2<f1);
}

//Operador !=

bool operator !=(const Fecha& f1,const Fecha& f2){

	return !(f1==f2);

}

//Operador <=

bool operator <=(const Fecha& f1,const Fecha& f2){

	return (f1<f2||f1==f2);

}

//Operador >=

bool operator >=(const Fecha& f1,const Fecha& f2){

	return (f1>f2||f1==f2);

}

//Operador de extracción

istream& operator >>(istream& is, Fecha& fecha)
{
	char d[3], m[3], a[5] , b1, b2, cleaner[50];
	is.get(d,3,'/');
	is>>b1;
	is.get(m,3,'/');
	is>>b2;
	is.get(a,5);

	if(b1 != '/' || b2 != '/'){
		is.getline(cleaner,50);
		is.setstate(ios::failbit);
		throw Fecha::Invalida("El formato es invalido");
	}
	else{
		try{
			fecha = Fecha(atoi(d), atoi(m), atoi(a));
		}
		catch (const Fecha::Invalida& e){
			is.setstate(ios::failbit);
			throw;
		}
	}
	return is;
}

//Operador de inserción

ostream& operator <<(ostream& os, const Fecha& fecha)
{
	os << fecha.cadena();
	return os;
}

// Conversión formato

Fecha::Fecha(const char *formato) {


	time_t tiempo_cal = time(nullptr);
	tm* tiempo_descompuesto = localtime(&tiempo_cal);

	int dia,mes,ano;

	if((3==(sscanf(formato,"%d/%d/%d",&dia,&mes,&ano)))){

		dia_= dia;
		mes_ = mes;
		anno_= ano;
			if(dia_ == 0)
				dia_=tiempo_descompuesto->tm_mday;
			if(mes_ == 0)
				mes_=tiempo_descompuesto->tm_mon+1;
			if(anno_ == 0)
				anno_=tiempo_descompuesto->tm_year+1900;

		valida();
	}
	else{

		throw Fecha::Invalida("Error en la conversion de fecha a cadena.");
	}

}

//Conversión cadena

const char* Fecha::cadena() const {

	char* cadena = new char[50];
	setlocale(LC_TIME, "");
	tm fecha = {};
	fecha.tm_mday = dia_;
	fecha.tm_mon = mes_ - 1;
	fecha.tm_year = anno_ - 1900;
	mktime(&fecha);

	valida();

	strftime(cadena,50, "%A %d de %B de %Y", &fecha);
	return cadena;

}

// Por que

const char* Fecha::Invalida::por_que() const{
	return s;
}
