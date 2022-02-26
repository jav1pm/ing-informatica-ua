#ifndef _TLISTACALENDARIO_H_
#define _TLISTACALENDARIO_H_

#include <iostream>
#include "tvectorcalendario.h"

class TNodoCalendario {

    friend class TListaPos;
    friend class TListaCalendario;

    private:

        TCalendario c;
        TNodoCalendario *siguiente;

    public:

        TNodoCalendario();
        TNodoCalendario(const TNodoCalendario &);
        ~TNodoCalendario();
        TNodoCalendario & operator=(const TNodoCalendario &);
};

class TListaPos {

    friend class TListaCalendario;

    private:
        //Posición a NODO de la lista de TCalendario.
        TNodoCalendario *pos;

    public:

        TListaPos();
        TListaPos(const TListaPos &);
        ~TListaPos();
        TListaPos & operator=(const TListaPos &);

        bool operator==(const TListaPos &) const;
        bool operator!=(const TListaPos &) const;
        TListaPos Siguiente();
        bool EsVacia() const;
};

class TListaCalendario {

    friend ostream & operator<<(ostream &, const TListaCalendario &);

    private:

        TNodoCalendario *primero;

    public:

        TListaCalendario();
        TListaCalendario(const TListaCalendario &);
        ~TListaCalendario();
        TListaCalendario & operator=(const TListaCalendario &);

        bool operator==(const TListaCalendario &);
        TListaCalendario operator+(const TListaCalendario &);
        TListaCalendario operator-(const TListaCalendario &);
        // Inserta el elemento en la posición que le corresponda dentro de la lista.
        bool Insertar(const TCalendario &);
        // Busca y borra el elemento
        bool Borrar(const TCalendario &);
        // Borra el elemento que ocupa la posición indicada.
        bool Borrar(const TListaPos &);
        //Borra todos los Calendarios con fecha ANTERIOR a la pasada.
        bool Borrar(int, int, int);
        // True si lista vacía, false en caso contrario.
        bool EsVacia() const;
        // Obtiene el elemento que ocupa la posición indicada.
        TCalendario Obtener(const TListaPos &) const;
        // Devuelve true si el Calendario está en la lista.
        bool Buscar(const TCalendario &);
        int Longitud() const;
        TListaPos Primera() const;
        TListaPos Ultima() const;
        // Suma de dos sublistas en una nueva lista.
        TListaCalendario SumarSubl(int, int, const TListaCalendario &, int, int);
        // Extraer un rango de nodos en una nueva lista.
        TListaCalendario ExtraerRango(int, int);
};

#endif