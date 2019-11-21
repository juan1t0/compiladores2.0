#include "Grammar.h"

void Gramatica::read(string texto) {
	if (texto.find("=?")) {
		readContx(texto);
		return;
	}
	string t1 = texto.substr(0, texto.find(":="));
	DeteleFromString(t1, ' ');
	Token temp1(t1);
	string temp2 = texto.substr(texto.find(":=") + 2, texto.length() - 1);
	stringstream ss(temp2);
	string token;
	while (getline(ss, token, '|')) {
		vector<Token> der;
		stringstream ss2(token);
		string token2;
		while (ss2 >> token2) {
			Token temp(token2);
			der.push_back(temp);
			terminals[temp.name] = 1;
		}
		Produccion* temp = new Produccion(temp1, der);
		production.push_back(temp);
	}
	discrinator();
}
void Gramatica::readContx(string texto) {
	int separe = texto.find(":=");
	string nameIZQ = texto.substr(0, texto.find("["));
	DeteleFromString(nameIZQ, ' ');
	Token nn(nameIZQ);
	readVarContx(texto.substr(texto.find("[") + 1, separe - texto.find("[") - 1), nn);
	for (int i = 0; i < nn.val->size(); ++i) {
		bool aux = true;
		for (int j = 0; j < contescto->size(); ++j) {
			if (contescto->at(j).first == nn.var->at(i))
				aux = false;
		}
		if(aux)
			contescto->push_back(make_pair(nn.var->at(i),nn.val->at(i)));
	}
	string dere = texto.substr(separe + 2);

	Produccion* ctp = new Produccion(nn);
	if (dere.find("?_") != string::npos) {
		vector<Token> *to_der = readMoreProduc(dere);
		ctp->der = to_der;
	}
	else {
		vector<Token> *to_der = readTerminals(dere);
		ctp->der = to_der;
	}
	production.push_back(ctp);
	discrinator();
}
void Gramatica::readVarContx(string subtex,Token &toq) {
	DeteleFromString(subtex, ']');
	stringstream Saux(subtex);
	string temp;
	vector<string> *vari = new vector<string>;
	vector<string> *vals = new vector<string>;
	while (getline(Saux, temp, ',')) {
		vari->push_back(temp.substr(0, temp.find("=")));
		vals->push_back(temp.substr(temp.find("=") + 1));
	}
	toq.var = vari;
	toq.val = vals;
}
vector<Token>* Gramatica::readMoreProduc(string& subtex) {
	stringstream Saux(subtex);
	string temp;
	vector<Token> *otherProd = new vector<Token>;
	while (Saux >> temp) {
		string nameIZQ = temp.substr(0, temp.find("["));
		Token nn(nameIZQ);
		readVarContx(temp.substr(temp.find("[") + 1),nn);
		otherProd->push_back(nn);
		terminals[nn.name] = 1;
		//			production.push_back(& otherProd[otherProd.size()-1]);
	}
	return otherProd;
}
vector<Token>* Gramatica::readTerminals(string& subtex) {
	stringstream Saux(subtex);
	string temp;
	vector<Token>* terminls = new vector<Token>;
	while (Saux >> temp) {
		terminls->push_back(Token(temp));
		terminals[temp] = 1;
	}
	return terminls;
}
vector<vector<string>> Gramatica::getProduction(string izq) {
	vector<vector<string>> result;
	for (size_t i = 0; i < production.size(); ++i) {
		if (production[i]->nombre.name == izq) {
			if (production[i]->der) {
				vector<string> t;
				for (size_t j = 0; j < production[i]->der->size(); ++j) {
					t.push_back(production[i]->der->at(j).name);
				}
				result.push_back(t);
			}
			else {
				vector<string> temp;
				Produccion* a = production[i];
				for (int j = 0; j < a->der->size(); j++) {
					string te = a->der->at(j).name;
					temp.push_back(te);
				}
				result.push_back(temp);
			}
		}
	}
	return result;
}
void Gramatica::printGrammar() {
	for (size_t i = 0; i < production.size(); ++i) {
		production[i]->nombre.print();
		for (size_t j = 0; j < production[i]->der->size(); ++j) {
			production[i]->der->at(j).print();
		}
		printf("\n");
	}
	printf("contx:\n");
	for (size_t i = 0; i < contescto->size(); ++i) {
		string uno = contescto->at(i).first, dos = contescto->at(i).second;
		printf("- %s ::= %s\n",uno.c_str(),dos.c_str());
	}
}
	
Produccion* Gramatica::get_Production(int pos) {
	return (production[pos]);
}
void Gramatica::insertProduction(Produccion* xtr, int pos) {
	production.insert(production.begin() + pos, xtr);
}

void Gramatica::discrinator() {
	for (int i = 0; i < production.size(); ++i) {
		terminals[production[i]->nombre.name] = 0;
	}
	//for (map<string, bool >::const_iterator it = terminals.begin(); it != terminals.end(); ++it){
	//	std::cout << it->first << " " << it->second << "\n";
	//}
}