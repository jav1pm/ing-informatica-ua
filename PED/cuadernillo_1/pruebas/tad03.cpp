#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1;
   TCalendario c;

   cout << l1.Longitud() << endl;

   l1.Insertar(c);
   cout << l1.Longitud() << endl;

   return 0;
}
