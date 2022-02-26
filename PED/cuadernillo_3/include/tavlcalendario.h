#ifndef _TAVLCALENDARIO_H_
#define _TAVLCALENDARIO_H_

#include <iostream>
#include <string.h>
#include "tvectorcalendario.h"

class TNodoAVL;

class TAVLCalendario
{
    friend ostream & operator<<(ostream &, const  TAVLCalendario &);

    private:

        // Puntero al nodo
        TNodoAVL *raiz;

        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;

        void Copiar(const TAVLCalendario &);

        bool InsertarAux(const TCalendario &, bool &);
        bool BorrarAux(const TCalendario &, bool &);

        void ActualizarFE();
        void Equilibrar();
        void DD();
        void DI();
        void II();
        void ID();

        TCalendario mayorIz();

    public:

        TAVLCalendario();
        TAVLCalendario(const TAVLCalendario &);
        ~TAVLCalendario();
        TAVLCalendario & operator=(const TAVLCalendario &);

        bool operator==(const TAVLCalendario &);
        bool operator!=(const TAVLCalendario &);
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

        TAVLCalendario operator+(const TAVLCalendario &);
        TAVLCalendario operator-(const TAVLCalendario &);
};

class TNodoAVL
{
    friend class TAVLCalendario;

    private:

        TCalendario item;
        TAVLCalendario iz, de;
        int fe; // factor de equilibrio

    public:

        TNodoAVL();
        TNodoAVL(const TNodoAVL &);
        ~TNodoAVL();
        TNodoAVL & operator=(const TNodoAVL &);
};

#endif