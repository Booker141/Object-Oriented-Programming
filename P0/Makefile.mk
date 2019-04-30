CXX = g++
CPPFLAGS = -g -Wall -std=c++11 -pedantic -DP0 -I ../Tests-auto -I.
VPATH = ../Tests-auto:.

EXES = test-P0-auto test-P0-consola
OBJS_AUTO = cadena.o fecha.o test-auto.o test-caso0-fecha-auto.o test-caso0-cadena-auto.o
OBJS_CONS = cadena.o fecha.o test-P0-consola.o
OBJETOS = $(OBJS_AUTO) $(OBJS_CONS)

all: $(EXES)

test-P0-auto: $(OBJS_AUTO)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS_AUTO)

test-P0-consola: $(OBJS_CONS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS_CONS)

cadena.o: cadena.hpp
fecha.o: fecha.hpp
test-auto.o: test-auto.hpp fecha.hpp cadena.hpp
test-caso0-fecha-auto.o: test-auto.hpp fecha.hpp
test-caso0-cadena-auto.o: test-auto.hpp cadena.hpp
test-P0-consola.o: fecha.hpp cadena.hpp

clean: rm -f all $(OBJETOS)
