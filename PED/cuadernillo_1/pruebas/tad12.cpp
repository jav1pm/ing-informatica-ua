#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1;
   TCalendario c1(14, 12, 1966, (char*) "Fecha 4");
   TCalendario c2(1, 1, 1954, (char*) "Fecha 1");
   TCalendario c3(3, 2, 1960, (char*) "Fecha 2");
   TCalendario c4(3, 2, 1960, (char*) "Fecha 3");
   TCalendario c5(1, 1, 2000, (char*) "Fecha 5");
   
   //Lista vacía
   cout<<l1<<endl;

   //Añadimos un elemento a una lista vacia
   l1.Insertar(c1);
   cout<<l1<<endl;

   //Añadimos un elemento al comienzo de una lista 
   l1.Insertar(c2);
   cout<<l1<<endl;

   //Añadimos dos elementos en medio de una lista 
   l1.Insertar(c3);
   l1.Insertar(c4);
   cout<<l1<<endl;

   //Añadimos un elemento al final de una lista
   l1.Insertar(c5);
   cout<<l1<<endl;

   //Añadimos un TCalendario ya existente
   if(l1.Insertar(c2))
      cout<<"Insertado TCalendario duplicado !!!"<<endl;
   else cout <<"No se inserto el duplicado"<<  endl;
   
   cout<<l1<<endl;

   return 0;
}
