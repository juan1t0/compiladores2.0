/**
* Hecho por
*	Heredia Parillo, JuanPablo Andrew
*	Rendon Zuniga, Luis Francisco
**/

#include "Acciones.h"
//////////////////////////////////////////////////token <string name, vector<string> variables , vector<string> valores>
void printEstadoC(Estado_Compilador ec, int index);
bool StopCond(Estado_Compilador* EC, Produccion* ini_prod, size_t INsize) {
	//printf("stop: %d %d \n", EC->PosPalabra, INsize);
	if (EC->PosPalabra == INsize) return true;
//	printf("stop: %d %d \n", EC->PosAsterisco, EC->producRef->der->size());
	if (EC->PosAsterisco >= EC->producRef->der->size() && EC->producRef->nombre.name == ini_prod->nombre.name) return true;
	//if(prod == inicial) return false;
	return false;
}
//hacer una funcion que con el map de la gramatica me genere un map de los valores de las producciones

vector<Estado_Compilador>* parser(Gramatica* gra, vector<Produccion>* listP, vector<Token>* entrada) {
	vector<Estado_Compilador>* Chart = new vector<Estado_Compilador>;
	Dummy *ADumi=new Dummy(gra);
	ADumi->aplica(Chart);
	Produccion* ini = gra->get_Production(0);
	int indiceChart;
//	return Chart;
	for (indiceChart = 0; indiceChart < Chart->size(); ++indiceChart) {
		printf(">>(%d %d)", indiceChart, Chart->size());
		printEstadoC(Chart->at(indiceChart), indiceChart);

		Estado_Compilador* cur_EC = &(Chart->at(indiceChart));
		if (StopCond(cur_EC, ini, entrada->size())) {
			break;
		}
		printf(",");
		Expandir* tempExp = new Expandir(gra);
		Completar* tempCpl = new Completar(gra);
		Aceptar* tempAcp = new Aceptar(gra,entrada);
		printf(",");
		if (tempExp->sePuedeAplicar(cur_EC,Chart)) {
			printf("e %d\n",indiceChart);
			tempExp->aplica(cur_EC, Chart);
		}
		else if (tempAcp->sePuedeAplicar(cur_EC, Chart)) {
			printf("a %d\n", indiceChart);
			tempAcp->aplica(cur_EC, Chart);
		}
		else if (tempCpl->sePuedeAplicar(cur_EC, Chart)) {
			printf("c %d\n", indiceChart);
			tempCpl->aplica(cur_EC, Chart);
			printf("clptado\n");
		}
		printf(",[%d %d]\n", indiceChart, Chart->size());
		delete tempExp;
		delete tempCpl;
		delete tempAcp;
	}
	printf(">>>(%d %d)", indiceChart, Chart->size());
	//printEstadoC(Chart->at(indiceChart), indiceChart);
	if (indiceChart >= Chart->size()) {////////pensá
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

//////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	Gramatica grammar;
	grammar.read("Sus[gen=?_,num=?_] := Det[gen=?_] Suj[gen=?_,num=?_]");
	grammar.read("Det[gen=?f,num=?s] := la");
	grammar.read("Det[gen=?m,num=?s] := el");
	grammar.read("Suj[gen=?m,num=?s] := nino");
	grammar.read("Suj[gen=?f,num=?p] := ninas");

	vector<Estado_Compilador>* myChart;
	
	//funcion para tener producciones
	//funcion para tener input
	vector<Produccion>* gp = getProducToParsin(grammar);
	vector<Token>* input = GetToksToParsin("el ninas", grammar);
	myChart = parser(&grammar, gp, input);
	grammar.printGrammar();
	printf("indexChart\tProduccion\tStatechar\tstateRef\tOperacion\tAncestrolist\n");
	for (int i = 0; i < myChart->size(); ++i) {
		printEstadoC(myChart->at(i),i);
	}
	return 0;
}

/**
* Sus[gen=? ] := Det[gen=? ] Suj[gen=? ]
* Det[gen=f] := 'la'
* Det[gen=m] := 'el'
* Suj[gen=m] := 'nino'
* Suj[gen=f] := 'nina'
*/

/*	AnalizadorSintacticoLL1 analizador;
analizador.llenarTas();
cout<<analizador.reconocerSentencia("num + num + num + num")<<endl;
cout<<analizador.reconocerSentencia("( num + num ) + ( num + num )")<<endl;
cout<<analizador.reconocerSentencia("num * ( num * num )")<<endl;
cout<<analizador.reconocerSentencia("( num *) num")<<endl;	*/
/*
int main(int argc, char* argv[]) {
	Gramatica grammar;
/*	grammar.read("E := T Ep");
	grammar.read("Ep := + T Ep | - T Ep | lambda");
	grammar.read("T := F Tp");
	grammar.read("Tp := * F Tp");
	grammar.read("F := (E) | num | id");
	
grammar.read("Sus[gen=?_,num=?_] := Det[gen=?_] Suj[gen=?_,num=?_]");
grammar.read("Det[gen=?f,num=?s] := 'la'");
grammar.read("Det[gen=?m,num=?s] := 'el'");
grammar.read("Suj[gen=?m,num=?s] := 'nino'");
grammar.read("Suj[gen=?f,num=?p] := 'ninas'");
/*	vector<vector<string>> producciones = grammar.getProduction("Sus");
	printMatrix(producciones);
	producciones = grammar.getProduction("Det");
	printMatrix(producciones);
	producciones = grammar.getProduction("Suj");
	printMatrix(producciones);

vector<Estado_Compilador>* myChart;

//funcion para tener producciones
//funcion para tener input

myChart = parser(grammar.estadoInicial, grammar.production, input);
grammar.printGrammar();

return 0;
}

*/