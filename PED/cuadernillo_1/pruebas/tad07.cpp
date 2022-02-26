#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
  TListaCalendario l1;
  
  if((l1.Primera()).EsVacia())
    cout << "Direccion vacia" << endl;
  else
    cout << "Direccion no vacia" << endl;
    
  if((l1.Ultima()).EsVacia())
    cout << "Direccion vacia" << endl;
  else
    cout << "Direccion no vacia" << endl;

  cout << "l1 = " << l1 << endl;

  return 0;
}
