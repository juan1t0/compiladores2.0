#include "Acciones.h"

Estado_Compilador::Estado_Compilador(int s_cht, int ast_pos, int pal_pos, Produccion* ptr_p, int ptr_e, string acci) {
	this->estadoChart = s_cht;
	this->PosAsterisco = ast_pos;
	this->PosPalabra = pal_pos;
	this->producRef = ptr_p;
	this->root = ptr_e;
	this->acc = acci;
}

bool Dummy::sePuedeAplicar(Estado_Compilador* estado, vector<Estado_Compilador>* chart) {
	return true; 
}
void Dummy::aplica(vector<Estado_Compilador>* chart) {
	Produccion* fist = gramarSource->get_Production(0);
	vector<Token> v;
	v.push_back(fist->nombre);
	string na = "S";
	Token nn(na);
	Produccion* temp = new Produccion(nn,v);
	Estado_Compilador* tt= new Estado_Compilador;
	tt->acc = "dummy";
	tt->PosAsterisco = 0;
	tt->PosPalabra = 0;
	tt->producRef = temp;
	tt->root = 0;
	gramarSource->production.insert((gramarSource->production.begin()), temp);
	chart->push_back(*tt);
}

bool Expandir::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	if (stte->PosAsterisco == stte->producRef->der->size())
		return false;
	string tokeni = (stte->producRef->der->at(stte->PosAsterisco)).name;
	return !(gramarSource->terminals[tokeni]);
}
void Expandir::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	size_t sizz = gramarSource->production.size();
	string nn = (stte->producRef->der->at(stte->PosAsterisco)).name;
	int pp = stte->PosPalabra;
	for (size_t i = 0; i < sizz; ++i) {
		if (gramarSource->production[i]->nombre.name == nn) {
			Estado_Compilador* EC = new Estado_Compilador;
			EC->producRef = gramarSource->production[i];
			EC->PosAsterisco = 0;
			EC->PosPalabra = pp;
			EC->root = 0;
			EC->acc = "expan";
			chart->push_back(*EC);
		}
	}
}

bool Aceptar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	if (stte->PosAsterisco == stte->producRef->der->size())
		return false;
	string nametemp = (stte->producRef->der->at(stte->PosAsterisco)).name;
	if (gramarSource->terminals[nametemp]) {
		Unificar t(gramarSource, entrada);
		return t.sePuedeAplicar(stte,chart);
	}
	return 0;
}
void Aceptar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	bool err=false;
	for (int i = 0; i < stte->producRef->nombre.var->size(); ++i) {
		err = false;
		string cur_var = stte->producRef->nombre.var->at(i), cur_val = stte->producRef->nombre.val->at(i);
		for (int j = 0; j < gramarSource->contescto->size(); ++j) {
			if (gramarSource->contescto->at(j).first == cur_var) {
				if (gramarSource->contescto->at(j).second == "?_") {
					gramarSource->contescto->at(j).second = cur_val;
					break;
				}
				else if (gramarSource->contescto->at(j).second == cur_val) {
					break;
				}
				err = true; 
				break;
			}
		}
		if (err)break;
	}
	if (err) {
		cout<<"ENTRADA NO RECONOCIDA"<<endl;
		return;
	}
	Estado_Compilador* neo = new Estado_Compilador;
	neo->acc = "acept";
	neo->PosAsterisco = stte->PosAsterisco + 1;
	neo->PosPalabra = stte->PosPalabra + 1;
	neo->producRef = stte->producRef;
	chart->push_back(*neo);
}

bool Unificar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	int palpos = stte->PosPalabra;
	int riscoPos = stte->PosAsterisco;
	string u1= stte->producRef->der->at(riscoPos).name, u2= entrada->at(palpos).name;
	if (stte->producRef->der->at(riscoPos).name == entrada->at(palpos).name) {
		return 1;
	}
	return 0;
}
void Unificar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	
}

bool Completar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	int posterisco = stte->PosAsterisco;
	int sise=-1;
	try
	{
		sise = stte->producRef->der->size();
	}
	catch (const std::exception&)
	{
		cout << "nan" << endl;
	}
	if (posterisco == sise)
		return 1;
	else return 0;
}
void Completar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	int sz = chart->size();
	Token aceT = stte->producRef->nombre;
	for (int i = 0; i < sz; ++i) {
		Estado_Compilador* aux = &(chart->at(i));
		if (aux->PosAsterisco == aux->producRef->der->size())
			continue;
		Token auxT = aux->producRef->der->at(aux->PosAsterisco);
		if (auxT.name == aceT.name) {
			Estado_Compilador* neo = new Estado_Compilador;
			neo->acc = "complet";
			neo->PosAsterisco = aux->PosAsterisco + 1;
			neo->PosPalabra = stte->PosPalabra;
			neo->producRef = aux->producRef;
			neo->root = i;
			chart->push_back(*neo);
		}
	}
}