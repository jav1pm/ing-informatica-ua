#ifndef _TABBCALENDARIO_H_
#define _TABBCALENDARIO_H_

#include <iostream>
#include <string.h>
#include "tvectorcalendario.h"

class TNodoABB;

class TABBCalendario
{
    friend ostream & operator<<(ostream &, const  TABBCalendario);

    private:

        // Puntero al nodo
        TNodoABB *raiz;

        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;

        void Copiar(const TABBCalendario &);
        bool Iguales(const TABBCalendario &);
        TCalendario mayorIz();

    public:

        TABBCalendario();
        TABBCalendario(const TABBCalendario &);
        ~TABBCalendario();
        TABBCalendario & operator=(const TABBCalendario &);

        bool operator==(const TABBCalendario &);
        bool EsVacio() const;
        bool Insertar(const TCalendario &);
        bool Borrar(const TCalendario &);

        bool Buscar(const TCalendario &) const;
        TCalendario Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;

        TVectorCalendario Inorden() const;
        TVectorCalendario Preorden() const;
        TVectorCalendario Postorden() const;
        TVectorCalendario Niveles() const;

        TABBCalendario operator+(const TABBCalendario &);
        TABBCalendario operator-(const TABBCalendario &);
};

class TNodoABB
{
    friend class TABBCalendario;

    private:

        TCalendario item;
        TABBCalendario iz, de;

    public:

        TNodoABB();
        TNodoABB(const TNodoABB &);
        ~TNodoABB();
        TNodoABB & operator=(const TNodoABB &);
};

#endif