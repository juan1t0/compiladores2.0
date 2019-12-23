#include "Production.h"

void DeteleFromString(string& s, char d) {
	string result;
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] == d)continue;
		result += s[i];
	}
	s = result;
}
template<class T>
void printMatrix(vector<vector<T>>& mat) {
	for (size_t i = 0; i < mat.size(); ++i) {
		for (size_t j = 0; j < mat[i].size(); ++j) {
			cout << mat[i][j] << '\t';
		}
		cout << endl;
	}
}

Token::Token(string nn){
	this->name = nn;
	this->var = new vector<string>;
	this->val = new vector<string>;
}

void Token::print() {
	cout << this->name;
	if (!(this->val->empty())) {
		cout << "< ";
		for (size_t i = 0; i < this->val->size(); ++i) {
			cout << this->var->at(i) << "-" << this->val->at(i) << " , ";
		}
		cout << " >";
	}
	cout << "\t";
}

string Produccion::toprint(int posterisco) {
	string R;
	R += nombre.name;
	R += " ::= ";
	int i;
	for (i = 0; i < der->size(); ++i) {
		if (i == posterisco) R += "(*)";
		R += der->at(i).name;
		R += " ";
	}
	if (i == posterisco) R += "(*)";
	return R;
}