#include "tavlcalendario.h"

//   TNodoAVL

TNodoAVL::TNodoAVL() : item(), iz(), de()
{
    fe = 0;
}

TNodoAVL::TNodoAVL(const TNodoAVL &tn) : item(tn.item), iz(tn.iz), de(tn.de)
{
    fe = tn.fe;
}

TNodoAVL::~TNodoAVL()
{
    fe = 0;
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &tn)
{
    if(this != &tn){
        this->~TNodoAVL();
        iz = tn.iz;
        de = tn.de;
        item = tn.item;
        fe = tn.fe;
    }
    return *this;
}

// TAVLCalendario

bool TAVLCalendario::EsVacio() const
{
    return (raiz == NULL);
}

TCalendario TAVLCalendario::Raiz() const
{
    TCalendario aux;

    if(raiz != NULL){
        aux = raiz->item;
    }
    return aux;
}

void TAVLCalendario::InordenAux(TVectorCalendario &tvc, int &pos) const
{
    if(raiz != NULL){
        (raiz->iz).InordenAux(tvc, pos);
        tvc[pos] = Raiz();
        pos++;
        (raiz->de).InordenAux(tvc, pos);
    }
}

void TAVLCalendario::PreordenAux(TVectorCalendario &tvc, int &pos) const
{
    if(raiz != NULL){
        tvc[pos] = Raiz();
        pos++;
        (raiz->iz).PreordenAux(tvc, pos);
        (raiz->de).PreordenAux(tvc, pos);
    }
}

void TAVLCalendario::PostordenAux(TVectorCalendario &tvc, int &pos) const
{
    if(raiz != NULL){
        (raiz->iz).PostordenAux(tvc, pos);
        (raiz->de).PostordenAux(tvc, pos);
        tvc[pos] = Raiz();
        pos++;
    }
}

TAVLCalendario::TAVLCalendario()
{
    raiz = NULL;
}

void TAVLCalendario::Copiar(const TAVLCalendario &tavl)
{
    if(tavl.raiz != NULL){
        TNodoAVL *aux = new TNodoAVL();
        aux->item = tavl.raiz->item;
        aux->fe = tavl.raiz->fe;
        raiz = aux;
        (raiz->iz).Copiar(tavl.raiz->iz);
        (raiz->de).Copiar(tavl.raiz->de);
    }
    else raiz = NULL;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &tavl)
{
    if(this != &tavl) Copiar(tavl);
}

TAVLCalendario::~TAVLCalendario()
{
    if(raiz != NULL){
        delete raiz;
        raiz = NULL;
    }
}

TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &tavl)
{
    if(this != &tavl){
        this->~TAVLCalendario();
        Copiar(tavl);
    }
    return *this;
}

int TAVLCalendario::Altura() const
{
    int a1 = 0, a2 = 0;
    
    if(EsVacio()){
        return 0;
    }
    else {
        a1 = (raiz->iz).Altura();
        a2 = (raiz->de).Altura();
        return (1 + (a1 < a2 ? a2 : a1));
    }
}

int TAVLCalendario::Nodos() const
{
    if(EsVacio()){
        return 0;
    }
    else {
        return (1 + (raiz->iz).Nodos() + (raiz->de).Nodos());
    }
}

int TAVLCalendario::NodosHoja() const
{
    if(EsVacio()){
        return 0;
    }
    else {
        if((raiz->iz).EsVacio() && (raiz->de).EsVacio()){
            return 1;
        }
        else {
            return (raiz->iz).NodosHoja() + (raiz->de).NodosHoja();
        }
    }
}

bool TAVLCalendario::operator==(const TAVLCalendario &tavl)
{
    TVectorCalendario vIZ = Inorden();
    TVectorCalendario vDE = tavl.Inorden();

    if(vIZ == vDE){
        return true;
    }
    return false;
}

bool TAVLCalendario::operator!=(const TAVLCalendario &tavl)
{
    return !(*this == tavl);
}

/**
 *  Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario.
 */
bool TAVLCalendario::Buscar(const TCalendario &cal) const
{
    if(EsVacio()){
        return false;
    }
    if(raiz->item == cal){
        return true;
    }
    else{
        return (raiz->iz).Buscar(cal) || (raiz->de).Buscar(cal);
    }
}

void TAVLCalendario::ActualizarFE()
{
    if(!EsVacio()){
        // Actualización del FE
        raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
        raiz->iz.ActualizarFE();
        raiz->de.ActualizarFE();
    }
}

