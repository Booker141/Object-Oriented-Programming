#ifndef _FECHA_HPP_
#define _FECHA_HPP_

#include <iostream>
#include <ctime>
#include <stdexcept>

using namespace std;


class Fecha{

	public:

//EXCEPCIÓN

		class Invalida{
			public:

			Invalida(char *cadena){};
			const char* por_que() const;

			private:
			const char* s;
		};

		static const int AnnoMinimo = 1902;
		static const int AnnoMaximo = 2037;

//CONSTRUCTORES

		explicit Fecha(int d=0, int m=0, int a=0);
		Fecha(int d, int m);
		explicit Fecha(int d);

//OPERADORES

		Fecha& operator =(const Fecha& c);
		friend bool operator ==(const Fecha& f1, const Fecha& f2);

		//PREINCREMENTO

		Fecha& operator ++();

		//POSTINCREMENTO

		Fecha operator ++(const int);

		//PREDECREMENTO

		Fecha& operator --();

		//POSTDECREMENTO

		Fecha operator --(const int);

		friend Fecha operator -( Fecha& fecha,  int i) ;
		friend long operator - (const Fecha& f1, const Fecha& f2);
		friend Fecha operator +(Fecha& fecha, int i);
		Fecha& operator +=(const int i);
		Fecha& operator -=(const int i);
		
		
		friend bool operator <(const Fecha& f1,const Fecha& f2);
		friend bool operator >(const Fecha& f1,const Fecha& f2);
		friend bool operator !=(const Fecha& f1,const Fecha& f2);
		friend bool operator <=(const Fecha& f1,const Fecha& f2);
		friend bool operator >=(const Fecha& f1,const Fecha& f2);
		
		friend istream& operator >>(istream& is, Fecha& fecha);
		friend ostream& operator <<(ostream& os, const Fecha& fecha);

		Fecha(Fecha& c);
		Fecha(char* formato);
		const char* cadena() const;
		

//OBSERVADORES

		int dia() const;
		int mes() const;
		int anno() const;

	private:

		time_t Ssince1900() const noexcept;
		tm fsince1900(int dias = 0) const noexcept;

		void valida() const;
		int dia_, mes_, anno_;

};

#endif

