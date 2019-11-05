#pragma once
#include "Grammar.h"

class Estado_Compilador {
public:
	int estadoChart = 0;
	Produccion* producRef;
	int PosAsterisco=0;
	int PosPalabra=0;
	Estado_Compilador* root;
	Estado_Compilador() {}
	Estado_Compilador(int s_cht, int ast_pos, int pal_pos, Produccion* ptr_p, Estado_Compilador* ptr_e);
	~Estado_Compilador() {}
};
//queue <Estado_Compilador*> chart;
vector<Estado_Compilador*> chart;

class Accion {
public:
	Gramatica* gramarSource;
	virtual bool sePuedeAplicar(Estado_Compilador* estado) = 0;
	virtual void aplica(Estado_Compilador* estado) = 0;//, queue<Estado_Compilador*> &chart) = 0;
};

class Dummy : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte);
	void aplica(Estado_Compilador* stte);// {//, queue<Estado_Compilador*> &chrt){
	Dummy(Estado_Compilador* state);
	~Dummy() {}
};

class Expandir : public Accion {
	bool sePuedeAplicar(Estado_Compilador* stte);
	void aplica(Estado_Compilador* stte);// {//, queue<Estado_Compilador*> &chrt){
	Expandir(Estado_Compilador* state);
	~Expandir() {}
};

class Aceptar : public Accion {
	bool sePuedeAplicar(Estado_Compilador* stte);
	void aplica(Estado_Compilador* stte);
	Aceptar(Estado_Compilador* state);
	~Aceptar() {}
};

class Unificar : public Accion {
	bool sePuedeAplicar(Estado_Compilador* stte);
	void aplica(Estado_Compilador* stte);
	Unificar(Estado_Compilador* state);
	~Unificar() {}
};