/**
* Hecho por
*	Heredia Parillo, JuanPablo Andrew
*	Rendon Zuniga, Luis Francisco
**/

#include "Acciones.h"
//////////////////////////////////////////////////token <string name, vector<string> variables , vector<string> valores>
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