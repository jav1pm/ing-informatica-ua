#include <iostream>

using namespace std;

#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"

int
main(void)
{
    TCalendario a(10,10,2006, (char*) "mensaje 1");
    TCalendario b(11,10,2006, (char*) "mensaje 2");
    TCalendario c(12,10,2006, (char*) "mensaje 3");
    TCalendario d(13,10,2006, (char*) "mensaje 4");
    TCalendario e(14,10,2006, (char*) "mensaje 5");

    TListaCalendario lista;
    TListaCalendario lista2;

    lista.Insertar(a);
    lista.Insertar(b);
    lista.Insertar(c);

    //Probamos el destructor
    cout << lista << endl;                                  //1
    lista.~TListaCalendario();
    cout << lista << endl;                                  //2
    cout << lista.Primera().EsVacia() << endl;                                  //3
    cout << lista.Ultima().EsVacia() << endl;               //4
    

    cout<< lista2 << endl;                                  //5
    lista2.~TListaCalendario();
    cout << lista2 << endl;//6                                  //6


    

    //Probamos el operador ==
    if(lista == lista2)
        cout << "OK.Las listas vacías coinciden" << endl;                                  //7
    else cout << "Fallo en la la linea 38 de tad99.cpp" << endl;                                  //7


    lista.Insertar(a);
    lista.Insertar(b);
    lista.Insertar(c);

    if(lista == lista2)
        cout << "Fallo en la la linea 46 de tad99.cpp" << endl;                                  //8
    else cout << "OK.Las listas no coinciden" << endl;                                   //8

    
    lista2 = lista;
    //cout<< lista<<endl;
    //cout<<lista2<<endl;
    if(lista == lista2)
        cout << "OK.Las listas coinciden" << endl;                                    //9
    else cout << "Fallo en la la lainea 52 de tad99.cpp" << endl;                                  //9

    TListaCalendario *lista3 = new TListaCalendario(lista2);
    if((*lista3) == lista2)
        cout << "OK.Las listas coinciden" << endl;//10                                  //19
    else cout << "Fallo en la la linea 57 de tad99.cpp" << endl;                                  //10

    
    //cout<<"LISTA ! -->"<<lista<<endl;
    //Probamos el operador+
    TListaCalendario lista4;
    lista4.Insertar(d);
    lista4.Insertar(e);
    cout << lista4 << endl;//11
    //cout<<"LISTA ! -->"<<lista<<endl;
    TListaCalendario lista5;
    lista5 = lista + lista4;
    //cout<<"LISTA ! -->"<<lista<<endl;
    cout << lista5 << endl;//12
    cout << lista << endl;//13
    cout << lista4 << endl;//14



    //Probamos el operador-
    TListaCalendario lista6;
    lista6 = lista - lista4;   
    cout << lista6 << endl; //Como no contienen elementos iguales la lista6 debe ser igual a lista
    cout << lista << endl;
    cout << lista4 << endl;

    //cout<<"LISTA 1 -->"<<lista<<endl;
    //cout<<"LISTA 5 -->"<<lista5<<endl;

    lista6 = lista - lista5;
    cout << lista6 << endl; //Como lista5 tiene todos los elementos de lista,e sta se quedará vacia
    cout << lista << endl;
    cout << lista5 << endl;//20




    //Probamos ExtraerRango()
    lista5 = lista;
    lista6 = lista5.ExtraerRango(1, 10); //Sobrepasa la longitud
    cout << lista6 << endl;
    
    lista5 = lista;
    lista6 = lista5.ExtraerRango(-1, 3); //n1 Por debajo de 0 el rango
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(-3, -1); //n2 Por debajo de 0 el rango
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(2,2); //n1==n2
    cout << lista6 << endl;

    lista5 = lista;
    lista6 = lista5.ExtraerRango(2, 1); //n1>n2
    cout << lista6 << endl;

    
    return 0;
}