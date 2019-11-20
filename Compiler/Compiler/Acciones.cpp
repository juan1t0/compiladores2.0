#include "Acciones.h"

Estado_Compilador::Estado_Compilador(int s_cht, int ast_pos, int pal_pos, Produccion* ptr_p, Estado_Compilador* ptr_e) {
	this->estadoChart = s_cht;
	this->PosAsterisco = ast_pos;
	this->PosPalabra = pal_pos;
	this->producRef = ptr_p;
	this->root = ptr_e;
}

bool Dummy::sePuedeAplicar() {
	return true; 
}
void Dummy::aplica(vector<Estado_Compilador> *chart, Produccion* ini){
	Produccion* fist = gramarSource->get_Production(0);
	vector<Token> v;
	v.push_back(fist->nombre);
	string na = "S";
	Token nn(na);
	Produccion* temp = new Produccion(nn,v);
	Estado_Compilador tt;
	tt.PosAsterisco = 0;
	tt.PosPalabra = 0;
	tt.producRef = temp;
	tt.root = 0;
//	tt.estadoChart = 0;
	gramarSource->production.insert(gramarSource->production.begin(), temp);
	chart->push_back(tt);
	ini = temp; //////revisa esta partre
}
//cambiar constructor
Dummy::Dummy(vector<Estado_Compilador>* chart, Produccion* ini) {
	if (sePuedeAplicar()) {
		aplica(chart,ini);
	}
}
bool Expandir::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	//        if (stte->producRef->isTerminal) return false;
	int i;
	for (i = 0; i < chart->size(); ++i) {
		if (chart->at(i).producRef->nombre.name == stte->producRef->nombre.name) return false;
	}
	return true;
}
void Expandir::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {//, queue<Estado_Compilador*> &chrt){
	size_t sizz = gramarSource->production.size();
	string nn = (stte->producRef->der->at(stte->PosAsterisco)).name;
	for (size_t i = 0; i < sizz; ++i) {
		if (gramarSource->production[i]->nombre.name == nn) {
			Estado_Compilador* EC = new Estado_Compilador;
			EC->producRef = gramarSource->production[i];
			//EC->gramarSource = stte->gramarSource;
			EC->PosAsterisco = 0;
			EC->PosPalabra = 0;
			EC->root = stte;
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
}
void Aceptar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
//	Estado_Compilador* NE = new Estado_Compilador(stte->producRef, stte->PosAsterisco + 1, stte->PosPalabra, stte->root);
//	NE->estadoChart = stte->estadoChart + 1;
//	chart.push_back(NE);
	///estado char incrementa
	///mueve el asterisco
}

bool Unificar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///si el no terminal es igual a un elemento de la oracion
	///si es libre de contexto, no verifica mas
}
void Unificar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///Verificamos si la cadena de la oracion es igual a la cadena del nodo no terminal
	///Si son iguales, verificamos si no hay problema con cambiar de contexto en el Estado compilador
	///Si el valor de la variable no fue establecido, verificamos que no haya conflicto
}

bool Completar::sePuedeAplicar(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///si el no terminal es igual a un elemento de la oracion
	///si es libre de contexto, no verifica mas
}
void Completar::aplica(Estado_Compilador* stte, vector<Estado_Compilador>* chart) {
	///Verificamos si la cadena de la oracion es igual a la cadena del nodo no terminal
	///Si son iguales, verificamos si no hay problema con cambiar de contexto en el Estado compilador
	///Si el valor de la variable no fue establecido, verificamos que no haya conflicto
}