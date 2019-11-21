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
	Estado_Compilador tt(0,0,0,temp,0,"dummy");
	gramarSource->production.insert((gramarSource->production.begin()), temp);
	chart->push_back(tt);

}

bool Expandir::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	//        if (stte->producRef->isTerminal) return false;
	//int i;
	//for (i = 0; i < chart->size(); ++i) {
	//	if (chart->at(i).producRef->nombre.name == stte->producRef->nombre.name) return false;
	//}
	//return true;
	//printf("expr: %d %d", stte->PosAsterisco, stte->producRef->der->size());
	if (stte->PosAsterisco == stte->producRef->der->size())
		return false;
	string tokeni = (stte->producRef->der->at(stte->PosAsterisco)).name;
	//cout <<"- * en "<< tokeni <<" con "<< gramarSource->terminals[tokeni] << endl;
	return !(gramarSource->terminals[tokeni]);
}
void Expandir::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	size_t sizz = gramarSource->production.size();
	string nn = (stte->producRef->der->at(stte->PosAsterisco)).name;
	int pp = stte->PosPalabra;
	printf("pp: %d\n", pp);
	for (size_t i = 0; i < sizz; ++i) {
		if (gramarSource->production[i]->nombre.name == nn) {
			Estado_Compilador* EC = new Estado_Compilador;
			EC->producRef = gramarSource->production[i];
			//EC->gramarSource = stte->gramarSource;
			EC->PosAsterisco = 0;
			EC->PosPalabra = pp;
			EC->root = 0;
			EC->acc = "expan";
			chart->push_back(*EC);
		}
	}
}

bool Aceptar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///si el astericso esta a la izquierda de un terminal
//	vector<string> tokens = *(stte->tokens);
//	if (gramarSource->isTerminal(tokens[stte->PosAsterisco])) {//faltaria implementar isTerminal
		///verificamos con ayuda de unificar si es el mismo elemento indicado con pos palabra del estado compilador
//	}
	//printf("a: %d %d\n", stte->PosAsterisco, stte->producRef->der->size());
	if (stte->PosAsterisco == stte->producRef->der->size())
		return false;
	string nametemp = (stte->producRef->der->at(stte->PosAsterisco)).name;
//printf("acp: %s\n",nametemp.c_str());
	if (gramarSource->terminals[nametemp]) {
	//	printf("tmb\n");
		Unificar t(gramarSource, entrada);
		return t.sePuedeAplicar(stte,chart);
	}
	return 0;
}
void Aceptar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
//	Estado_Compilador* NE = new Estado_Compilador(stte->producRef, stte->PosAsterisco + 1, stte->PosPalabra, stte->root);
//	NE->estadoChart = stte->estadoChart + 1;
//	chart.push_back(NE);
	///estado char incrementa
	///mueve el asterisco
	bool err=false;
	for (int i = 0; i < stte->producRef->nombre.var->size(); ++i) {
		err = false;
		string cur_var = stte->producRef->nombre.var->at(i), cur_val = stte->producRef->nombre.val->at(i);
		printf("cur:: %s %s\n", cur_var.c_str(), cur_val.c_str());
		for (int j = 0; j < gramarSource->contescto->size(); ++j) {
			if (gramarSource->contescto->at(j).first == cur_var) {
				
				cout << gramarSource->contescto->at(j).first << " # " << gramarSource->contescto->at(j).second <<"|"<< endl;

				if (gramarSource->contescto->at(j).second == "?_ ") {
					cout << "vacio ->> ";
					gramarSource->contescto->at(j).second = cur_val;
					cout << gramarSource->contescto->at(j).second << endl;
					break;
				}
				else if (gramarSource->contescto->at(j).second == cur_val) {
					cout << "el mismo" << endl;
					break;
				}
				err = true; 
				cout << gramarSource->contescto->at(j).first << " ## " << gramarSource->contescto->at(j).second << endl;
				break;
			}
		}
		if (err)break;
	}
	if (err) {
		cout<<"error de tipo"<<endl;
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
	printf("u: %d %d\n", palpos, riscoPos);
	string u1= stte->producRef->der->at(riscoPos).name, u2= entrada->at(palpos).name;
	printf("us: %s %s\n", u1.c_str(),u2.c_str());
	if (stte->producRef->der->at(riscoPos).name == entrada->at(palpos).name) {
		return 1;
	}
	return 0;

	//for (int i = 0; i < gramarSource->production.size(); ++i) {
	//	if (gramarSource->production[i]->der->size() == 1) {
	//		if (gramarSource->production[i]->der->at(0).name == entrada->at(palpos).name) {
	//			string a1 = gramarSource->production[i]->der->at(0).name;
	//			string a2 = entrada->at(palpos).name;
	//			printf("%s == %s\n", a1.c_str(), a2.c_str());
	//			return 1;
	//		}
	//	}
	//}
	return 0;
}
void Unificar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///Verificamos si la cadena de la oracion es igual a la cadena del nodo no terminal
	///Si son iguales, verificamos si no hay problema con cambiar de contexto en el Estado compilador
	///Si el valor de la variable no fue establecido, verificamos que no haya conflicto
}

bool Completar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	int posterisco = stte->PosAsterisco;
	int sise = stte->producRef->der->size();
	//printf("cmplt: %d %d \n",posterisco, sise);
	if (posterisco == sise)
		return 1;
	else return 0;
}
//completar tmb añade el contexto que se acepto, luego verifica si ya habia contexto, si hay co revisa, si no lo añade ala prt izq
void Completar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	int sz = chart->size();
	Token aceT = stte->producRef->nombre;
	for (int i = 0; i < sz; ++i) {
		Estado_Compilador* aux = &(chart->at(i));
		if (aux->acc == "acept" || aux->acc == "complet")
			continue;
		if (aux->PosAsterisco == aux->producRef->der->size())
			continue;
		Token auxT = aux->producRef->der->at(aux->PosAsterisco);
		//cout << auxT.name << "==" << aceT.name << endl;
		if (auxT.name == aceT.name) {
			//verificar contexto

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

/**
*	unificar:
		- si la izq tiene valores reales en su contexto, verificamos que no halla conflicto
		- si no lo agregamos
		LA VERIFICACION SE HACE EN LOS DE ARRIBA, NO EN LOS QUE CONTIENEN LOS NO TERMINNALES DE ORACION
	aceptar:
		- si se unifica, pasa el asterisco al lado der
	completar:
		-actualiza las producciones, 
		"unifica" cuando pasa el * en otras producciones agrega el contexto,
		-- le pone el ancestro, busca todos los que tengan el izq en el pos*
		- solo se aplica cuando pos* esta al final, osea == der.size() de la produccion
*/