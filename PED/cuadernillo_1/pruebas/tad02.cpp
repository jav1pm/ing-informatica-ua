#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1;
   TCalendario c1(14, 12, 1966, (char*) "Fecha Correcta");
   TCalendario c2(1, 1, 1954, (char*) "Fecha Correcta");
   
   cout << l1 << endl;
   l1.Insertar(c1);
   cout << l1 << endl;
   l1.Insertar(c2);
   cout << l1 << endl;

   return 0;
}
