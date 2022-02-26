#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"


int
main(void)
{
   TVectorCalendario a(3);
   TCalendario ca1(1,1,2006, (char*) "uno"), ca2(1,2,2006, (char*) "dos"), ca3(1,3,2006, (char*) "tres");

   a[1]=ca1;
   a[2]=ca2;
   a[3]=ca3;
   
   //Imprimimos el vector
   cout << a << endl;

   //cout << a[1] << endl;
   //cout << a[0] << endl;
   //Pasamos fecha incorrecta
   a.MostrarMensajes(32,12, 2000);
   cout << endl;

   //Pasamos fecha correcta
   a.MostrarMensajes(1,1,2006);
   cout << endl;

   //Pasamos fecha correcta
   a.MostrarMensajes(1,2,2006);
   cout << endl;
}