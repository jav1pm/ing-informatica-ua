#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"

int main()
{
    TCalendario a(10,10,2006, (char*) "mensaje 1");
    TCalendario b(11,10,2006, (char*) "mensaje 2");
    TCalendario c(12,10,2006, (char*) "mensaje 3");
    TCalendario d(13,10,2006, (char*) "mensaje 4");
    TCalendario e(14,10,2006, (char*) "mensaje 5");
    TCalendario f(15,10,2006, (char*) "mensaje 6");
    TListaCalendario lis;
    TListaPos p;

    lis.Insertar(a);
    lis.Insertar(b);
    lis.Insertar(c);
    lis.Insertar(d);
    lis.Insertar(e);
    lis.Insertar(f);

    cout << "Lista original: " << lis << endl << endl;
    
    p = lis.Primera(); //Sacamos la primera posicion

    //Hacemos que borre la primera posicion
    cout << lis.Borrar(p) << endl;
    cout << lis << endl;

    p = lis.Ultima(); //Sacamos la ultima posicion
    p = p.Siguiente(); //Saco la posicion siguiente(POSICION NO VALIDA)

    //Borramos con la posicion no valida
    cout << lis.Borrar(p) << endl;
    cout << lis << endl;

    p = lis.Ultima(); //Saco la ultima posicion

    //Borramos la ultima posicion una vez(debe hacerse bien)
    cout << lis.Borrar(p) << endl;
    cout << lis << endl;

    //Borramos por segunda vez la segunda posicion(debe salir false y no borrarse nada)
    cout << lis.Borrar(p) << endl;
    cout << lis << endl;

    p = lis.Primera(); //Sacamos la primera posicion
    p = p.Siguiente();
    p = p.Siguiente(); //Hacemos dos siguientes para que nos de una posicion intermedia de la lista

    //Borramos una posicion intermedia(En este caso la posicion de el TCalendario d)
    cout << lis.Borrar(p) << endl;
    cout << lis << endl;

    //Declaramos una posicion vacia
    TListaPos p2;

    //Borramos con la posicion vacía(debe dar false)
    cout << lis.Borrar(p2) << endl;
    cout << lis << endl;
}