void TAVLCalendario::DD()
{
    TNodoAVL* j;

    //Mover (J, HijoDe(I));
    j = raiz->de.raiz;
    raiz->de.raiz = NULL;

    //Mover (HijoDe(I), HijoIz(J));
    raiz->de.raiz = j->iz.raiz;
    j->iz.raiz = NULL;

    // Mover (HijoIz (J), I);
    j->iz.raiz = raiz;
    raiz = NULL;

    //FE (J) = 0; FE (HijoIz (J)) = 0;
    j->fe = 0; 
    j->iz.raiz->fe = 0;

    //Mover (I,J);
    raiz = j;
    j = NULL;
}

void TAVLCalendario::DI()
{
    TNodoAVL* j;
    TNodoAVL* k;
    int E2;

    //Mover (J, HijoDe (I));
    j = raiz->de.raiz;
    raiz->de.raiz= NULL;

    //Mover (K, HijoIZ (J));
    k = j->iz.raiz;
    j->iz.raiz= NULL;

    //E2 = FE (K);
    E2 = k->fe;

    //Mover (HijoDE (I), HijoIz(K));
    raiz->de.raiz = k->iz.raiz;
    k->iz.raiz = NULL;

    //Mover (HijoIz (J), HijoDe(K));
    j->iz.raiz = k->de.raiz;
    k->de.raiz= NULL;

    //Mover (HijoDe (K), J);
    k->de.raiz = j;
    j = NULL;

    //Mover (HijoIz (K), I);
    k->iz.raiz= raiz;
    raiz= NULL;

    //FE (K) = 0;
    k->fe= 0;

    switch(E2)
    {
        case -1:
            k->de.raiz->fe= 1;
            k->iz.raiz->fe= 0;
            break;
        case 1:
            k->de.raiz->fe= 0;
            k->iz.raiz->fe= -1;
            break;
        case 0:
            k->de.raiz->fe= 0;
            k->iz.raiz->fe= 0;
            break;
    }

    //Mover (I, K);
    raiz = k;
    k = NULL;
}

void TAVLCalendario::II()
{
    TNodoAVL* j;

    // Mover (J, HijoIzq (I));
    j = raiz->iz.raiz;
    raiz->iz.raiz = NULL;

    // Mover (HijoIzq (I), HijoDer(J));
    raiz->iz.raiz = j->de.raiz;
    j->de.raiz = NULL;

    // Mover (HijoDer (J), I)
    j->de.raiz = raiz; 
    raiz = NULL;

    // FE (J) = 0; FE (HijoDer (J))=0;
    j->fe = 0;
    j->de.raiz->fe = 0;

    // Mover (I,J);
    raiz = j;
    j = NULL;
}

void TAVLCalendario::ID()
{
    TNodoAVL* j;
    TNodoAVL* k;
    int E2;
    
    // Mover (J, HijoIzq (I));
    j = raiz->iz.raiz;
    raiz->iz.raiz = NULL;

    // Mover (K, HijoDer (J));
    k = j->de.raiz;
    j->de.raiz = NULL;

    // E2 = FE (K);
    E2 = k->fe;

    // Mover (HijoIzq (I), HijoDer(K));
    raiz->iz.raiz = k->de.raiz;
    k->de.raiz = NULL;

    // Mover (HijoDer (J), HijoIzq(K));
    j->de.raiz = k->iz.raiz;
    k->iz.raiz = NULL;

    // Mover (HijoIzq (K), J); 
    k->iz.raiz = j; 
    j = NULL;

    // Mover (HijoDer (K), I);
    k->de.raiz = raiz;
    raiz = NULL;
    
    // FE (K) = 0;
    k->fe = 0;

    switch (E2)
    {
    case -1:
        // FE (HijoIzq (K)) = 0; FE (HijoDer (K)) = 1;
        k->iz.raiz->fe = 0;
        k->de.raiz->fe = 1;
        break;
    case +1:
        // FE (HijoIzq (K)) = -1; FE (HijoDer (K)) = 0;
        k->iz.raiz->fe = -1;
        k->de.raiz->fe = 0;
        break;
    case 0:
        // FE (HijoIzq (K)) = 0; FE (HijoDer (K)) = 0;
        k->iz.raiz->fe = 0;
        k->de.raiz->fe = 0;
        break;
    }
    // Mover (I, K);
    raiz = k;
    k = NULL;
}

void TAVLCalendario::Equilibrar()
{
    if(!raiz->iz.EsVacio()){
        raiz->iz.Equilibrar();
    }

    if(!raiz->de.EsVacio()){
        raiz->de.Equilibrar();
    }

    // Nodo hoja
    switch(raiz->fe){
        case 2:
            if(raiz->de.raiz->fe == 0 || raiz->de.raiz->fe == 1){
                DD();
            }
            else if(raiz->de.raiz->fe == -1){
                DI();
            }
            break;
        case -2:
            if(raiz->iz.raiz->fe == 0 || raiz->iz.raiz->fe == -1){
                II();
            }
            else if(raiz->iz.raiz->fe ==  1){
                ID();
            }
            break;
    }
}

