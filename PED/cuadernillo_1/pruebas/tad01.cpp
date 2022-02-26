#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
   TListaCalendario l1;
   TCalendario c1;
   TCalendario c2(1, 1, 2007, (char*) "Fecha 2");
   TCalendario c3(2, 1, 2007, (char*) "Fecha 3");
   TCalendario c4(1, 2, 2007, (char*) "Fecha 4");

   l1.Insertar(c4);
   l1.Insertar(c2);
   l1.Insertar(c1);
   l1.Insertar(c3);
   TListaCalendario l2 = l1;

   cout << l1 << endl;                             //1
   cout << l2 << endl;                             //2
// <01/01/1900 "" 01/01/2007 "Fecha 2" 02/01/2007 "Fecha 3" 01/02/2007 "Fecha 4">


   // PRUEBAS MÉTODO borrar(TCalendario)
   // Borrar al principio
   l2.Borrar(c1);
   cout << l2 << endl;                             //3
   l2 = l1;
   
   //Borrar por medio
   l2.Borrar(c2);
   l2.Borrar(c3);
   cout << l2 << endl;                             //4
   l2 = l1;

   //Borrar al final
   l2.Borrar(c4);
   cout << l2 << endl;                             //5
   l2 = l1;

   //Borrar la lista entera
   l2.Borrar(c1);
   l2.Borrar(c2);
   l2.Borrar(c3);
   l2.Borrar(c4);
   cout << l2 << endl;                             //6

   //PRUEBAS MÉTODO borrar(int, int, int)
   //Le pasamos una fecha posterior a la ultima de la lista para ver si se borra entera
   l2 = l1;
   l2.Borrar(1,3,2007);
   cout << l2 << endl;                             //7         // <>

   //Le pasamos la ultima fecha (se tiene que quedar)
   l2 = l1;
   l2.Borrar(1,2,2007);                                        // <01/02/2007 "Fecha 4">
   cout << l2 << endl;                             //8

   //Le pasamos una fecha anterior a la primera (no se borra ninguna)
   l2 = l1;
   l2.Borrar(1,1,1800); //SE BORRA LA 1/1/1900 ya que en la función borrar() se invoca al constructor de TCalendario que lo pone a 1/1/1900 y como es igual lo borra
   cout << l2 << endl;                             //9

   return 0;
}
