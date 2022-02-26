#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1;
   TCalendario c1;
   TCalendario c2(1, 1, 2007, (char*) "Fecha2");

   cout << l1 << endl;

   l1.Insertar(c1);
   l1.Insertar(c2);
   cout << l1 << endl;

   l1.Borrar(c2);
   cout << l1 << endl;

   return 0;
}
