#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>

#define contex pair<string,string>

using namespace std;

void DeteleFromString(string& s, char d);

template<class T>
void printMatrix(vector<vector<T>>& mat);

struct Token {
	string name;
	vector<string>* var = 0;
	vector<string>* val = 0;

	Token() {}
	Token(string nn);
	~Token() {}

	void print();
};

class Produccion {
public:
	Token nombre;
	vector<Token>* der = 0;

	Produccion() {}
	Produccion(Token& s) : nombre(s) {}
	Produccion(Token& s, vector<Token>& vec) : nombre(s), der(new vector<Token>(vec)) {}

	string toprint(int posterisco);
};
/*
class SimpleProduc : public Produccion {
public:
	SimpleProduc(string& s, vector<string>& vec) : Produccion(s, vec) {}
};

class ContexProduc : public Produccion {
public:
	vector<contex>* contexto = 0;
	vector<Produccion>* derP = 0;
	ContexProduc(Produccion p);
	ContexProduc(string& name, vector<contex>& ctx);
	ContexProduc(string& name, vector<contex>& ctx, vector<string>& der);
	ContexProduc(string& name, vector<contex>& ctx, vector<Produccion>& derP);
};
*/