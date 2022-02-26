#include "tlistacalendario.h"

// TNodo

TNodoCalendario::TNodoCalendario()
{
    siguiente = NULL;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &n)
{
    if(this != &n){
        siguiente = NULL;
        c = n.c;
        siguiente = n.siguiente;
    }
}

TNodoCalendario::~TNodoCalendario()
{
    siguiente = NULL;
}

TNodoCalendario & TNodoCalendario::operator=(const TNodoCalendario &n)
{
    if(this != &n){
        this->~TNodoCalendario();
        c = n.c;
        siguiente = n.siguiente;
    }
    return *this;
}

// TListaPos

TListaPos::TListaPos()
{
    pos = NULL;
}

TListaPos::TListaPos(const TListaPos &tlp)
{
    if(this != &tlp){
        pos = tlp.pos;
    }
}

TListaPos::~TListaPos()
{
    pos = NULL;
}

TListaPos & TListaPos::operator=(const TListaPos &tlp)
{
    if(this != &tlp){
        this->~TListaPos();
        pos = tlp.pos;
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &tlp) const
{
    return (pos == tlp.pos);
}

bool TListaPos::operator!=(const TListaPos &tlp) const
{
    return !(*this == tlp);
}

TListaPos TListaPos::Siguiente()
{
    TListaPos tlp;

    if(!this->EsVacia()){
        tlp.pos = pos->siguiente;
    }
    return tlp;
}

bool TListaPos::EsVacia() const
{
    return (pos == NULL);

}

//TListaCalendario

/**
 *  Crea una lista vacía
 */
TListaCalendario::TListaCalendario()
{
    primero = NULL;
}

TListaCalendario::TListaCalendario(const TListaCalendario &tlc)
{
    primero = NULL;
    *this = tlc;
}

TListaCalendario::~TListaCalendario()
{
    TNodoCalendario *aux;
    
    while(!EsVacia()){
        aux = primero;
        primero = primero->siguiente;
        if(aux != NULL){
            delete aux;
            aux = NULL;
        }
    }
}

TListaCalendario & TListaCalendario::operator=(TListaCalendario const &tlc)
{
    if(this != &tlc){
        this->~TListaCalendario();
        TNodoCalendario *aux = tlc.primero;
        
        while(aux != NULL){
            Insertar(aux->c);
            aux = aux->siguiente; // avanzar
        }
    }
    return *this;
}

bool TListaCalendario::EsVacia() const
{
    return (primero == NULL);
}

TListaPos TListaCalendario::Primera() const
{
    TListaPos aux;

    if(!EsVacia()){
        aux.pos = primero;
    }
    return aux;
}

TListaPos TListaCalendario::Ultima() const
{
    TListaPos aux;

    if(!EsVacia()){
        TNodoCalendario *tn = primero;
        while(tn != NULL){
            if(tn->siguiente == NULL){
                aux.pos = tn;
            }
            tn = tn->siguiente; // avanzo por la lista
        }
    }
    return aux;
}

int TListaCalendario::Longitud() const
{
    int longitud = 0;
    TNodoCalendario *aux = primero;

    while(aux != NULL) {
        longitud ++;
        aux = aux->siguiente;
    }
    return longitud;
}

/**
 * Devolver el TCalendario apuntado por el objeto TListaPos, si es vacio, TCalendario vacio.
 */
TCalendario TListaCalendario::Obtener(const TListaPos &tlp) const
{
    TCalendario vacio;
    
    if(!tlp.EsVacia()) {
        return tlp.pos->c;
    }
    return vacio;
}

bool TListaCalendario::Buscar(const TCalendario &cal) 
{
    TNodoCalendario *aux = primero;

    while(aux != NULL){
        if(cal == aux->c){ // Si el calendario está en la lista...
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

bool TListaCalendario::operator==(const TListaCalendario &tlc)
{
    TListaPos first_tlc = tlc.Primera();
    TListaPos first = Primera();

    if(tlc.Longitud() != Longitud()){
        return false;
    }

    while(!first_tlc.EsVacia() && !first.EsVacia()){
        if(Obtener(first_tlc) == Obtener(first)){
            first_tlc = first_tlc.Siguiente();
            first = first.Siguiente();
        }
        else {
            return false;
        }
    }
    return true;
}

/**
 * Inserta el calendario en la lista de forma que se mantenga el orden de la misma. Se 
 * devuelve TRUE si el elemento se ha podido insertar (no existe previamente en la lista), y FALSE en 
 * caso contrario
 */
bool TListaCalendario::Insertar(const TCalendario &cal)
{
    if(!Buscar(cal)){ // Si el elemento no existe previamente en la lista podemos insertar

        TNodoCalendario *aux = new TNodoCalendario();
        aux->c = cal;

        if(primero != NULL){
            if(cal > primero->c){
                TNodoCalendario *rec = primero;
                TNodoCalendario *ante = primero;
                
                // Recorro la lista para ver donde lo meto
                while((cal > rec->c || cal == rec->c) && rec->siguiente != NULL){
                    ante = rec; // guardo el anterior
                    rec = rec->siguiente; // guardo el siguiente
                }

                // insertar al final
                if(cal > rec->c || cal == rec->c){
                    rec->siguiente = aux;
                }
                else { // insertar en medio
                    aux->siguiente = rec;
                    ante->siguiente = aux;
                }
            }
            else { // insertar al principio
                aux->siguiente = primero;
                primero = aux;
            }
        }
        else{ // insertar en lista vacia
            primero = aux;
        }
    }
    else {
        return false;
    }
    return true;
}

bool TListaCalendario::Borrar(const TCalendario &cal)
{
    bool borrar = false;

    if(!EsVacia() && Buscar(cal)){
        TNodoCalendario *aux;
        TNodoCalendario *ante = NULL;

        aux = primero;

        // Recorrer la lista.
        while(aux != NULL && aux->c != cal){
            ante = aux;
            aux = aux->siguiente;
        }

        if(aux == NULL) { // Elemento no encontrado.
            borrar = false;
        }
        else if(ante == NULL) { // Primer elemento de la lista.
            primero = primero->siguiente; //Apuntar al siguiente elemento de la lista.
            delete aux;
            aux = NULL;
            borrar = true;
        }
        else {
            ante->siguiente = aux->siguiente;
            delete aux;
            aux = NULL;
            borrar = true;
        }
    }
    return borrar;
}

bool TListaCalendario::Borrar(const TListaPos &tlp)
{
    bool borrar = false;
    if(!tlp.EsVacia()){
        borrar = Borrar(tlp.pos->c);
    }
    return borrar;
}

bool TListaCalendario::Borrar(int d, int m, int a)
{
    bool borrar = false;
    TCalendario cal(d, m, a, NULL);

    while(!EsVacia() && primero->c < cal){
        borrar = Borrar(primero->c);
    }
    return borrar;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2)
{
    TListaCalendario lista;
    TNodoCalendario *aux1, *aux2;

    aux1 = primero;

    if(n2 > Longitud()){
        n2 = Longitud();
    }
    if(n1 <= 0){
        n1 = 1;
    }
    if(n1 == n2){
        for(int i=1; aux1 != NULL && i < n1; i++){
            aux1 = aux1->siguiente;
        }
        lista.Insertar(aux1->c);
        Borrar(aux1->c);
    }
    else if(n1 > n2){
        return lista;
    }
    else{
        for(int i=1; aux1 != NULL && i < n1; i++){
            aux1 = aux1->siguiente;
        }
        for(int j=n1; aux1 != NULL && j <= n2; j++){
            aux2 = aux1;
            lista.Insertar(aux2->c);
            aux1 = aux1->siguiente;
            Borrar(aux2->c);
        }
    }
    return lista;
}

TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2)
{
    TListaCalendario lista1(*this);
    TListaCalendario lista2(L2);
    return lista1.ExtraerRango(I_L1, F_L1) + lista2.ExtraerRango(I_L2, F_L2);
}

TListaCalendario TListaCalendario::operator+(const TListaCalendario &tlc)
{
    TListaCalendario lista = *this;
    TNodoCalendario * aux = tlc.primero;

    while(aux != NULL){
        lista.Insertar(aux->c);
        aux = aux->siguiente;
    }
    return lista;
}

TListaCalendario TListaCalendario::operator-(const TListaCalendario &tlc)
{
    TListaCalendario lista = *this;
    TNodoCalendario * aux = tlc.primero;

    while(aux != NULL){
        lista.Borrar(aux->c);
        aux = aux->siguiente;
    }
    return lista;
}

ostream & operator<<(ostream &os, const TListaCalendario &tlc)
{
    TListaPos aux = tlc.Primera();

    os << "<";
    
    while(!aux.EsVacia()){
        os << tlc.Obtener(aux);
        aux = aux.Siguiente(); // avanzo
        if(!aux.EsVacia()){
            os << " ";
        }
    }
    os << ">";
    return os;
}