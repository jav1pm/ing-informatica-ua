#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
  TCalendario a(1, 1, 1977, (char*) "uno");
  TCalendario b(1, 1, 1980, (char*) "dos");
  TListaCalendario l1;

  if(l1.EsVacia())
    cout << "Lista vacia" << endl;
  else
    cout << "Lista no vacia" << endl;
  
  l1.Insertar(a);   
  l1.Insertar(b);

  if(l1.EsVacia())
    cout << "Lista vacia" << endl;
  else
    cout << "Lista no vacia" << endl;

  return 0;
}
