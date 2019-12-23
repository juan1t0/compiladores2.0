/**
* Hecho por
*	- Heredia Parillo, JuanPablo Andrew
*	- Rendon Zuniga, Luis Francisco
**/

#include "Acciones.h"
void printEstadoC(Estado_Compilador ec, int index);
bool StopCond(Estado_Compilador* EC, Produccion* ini_prod, size_t INsize) {
	if (EC->PosPalabra == INsize)
		return true;
	if (EC->PosAsterisco >= EC->producRef->der->size() && EC->producRef->nombre.name == ini_prod->nombre.name)
		return true;
	return false;
}
vector<Estado_Compilador>* parser(Gramatica* gra, vector<Produccion>* listP, vector<Token>* entrada) {
	vector<Estado_Compilador>* Chart = new vector<Estado_Compilador>;
	Dummy *ADumi=new Dummy(gra);
	ADumi->aplica(Chart);
	Produccion* ini = gra->get_Production(0);
	int indiceChart;
	for (indiceChart = 0; indiceChart < Chart->size(); ++indiceChart) {
		Estado_Compilador* cur_EC = &(Chart->at(indiceChart));
		if (StopCond(cur_EC, ini, entrada->size())) {
			break;
		}
		Expandir* tempExp = new Expandir(gra);
		Completar* tempCpl = new Completar(gra);
		Aceptar* tempAcp = new Aceptar(gra,entrada);
		if (tempExp->sePuedeAplicar(cur_EC,Chart)) {
			tempExp->aplica(cur_EC, Chart);
		}
		else if (tempAcp->sePuedeAplicar(cur_EC, Chart)) {
			tempAcp->aplica(cur_EC, Chart);
			indiceChart = Chart->size()-1;
			cur_EC = &(Chart->at(indiceChart));
			if (tempCpl->sePuedeAplicar(cur_EC, Chart)) {
				tempCpl->aplica(cur_EC, Chart);
			}
		}
		else if (tempCpl->sePuedeAplicar(cur_EC, Chart)) {
			tempCpl->aplica(cur_EC, Chart);
		}
		delete tempExp;
		delete tempCpl;
		delete tempAcp;
	}
	if (indiceChart > Chart->size()) {
		return NULL;
	}
	return Chart;
}
vector<Produccion>* getProducToParsin(Gramatica &gr){
	vector<Produccion>* R = new vector<Produccion>;
	for (int i = 0; i < gr.production.size(); ++i) {
		R->push_back(*(gr.production[i]));
	}
	return R;
}
vector<Token>* GetToksToParsin(string in, Gramatica &gr){
	vector<Token>* R = new vector<Token>;
	stringstream ss(in);
	string str;
	while(ss>>str){
		Token t(str);
		R->push_back(t);
	}
	return R;
}
void printEstadoC(Estado_Compilador ec, int index) {
	string producion, accion, ancestro;
	int estado, estado_ref;
	printf(".");
	producion = ec.producRef->toprint(ec.PosAsterisco);
	printf(".");
	estado = ec.PosPalabra;
	printf(".");
	estado_ref = 0;
	printf(".");
	accion = ec.acc;
	printf(".");
	ancestro = "[";
	ancestro += to_string(ec.root);
	ancestro+="]";
	printf(".\n");
	printf("%d\t\t%s\t%d\t\t%d\t\t%s\t\t%s\n", index, producion.c_str(), estado, estado_ref, accion.c_str(), ancestro.c_str());
}


int main(int argc, char* argv[]) {
	Gramatica grammar;
	
	//grammar.read("Sen[NUM=?_] := NP[NUM=?_] VP[NUM=?_]");
	//grammar.read("NP[NUM=?_] := Det[NUM=?_] N[NUM=?_]");
	//grammar.read("VP[NUM=?_] := V[NUM=?_]");
	//grammar.read("Det[NUM=?s] := this");
	//grammar.read("Det[NUM=?p] := these");
	//grammar.read("N[NUM=?s] := dog");
	//grammar.read("N[NUM=?p] := dogs");
	//grammar.read("V[NUM=?s] := runs");
	//grammar.read("V[NUM=?p] := run");


	grammar.read("Sus[gen=?_,num=?_] := Det[gen=?_,num=?_] Suj[gen=?_,num=?_]");
	grammar.read("Det[gen=?f,num=?p] := las");
	grammar.read("Det[gen=?m,num=?s] := el");
	grammar.read("Suj[gen=?m,num=?s] := nino");
	grammar.read("Suj[gen=?f,num=?p] := ninas");
	
	/*grammar.read("Sus[gen=?_] := Det[gen=?_] Suj[gen=?_]");
	grammar.read("Det[gen=?f] := la");
	grammar.read("Det[gen=?m] := el");
	grammar.read("Suj[gen=?m] := nino");
	grammar.read("Suj[gen=?f] := ninas");*/


	vector<Estado_Compilador>* myChart;
	
	vector<Produccion>* gp = getProducToParsin(grammar);
	string Sinput = "las nino";
	vector<Token>* input = GetToksToParsin(Sinput, grammar);
	myChart = parser(&grammar, gp, input);
	grammar.printGrammar();
	printf("\nEntrada: %s\n", Sinput.c_str());
	cout << "---------" << endl;
	printf("indexChart\tProduccion\tStatechar\tstateRef\tOperacion\tAncestrolist\n");
	cout << "---------" << endl;
	if (myChart == NULL)return 0;
	for (int i = 0; i < myChart->size(); ++i) {
		printEstadoC(myChart->at(i),i);
	}
	return 0;
}