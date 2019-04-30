#ifndef CADENA_HPP
#define CADENA_HPP

#include <stdexcept>
#include <iostream>
#include <cstring>




using namespace std;

class Cadena{

public:


	explicit Cadena(size_t tamano = 0, char c = ' ');
	Cadena(const Cadena& copia);
	Cadena(Cadena& cadena, size_t i, size_t tamano);
	Cadena(const char* cadena, size_t tamano);
	Cadena(const char* cadena);
	Cadena(Cadena&& cadena);

	const char* c_str() const { return s_; }
	size_t length() const { return tam_; }

    friend Cadena operator+=( Cadena& c1, Cadena& c2) ;
    friend Cadena operator+(const Cadena& c1,const Cadena& c2) ;

	friend bool operator==(const Cadena& c1,const Cadena& c2);
	friend bool operator!=(const Cadena& c1,const Cadena& c2);

	friend bool operator<(const Cadena& c1,const Cadena& c2);
	friend bool operator>(const Cadena& c1,const Cadena& c2);

	friend bool operator<=(const Cadena& c1,const Cadena& c2);
	friend bool operator>=(const Cadena& c1,const Cadena& c2);

	Cadena& operator=(const Cadena& s);
	Cadena& operator=(const char* c);


	char operator[](size_t tamano) const noexcept;
    char& operator[](size_t tamano) noexcept;
    
   friend istream& operator >>(istream& is, Cadena& cadena);
friend ostream& operator <<(ostream& os, const Cadena& cadena);
	
	char at(size_t p) const;
    char& at(size_t p);

    ~Cadena();
    
        typedef char* iterator;
	typedef char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        iterator begin() noexcept {return s_;}
	const_iterator cbegin() const noexcept { return s_; }
   	const_iterator begin() const { return s_; }

	iterator end() noexcept { return s_ + tam_; }
	const_iterator cend() const noexcept  { return s_ + tam_; }
	const_iterator end() const noexcept { return s_+ tam_; }

	const_reverse_iterator crbegin() const noexcept
	{ return reverse_iterator(end()); }

	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return crbegin(); }

	const_reverse_iterator crend() const noexcept
	{ return reverse_iterator(begin()); }

	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const noexcept { return crend(); }


    Cadena substr(unsigned int indiceInic, unsigned int tamano) const;

private:

	char* s_;
	size_t tam_;
};

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].

namespace std {
template <> struct hash<Cadena> {
size_t operator()(const Cadena& cad) const
{ // conversión const char* ->string
	return hash<string>{}(cad.c_str());
	}
 };
}


#endif
