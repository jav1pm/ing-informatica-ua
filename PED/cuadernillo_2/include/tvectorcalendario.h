#ifndef _TVECTORCALENDARIO_H_
#define _TVECTORCALENDARIO_H_

#include <iostream>
#include <string.h>
#include "tcalendario.h"

using namespace std;

class TVectorCalendario {

    friend ostream & operator<<(ostream &, const TVectorCalendario &);

    private:

        TCalendario *c;
        int tamano;
        TCalendario error;
        void Copia(const TVectorCalendario &);

    public:

        // FORMA CANÓNICA
        TVectorCalendario();
        TVectorCalendario(int);
        TVectorCalendario(const TVectorCalendario &);
        ~TVectorCalendario();
        TVectorCalendario & operator=(const TVectorCalendario &);

        // MÉTODOS
        bool operator==(const TVectorCalendario &);
        bool operator!=(const TVectorCalendario &);
        TCalendario & operator[](int); // Parte IZQUIERDA.
        TCalendario operator[](int) const; // Parte DERECHA.
        int Tamano() {return tamano;}
        int Ocupadas();
        bool ExisteCal(const TCalendario &);
        void MostrarMensajes(int, int, int);
        bool Redimensionar(int);
};

#endif