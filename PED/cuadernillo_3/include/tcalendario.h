#ifndef _TCALENDARIO_H_
#define _TCALENDARIO_H_

#include <iostream>
#include <string.h>

using namespace std;

class TCalendario {

    // Sobrecarga del operador salida
    friend ostream & operator<<(ostream &, const TCalendario &);

    private:

        int dia, mes, anyo;
        char* mensaje;

        bool EsBisiesto();
        bool FechaCorrecta();
        int ObtenerDiasDelMes(int);
        void FixDate();

    public:

        TCalendario();
        TCalendario(int, int, int,char *);
        TCalendario (const TCalendario &);
        ~TCalendario();

        TCalendario & operator=(const TCalendario &);
        TCalendario operator+(const int);
        TCalendario operator-(const int);
        TCalendario operator++(int);
        TCalendario & operator++();
        TCalendario operator--(int);
        TCalendario & operator--();

        bool ModFecha (int, int, int);
        bool ModMensaje(char *);

        bool operator==(const TCalendario &) const;
        bool operator!=(const TCalendario &) const;
        bool operator>(const TCalendario &) const;
        bool operator<(const TCalendario &) const;

        bool EsVacio();

        int Dia() {return dia;}
        int Mes() {return mes;}
        int Anyo(){return anyo;}
        char *Mensaje();
};

#endif