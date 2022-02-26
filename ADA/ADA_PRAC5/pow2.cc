// # FRANCISCO JAVIER PEREZ MARTINEZ   DNI: 74384305M
#include <iostream>
#include <iomanip>
using namespace std;

unsigned long llamadasRecursivas_pow2_1;
unsigned long llamadasRecursivas_pow2_2;
unsigned long llamadasRecursivas_pow2_3;

//Complejidad de n
unsigned long pow2_1(unsigned n)
{
    llamadasRecursivas_pow2_1++;
    unsigned long rec;

    if(n == 0) {
        rec = 1;
    }
    else {
        if(n > 0) {
            rec = (2 * pow2_1(n - 1));
        }
    }
    return rec;
}

//Complejidad de 2^n
unsigned long pow2_2(unsigned n)
{
    llamadasRecursivas_pow2_2++;
    unsigned long rec;

    if(n == 0) {
        rec = 1;
    }
    else {
        if(n > 0) {
            if(n % 2 == 0) {
                rec =  (pow2_2(n/2) * pow2_2(n/2));
            }
            else {
                rec  = (2 * pow2_2(n/2) * pow2_2(n/2));
            }
        }
    }
    return rec;
}

//Complejidad de log(n)
unsigned long pow2_3(unsigned n)
{
    llamadasRecursivas_pow2_3++;
    unsigned long rec;
    unsigned long x;

    if(n == 0) {
        rec = 1;
    }
    else {
        if(n > 0) {
            x = pow2_3(n/2);
            if(n % 2 == 0) {
                rec =  x * x;
            }
            else {
                rec = 2 * x * x;
            }
        }
    }
    return rec;
}

int main()
{
    cout << "#===================================" << endl;
    cout << setw(4) << "n" << std::flush;
    cout << setw(12) << "pow2_1" << std::flush;
    cout << setw(10) << "pow2_2" << std::flush;
    cout << setw(10) << "pow2_3" << std::flush;
    cout << endl;
    cout << "#===================================" << endl;

    for(unsigned int i=0;i<=200; i++){

        llamadasRecursivas_pow2_1 = 0;
        llamadasRecursivas_pow2_2 = 0;
        llamadasRecursivas_pow2_3 = 0;

        pow2_1(i);
        pow2_2(i);
        pow2_3(i);

        cout << setw(4) << i << std::flush;
        cout << setw(10) << llamadasRecursivas_pow2_1 << std::flush;
        cout << setw(10) << llamadasRecursivas_pow2_2 << std::flush;
        cout << setw(10) << llamadasRecursivas_pow2_3 << std::flush;
        cout << endl;
    }
    
    return 0;
}