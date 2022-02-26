#include "tvectorcalendario.h"

TVectorCalendario::TVectorCalendario()
{
    this->tamano = 0;
    this->c = NULL;
}

TVectorCalendario::TVectorCalendario(int tam)
{
    if(tam < 0){
        this->tamano = 0;
        this->c = NULL;
    }
    else {
        this->tamano = tam;
        this->c = new TCalendario[tam];
    }
}

void TVectorCalendario::Copia(const TVectorCalendario &v)
{
    if(c != NULL){
        delete[] c;
        c = NULL;
    }

    tamano = v.tamano;

    if(tamano > 0 && v.c != NULL){
        c = new TCalendario[v.tamano];
        for(int i = 0; i < tamano; i++){
            c[i] = v.c[i];
        }
    }
    else{
        c = NULL;
        tamano = 0;
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &v)
{
    if(this != &v){
        tamano = 0;
        c = NULL;
        Copia(v);
    }
}

TVectorCalendario::~TVectorCalendario()
{
    tamano = 0;
    if(c != NULL){
        delete[] c;
        c = NULL;
    }
}

TVectorCalendario & TVectorCalendario::operator=(const TVectorCalendario &v)
{
    if(this != &v){
        this->~TVectorCalendario();
        Copia(v);
    }
    return *this;
}

bool TVectorCalendario::operator==(const TVectorCalendario &v)
{
    if(tamano != v.tamano){
        return false;
    }
    else{
        for(int i = 0; i < tamano; i++){
            if(c[i] != v.c[i]) 
            return false;
        }
    }
    return true;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &v)
{
    return !(*this == v);
}

// PARTE IZQUIERDA
TCalendario & TVectorCalendario::operator[](int indice)
{
    if(indice >=1 && indice <= tamano){
        return c[indice - 1];
    }
    else {
        return error;
    }
}

// PARTE DERECHA
TCalendario TVectorCalendario::operator[](int indice) const
{
    if(indice >=1 && indice <= tamano){
        return c[indice - 1];
    }
    else {
        return error;
    }
}

int TVectorCalendario::Ocupadas()
{
    int cant = 0;

    for(int i = 0; i < tamano; i++){
        if(!c[i].EsVacio()){
            cant++;
        }
    }
    return cant;
}

bool TVectorCalendario::ExisteCal(const TCalendario &cal)
{
    for(int i = 0; i < tamano; i++){
        if(c[i] == cal){
            return true;
        }
    }
    return false;
}

void TVectorCalendario::MostrarMensajes(int d, int m, int a)
{
    char mensaje[] = "";
    TCalendario aux(d, m, a, mensaje);
    cout << "[";
    if(aux.Mensaje() != NULL){
        for(int i = 0; i < tamano; i++){
            if(c[i].Dia() >= d && c[i].Mes() >= m && c[i].Anyo() >= a) {
                cout << c[i];
                if(i != tamano - 1){ // Separamos cada TCalendario
                    cout << ", ";
                }
            }
        }
    }
    cout << "]";
}

bool TVectorCalendario::Redimensionar(int tam)
{
    if(tamano == tam || tam <= 0){
        return false;
    }
    else{
        TVectorCalendario aux(tam);
        if(tam > tamano){
            for(int i = 0; i < tamano; i++){
                aux.c[i] = c[i];
            }
            for(int i = tamano; i < tam; i++){
                TCalendario vacio;
                aux.c[i] = vacio;
            }
        }
        else{
            for(int i = 0; i < tam; i++){
                aux.c[i] = c[i];
            }
        }
        Copia(aux);
        return true;
    }
}

ostream& operator<<(ostream &os, const TVectorCalendario &v)
{
    os << "[";
    for(int i = 0; i < v.tamano; i++){
        os << "(" << i+1 << ") " << v.c[i];

        if(i != v.tamano - 1){
            os << ", ";
        }
    }
    os << "]";
    return os;
}




