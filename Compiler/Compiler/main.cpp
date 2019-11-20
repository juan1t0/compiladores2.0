/**
* Hecho por
*	Heredia Parillo, JuanPablo Andrew
*	Rendon Zuniga, Luis Francisco
**/

#include "Acciones.h"
//////////////////////////////////////////////////token <string name, vector<string> variables , vector<string> valores>

bool StopCond(Estado_Compilador* EC, Produccion* prod, size_t INsize) {
	if (EC->PosPalabra == INsize) return true;
	if (EC->PosAsterisco >= EC->producRef->der->size()) return true;
	//if(prod == inicial) return false;
	return false;
}
//hacer una funcion que con el map de la gramatica me genere un map de los valores de las producciones

vector<Estado_Compilador>* parser(Produccion* ini, vector<Produccion>* listP, vector<Token> *entrada) {
	vector<Estado_Compilador>* Chart = new vector<Estado_Compilador>;
	Dummy(Chart,ini);
	int indiceChart;
	for (indiceChart = 0; indiceChart < Chart->size(); ++indiceChart) {
		Estado_Compilador* cur_EC = &(Chart->at(indiceChart));
		if (StopCond(cur_EC, ini, entrada->size())) {
			break;
		}
		Expandir* tempExp = new Expandir();
		Completar* tempCpl = new Completar();
		Aceptar* tempAcp = new Aceptar();
		if (tempExp->sePuedeAplicar(cur_EC,Chart)) {
			tempExp->aplica(cur_EC, Chart);
		}
		else if (tempCpl->sePuedeAplicar(cur_EC, Chart)) {
			tempCpl->aplica(cur_EC, Chart);
		}
		else if (tempAcp->sePuedeAplicar(cur_EC, Chart)) {
			tempAcp->aplica(cur_EC, Chart);
		}
		delete tempExp;
		delete tempCpl;
		delete tempAcp;
	}
	if (indiceChart >= Chart->size()) {
		return NULL;
	}
	return Chart;
}

//////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	Gramatica grammar;
/*	grammar.read("E := T Ep");
	grammar.read("Ep := + T Ep | - T Ep | lambda");
	grammar.read("T := F Tp");
	grammar.read("Tp := * F Tp");
	grammar.read("F := (E) | num | id");
	*/
	grammar.read("Sus[gen=?_,num=?_] := Det[gen=?_] Suj[gen=?_,num=?_]");
	grammar.read("Det[gen=?f] := 'la'");
	grammar.read("Det[gen=?m] := 'el'");
	grammar.read("Suj[gen=?m] := 'nino'");
	grammar.read("Suj[gen=?f] := 'nina'");
/*	vector<vector<string>> producciones = grammar.getProduction("Sus");
	printMatrix(producciones);
	producciones = grammar.getProduction("Det");
	printMatrix(producciones);
	producciones = grammar.getProduction("Suj");
	printMatrix(producciones);
*/	grammar.printGrammar();
	
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