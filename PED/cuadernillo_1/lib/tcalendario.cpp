#include "tcalendario.h"

TCalendario::TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

/**
 * Comprobamos si fecha es correcta:
 * - Número correcto de días y meses
 * - Control de años bisiestos
 */
TCalendario::TCalendario(int d, int m, int a, char * mens)
{
    mensaje = NULL;
    
    if(!ModFecha(d,m,a)){ // Si fecha INCORRECTA...
        this->dia = 1;
        this-> mes = 1;
        this->anyo = 1900;
    } 
    else {
        ModMensaje(mens);
    }
}

TCalendario::TCalendario(const TCalendario &cal)
{
    dia = cal.dia;
    mes = cal.mes;
    anyo = cal.anyo;
    mensaje = NULL;
    ModMensaje(cal.mensaje);
}

TCalendario::~TCalendario()
{
    dia = 1;
    mes = 1;
    anyo = 1900;

    if(mensaje != NULL) {
        delete[] mensaje;
        mensaje = NULL;
    }
}

char * TCalendario::Mensaje()
{
    return mensaje == NULL ? NULL : this->mensaje;
}

bool TCalendario::EsVacio()
{
    return (dia == 1  && mes == 1 && anyo == 1900 && mensaje == NULL);
}

bool TCalendario::EsBisiesto()
{
    return (anyo % 4 == 0 && (anyo % 400 == 0 || anyo % 100 != 0));
}

bool TCalendario::ModMensaje(char * mens)
{
    if(mensaje != NULL){
        delete[] mensaje;
        mensaje = NULL;
    }
    
    if(mens != NULL) {
        mensaje = new char[strlen(mens) + 1];
        strcpy(mensaje, mens);
    }
    return true;
}

/**
 * Función que obtiene los dias de cada mes.
 */
int TCalendario::ObtenerDiasDelMes(int mes)
{
    int dias;
    switch (mes){
    case 2:
        if(EsBisiesto()) {
            dias = 29; // Febrero con 29 dias si es bisiesto.
        } 
        else {
            dias = 28;
        }
        break;
    case 4: 
        dias = 30; break;
    case 6:
        dias = 30; break;
    case 9:
        dias = 30; break;
    case 10:
        dias = 30; break;
    default:
        dias = 31;
        break;
    }
    return dias;
}

/**
 * Función que comprueba que una fecha sea correcta.
 */
bool TCalendario::FechaCorrecta()
{
    if(dia >= 1 && dia <= ObtenerDiasDelMes(mes) && mes >= 1 && mes <= 12 && anyo >= 1900){
        return true;
    }
    return false;
}

/**
 * Función que corrige una fecha.
 */
void TCalendario::FixDate()
{
    bool fix = false;

    while(!fix){
        int diasMes = ObtenerDiasDelMes(mes);

        if(dia >= 1 && dia <= diasMes) fix = true; //Fecha correcta
        else if (dia < 1){
            int diasMesAnterior = ObtenerDiasDelMes(mes-1);
            dia += diasMesAnterior;

            if(mes==1){ //Si es Enero
                mes = 12; // Diciembre
                anyo--; // Año anterior
            }
            else{
                mes--; // Mes anterior
            }
        }
        else if (dia > diasMes){
            dia -= diasMes;

            if(mes == 12){ // Si es Diciembre
                mes = 1; // Enero
                anyo++; // Año siguiente
            }
            else{
                mes++; // Mes siguiente
            }
        }
    }
}

bool TCalendario::ModFecha(int d, int m, int a)
{
    bool modified = false;

    TCalendario aux;
    aux.dia = d;
    aux.mes = m;
    aux.anyo = a;

    if(aux.FechaCorrecta()){
        dia = d;
        mes = m;
        anyo = a;
        modified = true;
    }
    return modified;
}

TCalendario & TCalendario::operator=(const TCalendario &cal)
{
    if(this != &cal) { //Comprobamos antes de realizar la copia en la asignación que no se trata del mismo objeto.
        this->~TCalendario();

        dia = cal.dia;
        mes = cal.mes;
        anyo = cal.anyo;

        ModMensaje(cal.mensaje);
    }
    return *this;
}

bool TCalendario::operator==(const TCalendario &cal) const
{
    if(dia == cal.dia && mes == cal.mes && anyo == cal.anyo) {
        if(mensaje == NULL && cal.mensaje == NULL){
            return true;
        }
        else{
            if(cal.mensaje != NULL && mensaje != NULL){
                if(strcmp(mensaje, cal.mensaje) == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool TCalendario::operator!=(const TCalendario &cal) const
{
    return !(*this == cal);
}

TCalendario TCalendario::operator+(const int suma)
{
    TCalendario temp(*this);

    if(suma > 0){
        temp.dia = dia + suma;
        // Si la fecha no es correcta, la corregimos.
        if(!temp.FechaCorrecta()) temp.FixDate();
    }
    return temp;
}

TCalendario TCalendario::operator-(const int resta)
{
    TCalendario temp(*this);

    if(resta > 0){
        temp.dia = dia - resta;
        temp.FixDate();
        
        // Si fecha no correcta => 1/1/1900 Mensaje=NULL
        if(!temp.FechaCorrecta()) temp.~TCalendario();
    }
    return temp;
}

TCalendario TCalendario::operator++(int post)
{
    TCalendario temp(*this);

    dia++;
    // Si la fecha no es correcta, la corregimos.
    if(!FechaCorrecta()) FixDate();
    return temp;
}

TCalendario & TCalendario::operator++()
{
    dia++;
    // Si la fecha no es correcta, la corregimos.
    if(!FechaCorrecta()) FixDate();
    return (*this);
}

TCalendario TCalendario::operator--(int post)
{
    TCalendario temp(*this);
    
    dia--;
    FixDate();
    // Si fecha no correcta => 1/1/1900 Mensaje=NULL
    if(!FechaCorrecta()) this->~TCalendario();
    return temp;
}

TCalendario & TCalendario::operator--()
{
    dia--;
    FixDate();
    // Si fecha no correcta => 1/1/1900 Mensaje=NULL
    if(!FechaCorrecta()) this->~TCalendario();
    return (*this);
}

bool TCalendario::operator>(const TCalendario &cal) const
{
    bool mayor = false;
    if(anyo > cal.anyo){
        mayor = true;
    }
    else if(anyo == cal.anyo){
        if(mes > cal.mes){
            mayor = true;
        }
        else if(mes == cal.mes){
            if(dia > cal.dia){
                mayor = true;
            }
            else if(dia == cal.dia){
                if(mensaje == NULL && cal.mensaje == NULL){
                    mayor = false;
                }
                else if(mensaje != NULL && cal.mensaje == NULL){
                    mayor = true;
                }
                else if(mensaje == NULL && cal.mensaje != NULL){
                    mayor = false;
                }
                else{
                    if(strcmp(mensaje, cal.mensaje) > 0){
                        mayor = true;
                    }
                    else {
                        mayor = false;
                    }
                }
            }
        }
    }
    return mayor;
}

bool TCalendario::operator<(const TCalendario &cal) const
{
    return !(*this > cal || *this == cal);
}

ostream & operator<<(ostream &os, const TCalendario &tc)
{
    if(tc.dia < 10) os << "0";
    os << tc.dia << "/";

    if(tc.mes < 10) os << "0";
    os << tc.mes << "/" << tc.anyo << " \"";

    if(tc.mensaje != NULL) os << tc.mensaje;
    os << "\"";
    
    return os;
}