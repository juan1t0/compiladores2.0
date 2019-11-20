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

class Accion {
public:
	Gramatica* gramarSource;
	virtual bool sePuedeAplicar(Estado_Compilador* estado, vector<Estado_Compilador>* chart) = 0;
	virtual void aplica(Estado_Compilador* estado, vector<Estado_Compilador>* chart) = 0;//, queue<Estado_Compilador*> &chart) = 0;
};

class Dummy : public Accion {
public:
	bool sePuedeAplicar();
	void aplica(vector<Estado_Compilador>* chart, Produccion* ini);// {//, queue<Estado_Compilador*> &chrt){
	Dummy(vector<Estado_Compilador>* chart, Produccion* ini);
	~Dummy() {}
};

class Expandir : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte,vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte,vector<Estado_Compilador>* chart);// {//, queue<Estado_Compilador*> &chrt){
	Expandir(){}
	~Expandir() {}
};

class Aceptar : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Aceptar(){}
	~Aceptar() {}
};

class Unificar : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Unificar(){}
	~Unificar() {}
};

class Completar : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Completar(){}
	~Completar() {}
};