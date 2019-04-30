#include "fecha.hpp"

#include <cstdio>


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

	time_t tiempo_cal = time(nullptr);
	tm* tiempo_desc = localtime(&tiempo_cal);

		if(d==0||m==0||a==0){

			if(d==0)
				d = tiempo_desc->tm_mday;
			if(m==0)
				m = tiempo_desc->tm_mon + 1;
			if(a==0)
				a = tiempo_desc->tm_year + 1900;

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

Fecha operator -( Fecha& fecha, int i) {


	Fecha aux = fecha;
	aux += -i;
	return aux;


}

long operator -( const Fecha& f1, const Fecha& f2){

	tm F1 = {};
	tm F2 = {};
	F1.tm_mday = f1.dia();
	F1.tm_mon = f1.mes() - 1;
	F1.tm_year = f1.anno() - 1900;
	F2.tm_mday = f2.dia();
	F2.tm_mon = f2.mes() - 1;
	F2.tm_year = f2.anno() -1900;
	long dias = (long) difftime(mktime (&F1), mktime (&F2)) / (24*60*60);
	return dias;

}

Fecha operator +(Fecha& fecha, int i) {

	Fecha aux = fecha;
	aux += i;
	return aux;

}

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

Fecha& Fecha::operator -=(const int i) {

	return (*this += -i);

}

bool operator <(const Fecha& f1,const Fecha& f2){

	if(f1.anno_<f2.anno_||(f1.anno_==f2.anno_&&f1.mes_==f2.mes_&&f1.dia_<f2.dia_)||(f1.anno_==f2.anno_&&f1.mes_<f2.mes_&&f1.dia_!=f2.dia_))

		return true;
	else
		return false;

}

bool operator >(const Fecha& f1,const Fecha& f2){

	return (f1>f2);
}

bool operator !=(const Fecha& f1,const Fecha& f2){

	return !(f1==f2);

}

bool operator <=(const Fecha& f1,const Fecha& f2){

	return (f1<f2||f1==f2);

}

bool operator >=(const Fecha& f1,const Fecha& f2){

	return (f1>f2||f1==f2);

}

istream& operator >>(istream& is, Fecha& fecha)
{
	char* format = new char[11];
	is >> format;
	if (is.fail())
		throw Fecha::Invalida("El formato de fecha introducido es mas extenso de lo esperado.");
	if (format[2] != '/' || format[5] != '/'){
		is.setstate(ios::failbit);
		throw Fecha::Invalida("El formato de fecha introducido es invalido.");
	}
	fecha = Fecha(format);
	delete[] format;
	fecha.valida();
	
	return is;
}

ostream& operator <<(ostream& os, const Fecha& fecha)
{
	os << fecha.cadena();
	return os;
}

Fecha::Fecha(char *formato) {


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

		throw Fecha::Invalida("Error en la conversión de fecha a cadena");
	}

}

const char* Fecha::cadena() const {

	char* cadena = new char[40];
	setlocale(LC_TIME, "");
	tm fecha = {};
	fecha.tm_mday = dia_;
	fecha.tm_mon = mes_ - 1;
	fecha.tm_year = anno_ - 1900;
	mktime(&fecha);
	strftime(cadena, 40, "%A %d de %B de %Y", &fecha);

	return cadena;
}

const char* Fecha::Invalida::por_que() const{
	return s;
}
