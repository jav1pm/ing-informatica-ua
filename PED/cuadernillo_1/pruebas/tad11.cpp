		#include <iostream>
#include "tlistacalendario.h"
using namespace std;
int main(){
	TListaCalendario lista1, lista2;
	
	lista1.Insertar(TCalendario(1, 3, 1976, (char*)"jose"));
	lista1.Insertar(TCalendario(1, 3, 1976, (char*)"fran"));
	lista1.Insertar(TCalendario(1, 3, 1976, NULL));
	lista1.Insertar(TCalendario(2, 2, 1980, (char*)"pepico"));
	lista1.Insertar(TCalendario(3, 4, 2000, (char*)"juan"));

	lista2.Insertar(TCalendario(2, 3, 1976, NULL));
	lista2.Insertar(TCalendario(4, 4, 1981, (char*)"soy negro"));
	lista2.Insertar(TCalendario(3, 3, 1988, (char*)"soy azul"));
	lista2.Insertar(TCalendario());
	lista2.Insertar(TCalendario(3, 3, 1976, NULL));

//																1				2				3					4				5
	cout << "Lista 1: " << lista1 << endl; //Lista 1: <01/03/1976 "" 01/03/1976 "fran" 01/03/1976 "jose" 02/02/1980 "pepico" 03/04/2000 "juan">
	cout << "lista 2: " << lista2 << endl; //lista 2: <01/01/1900 "" 02/03/1976 "" 03/03/1976 "" 04/04/1981 "soy negro" 03/03/1988 "soy azul">

	cout << lista1.SumarSubl(1, 2, lista2, 3, 10) << endl;  //<01/03/1976 "" 01/03/1976 "fran" 03/03/1976 "" 04/04/1981 "soy negro" 03/03/1988 "soy azul">
	cout << lista1.SumarSubl(-1, 3, lista2, -2, 4) << endl; //<01/01/1900 "" 01/03/1976 "" 01/03/1976 "fran" 01/03/1976 "jose" 02/03/1976 "" 03/03/1976 "" 04/04/1981 "soy negro">
	return 0;
}

