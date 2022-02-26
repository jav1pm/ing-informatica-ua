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
  
  l1.Insertar(a);   
  l1.Insertar(b);
  l1.Insertar(a + 3);

  TListaCalendario l2(l1);
  cout << "l2 = " << l2 << endl;
  cout << "l1 = " << l1 << endl;
  return 0;
}
