#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <sstream>
#include <queue>
#include <set>
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
