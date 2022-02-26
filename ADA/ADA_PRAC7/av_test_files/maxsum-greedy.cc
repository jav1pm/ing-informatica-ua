// FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

const int SENTINEL = -1;

vector<int> selection;

void readFile(string filename, int &n, int &T, vector<int> &valores)
{
    ifstream file(filename);
    int Vi;

    if(file.is_open()) {
        file >> n; // Nº de artículos.
        file >> T; // Umbral

        while(file >> Vi) valores.push_back(Vi); // Valores
        file.close();
    }
    else {
        cout << "ERROR: can't open file: " << filename << "." << endl;
        cout << "Usage:" << endl;
        cout << "maxsum-greedy -f file" << endl;
        exit(-1);
    }
}

int Greedy(const vector<int> &v, int n, int T)
{
    vector<int> vAux(n);
    vector<size_t> idx(v.size());
    for(size_t i = 0; i < idx.size(); i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&v] (size_t x, size_t y) {
        return v[x] > v[y];
    } );

    int acc_v = 0;

    for(auto i : idx) {
        if(v[i] < T) {
            acc_v += v[i];
            T -= v[i];
            if(v[i] != 0){
                vAux[i] = v[i];
                selection = vAux;
            }
        }
    }
    return acc_v;
}

/*
    Función auxiliar para mostrar los valores seleccionados.
*/
void showSelection(const vector<int> &v)
{
    for(unsigned int i = 0;i<v.size();i++){
        if(selection[i] != 0) {
            cout << selection[i] << " ";
        }
    }
    cout << endl;
}

/*
    Función auxiliar que suma todos los valores seleccionados para comprobar que nuestro algoritmo voraz está correcto.
*/
int selectionValue(const vector<int> &v)
{
    int value = 0;

    for(unsigned int i=0;i<v.size();i++){
        if(selection[i] != 0){
            value += selection[i];
        }
    }
    return value;
}

int main(int argc, char* argv[])
{
    int n, T;
    vector<int> valores;
    string readArgument, filename;

    for(int i=1; i<argc;i++) {
        readArgument = argv[i];

        if(readArgument == "-f") {
            if(i + 1 < argc) {
                filename = argv[i + 1];
                i++;
            }
        }

        if(readArgument != "-f") {
            cout << "ERROR: unknown option " << argv[i] << "." << endl;
            cout << "Usage: " << endl;
            cout << "maxsum-greedy -f file" << endl;
            exit(-1);
        }
    }
    readFile(filename, n, T, valores); // Leer fichero.
    cout << "Greedy: " << Greedy(valores, n, T) << endl;
    cout << "Selection: ";
    showSelection(valores); // Mostrar los valores seleccionados.
    cout << "Selection value: " << selectionValue(valores) << endl;
    return 0;
}