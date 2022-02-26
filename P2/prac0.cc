// DNI 74384305M PEREZ MARTINEZ, FRANCISCO JAVIER

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const unsigned kMATSIZE = 5;

//Ejercicio 1
void deleteChar(char str[], char c) {

    for(int i=0;str[i]!='\0';i++) {
        if(str[i] == c) {
            for(int j=i;str[j]!='\0';j++) {
                str[j] = str[j+1];
            }
            i = 0; //Empezamos a leer desde el principio.
        }
    }
}

//Ejercicio 2
unsigned factorial(unsigned n) {

    int prod = 1;

    for(unsigned int i=n;i>1;i--) {
        prod = prod * i;
    }
    return prod;
}

//Ejercicio 3
bool checkPassword(const char passWd[]) {
    
    bool check1 = false; // controlar si es una letra minúscula
    bool check2 = false; // controlar si es una letra mayúscula
    bool check3 = false; // controlar si es un dígito
    int tam = 0;

    while(passWd[tam]!= '\0') {
        tam++;
    }

    if(tam >= 8 && tam <= 12) {
        for(int j=0;j<tam;j++) {
            if(islower(passWd[j])) {
                check1 = true;
            }
            if(isupper(passWd[j])) {
                check2 = true;
            }
            if(isdigit(passWd[j])) {
                check3 = true;
            }
        }
    }
    if(tam == 16) {
        for(int k=0;k<tam;k++) {
            if(!isdigit(passWd[k])) {
                return false;
            }
        }
        return true;
    }
    if(check1 == true && check2 == true && check3 == true) { // si se cumple que las tres condiciones son verdades, entonces devuelve tru
        return true;
    }
    else {
        return false;
    }
}

//Ejercicio 4
int calculator(const int numbers[], unsigned size, const char operators[]) {

    int next = 0; // el siguiente numero para operar
    int  total= 0; // primer numero que cogemos e irá guardando el total de izq a der
    unsigned int i = 0;
    int j = 0;

    if(size == 1) { // si el tamaño del vector de numeros es 1, devuelve el primer número del vector.
        return numbers[0];
    }
    while(i<size && operators[j] != '\0') {
        if(i==0) {
            total = numbers[i]; //primer numero
            i++; // pasamos al siguiente
        }
        next = numbers[i]; // siguiente numero

        switch(operators[j]) {
            case '+':
                total += next;
                break;
            case '-':
                total -= next;
                break;
            case '*':
                total *= next;
                break;
            case '/':
                total /= next;
                break;
            default:
                    return total;
                break;
        }
        i++; // pasamos al siguiente numero
        j++; // pasamos al siguiente operador
    }
    return total;
}

//Ejercicio 5
unsigned buildNumber(const unsigned numbers[], unsigned size) {

    int pos = 0;
    int convert = 0;

    if(size == 0) {
        return 0;
    }
    for(unsigned int i=0;i<size;i++) {
        pos = numbers[i];
        convert = 10 * (pos + convert);
    }
    convert = convert / 10;
    return convert;
}

//Ejercicio 6
bool friends(unsigned x, unsigned y) {
    
    unsigned int amigaX = 0;
    unsigned int amigaY = 0;

    for(unsigned int i=1;i<x; i++) {
        if(x % i == 0 && x != 0) {
            amigaX = amigaX + i;
        }
    }
    for(unsigned int j=1;j<y;j++) {
        if(y % j == 0 && y!=0) {
            amigaY = amigaY + j;
        }
    }

    if(amigaX == y && amigaY == x) {
        return true;
    }
    else {
        return false;
    }
}

//Ejercicio 7
int sumNeighbors(int m[][kMATSIZE], int row, int column) {
    
    int suma = 0;
    int kSIZE = kMATSIZE;

    if( (row >= 0 && row <=kSIZE-1) && (column >= 0 && column <= kSIZE-1) ) {
        for(int i=-1;i<=1;i++) {
            for(int j=-1;j<=1;j++) {
                if( i+row >= 0 && j+column >= 0 && i+row < kSIZE && j+column < kSIZE) { // comprobamos que no se pase de los limites de la matriz
                    if(i+row!=row || j+column!=column) { //si no es igual a la coord que nos pasan, sumamos.
                        suma += m[i+row][j+column];
                    }
                }
            }
        }
        return suma;
    }
    else {
        return -1;
    }
}

//Ejercicio 8
void printX(int n) {

    if(n % 2 == 0 || n <= 0) {
        cout << "ERROR" << endl;
    }
    else {
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if((i==j) || (n-j==i+1)) {
                    cout << "X";
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
}