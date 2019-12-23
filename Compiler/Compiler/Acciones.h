#pragma once
#include "Grammar.h"

class Estado_Compilador {
public:
	int estadoChart = 0;
	Produccion* producRef;
	int PosAsterisco=0;
	int PosPalabra=0;
	int root;
	string acc;
	Estado_Compilador() {}
	Estado_Compilador(int s_cht, int ast_pos, int pal_pos, Produccion* ptr_p, int ptr_e, string acci);
	~Estado_Compilador() {}
};

class Accion {
public:
	Gramatica* gramarSource;
	virtual bool sePuedeAplicar(Estado_Compilador* estado, vector<Estado_Compilador>* chart) = 0;
	virtual void aplica(Estado_Compilador* estado, vector<Estado_Compilador>* chart) = 0;//, queue<Estado_Compilador*> &chart) = 0;
};

class Dummy : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* estado, vector<Estado_Compilador>* chart);
	void aplica(vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* estado, vector<Estado_Compilador>* chart){}
	Dummy() {}
	Dummy(Gramatica* gs) { gramarSource = gs; }
	~Dummy() {}
};

class Expandir : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte,vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte,vector<Estado_Compilador>* chart);
	Expandir(){}
	Expandir(Gramatica* gs) { gramarSource = gs; }
	~Expandir() {}
};

class Aceptar : public Accion {
public:
	vector<Token>* entrada;
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Aceptar(){}
	Aceptar(Gramatica* gs, vector<Token>* in) {
		gramarSource = gs;
		entrada = in;
	}
	~Aceptar() {}
};

class Unificar : public Accion {
public:
	vector<Token>* entrada;
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Unificar() { entrada = 0; }
	Unificar(Gramatica* gs, vector<Token>* in) {
		gramarSource = gs;
		entrada = in;
	}
	~Unificar() {}
};

class Completar : public Accion {
public:
	bool sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	void aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart);
	Completar(){}
	Completar(Gramatica* gs) { gramarSource = gs; }
	~Completar() {}
};