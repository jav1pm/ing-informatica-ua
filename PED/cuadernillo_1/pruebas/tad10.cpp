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
  
  l1.Insertar(b);
  cout << l1.Obtener(l1.Primera()) << endl;
  
  l1.Insertar(a);
  cout << l1.Obtener(l1.Primera()) << endl;

  cout << "l1 = " << l1 << endl;
  
  if(l1.EsVacia())
    cout << "Lista vacia" << endl;
  else
    cout << "Lista no vacia" << endl;
  
  return 0;
}