bool TAVLCalendario::InsertarAux(const TCalendario &cal, bool &crece)
{
    bool creceHijoIz = false, creceHijoDe = false, insercionOK = false;

    if(Buscar(cal)){
        return false;
    }

    if(EsVacio()){
        TNodoAVL *nodo = new TNodoAVL();
        raiz = nodo;
        raiz->item = cal;
        raiz->fe = 0;
        crece = true;
        insercionOK = true;
    }
    else{
        // Si el Calendario de la raiz es menor que el dado se procede con el hijo izquierdo.
        if(cal < raiz->item){
            //si cal debe insertarse en el hijo izquierdo
            insercionOK = raiz->iz.InsertarAux(cal, creceHijoIz);
        }
        else{ // proceder con el hijo derecho.
            //si cal debe insertarse en el hijo derecho
            insercionOK = raiz->de.InsertarAux(cal, creceHijoDe);
        }

        //Actualización de factores de equilibrio
        if(insercionOK){
            ActualizarFE();
            Equilibrar();
        }
    }
    return insercionOK;
}

bool TAVLCalendario::Insertar(const TCalendario &cal)
{
    bool crece = false;
    return InsertarAux(cal, crece);
}

TCalendario TAVLCalendario::mayorIz()
{
    TCalendario cal;

    if(EsVacio()) {
        return cal;
    }
    else{
        if((raiz->de).EsVacio()){
            cal = raiz->item;
        }
        else {
            cal = raiz->de.mayorIz();
        }
    }
    return cal;
}

bool TAVLCalendario::BorrarAux(const TCalendario &cal, bool &decrece)
{
    bool decreceHijoIz = false, decreceHijoDe = false, borradoOK = false;
    TCalendario mayorIz;
    TNodoAVL *nodo;
    
    if(EsVacio()){
        return false;
    }
    else{
        if(cal < raiz->item){ // Si el calendario dado es menor
        borradoOK = raiz->iz.BorrarAux(cal, decreceHijoIz); // Buscamos por la izq
        }
        else if(cal > raiz->item){ // Si el calendario dado es mayor
            borradoOK = raiz->de.BorrarAux(cal, decreceHijoDe); // Buscamos por la der
        }
        else{ // Si ya se encontró el calendario...
            borradoOK = true;
            // Si el calendario es la raiz y no tiene ni hijo izq ni der (nodo hoja)...
            if((raiz->iz).EsVacio() && (raiz->de).EsVacio()){
                delete raiz;
                raiz = NULL;
                decrece = borradoOK = true;
                return borradoOK;
            }
            // Si solo tiene hijo izq
            else if(!(raiz->iz).EsVacio() && (raiz->de).EsVacio()){
                nodo = raiz;
                raiz = (raiz->iz).raiz; // primero sustituimos el hijo izq
                nodo->iz.raiz = NULL;
                delete nodo; // despues borramos
                nodo = NULL;
                decrece = borradoOK = true;
            }
            // Si solo tiene hijo der
            else if((raiz->iz).EsVacio() && !(raiz->de).EsVacio()){
                nodo = raiz;
                raiz = (raiz->de).raiz; // primero sustituimos el hijo der
                nodo->de.raiz = NULL;
                delete nodo; // despues borramos
                nodo = NULL;
                decrece = borradoOK = true;
            }
            // Tiene dos hijos (izq y der)
            else{
                mayorIz = raiz->iz.mayorIz(); // obtenemos el maximo hijo izq
                raiz->item = mayorIz; // sustituimos
                borradoOK = raiz->iz.BorrarAux(mayorIz, decreceHijoIz);
            }
        }
    }
    //Actualización de factores de equilibrio
    if(borradoOK){
        ActualizarFE();
        Equilibrar();
    }

    return borradoOK;
}

bool TAVLCalendario::Borrar(const TCalendario &cal)
{
    bool decrece = false;
    return BorrarAux(cal, decrece);
}

TVectorCalendario TAVLCalendario::Inorden() const
{
    int pos = 1;

    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCalendario v(Nodos());
    InordenAux(v, pos);
    return v;
}

TVectorCalendario TAVLCalendario::Preorden() const
{
    int pos = 1;

    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCalendario v(Nodos());
    PreordenAux(v, pos);
    return v;
}

TVectorCalendario TAVLCalendario::Postorden() const
{
    int pos = 1;

    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorCalendario v(Nodos());
    PostordenAux(v, pos);
    return v;
}

ostream& operator<<(ostream &os, const TAVLCalendario &tavl)
{
    os << tavl.Inorden();
    return os;
}