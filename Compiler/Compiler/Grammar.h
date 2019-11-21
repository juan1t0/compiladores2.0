#pragma once
#include "Production.h"

struct Gramatica {
	string estadoInicial;
	vector<Produccion*> production;
	//set<string> terminales;
	//set<string> noterminales;
	map<string,bool> terminals;

	void read(string texto);
	void readContx(string texto);
	void readVarContx(string subtex,Token &toq);
	vector<Token>* readMoreProduc(string& subtex);///tokens de la derecha
	vector<Token>* readTerminals(string& subtex);
	vector<vector<string>> getProduction(string izq);
	void printGrammar();
	Gramatica() {}
	~Gramatica() {}

	Produccion* get_Production(int pos);
	void insertProduction(Produccion* xtr, int pos);

	void discrinator();
};
