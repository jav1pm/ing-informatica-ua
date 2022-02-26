#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
  TListaCalendario lista;

  /*  En obtener, se tiene que devolver el TCalendario apuntado por el objeto 
    TListaPos, excepto si dicho TListaPos es vacio (en cuyo caso se devuelve)
    un TCalendario "vacio"
  */

  cout << lista.Primera().EsVacia() << endl;
  TCalendario vacio = lista.Obtener(lista.Primera());
  cout << vacio << endl;
}
