// FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <numeric>

using namespace std;
using namespace chrono;

vector<unsigned> selection;
size_t expanded_nodes, discarded_nodes;

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
        cout << "maxsum-bt -f file" << endl;
        exit(-1);
    }
}

int knapsack_c(const vector<int> &v, size_t k, int T)
{
    int acc_v = 0;

    for(unsigned int i=k;i<v.size();i++) {
        if(v[i] > T) {
            acc_v += T/v[i] * v[i];
            break;
        }
        acc_v += v[i];
        T -= v[i];
    }
    return acc_v;
}

int knapsack_d(const vector<int> &v, size_t k, int T)
{
    int acc_v = 0;

    for(unsigned int i=k;i<v.size();i++) {
        if(v[i] < T) {
            acc_v += v[i];
            T -= v[i];
        }
    }
    return acc_v;
}

void Backtracking(const vector<int> &v, int T, size_t k, vector<unsigned> &x, int acc_v, int &best_v)
{
    if(k == x.size() || best_v >= T){ // if it's a leaf
        best_v = max(best_v, acc_v);
        if(k == x.size()){
            selection = x;
        }
        return;
    }
    for(unsigned j=0;j<2;j++){ // it is not a leaf
        x[k] = j;
        int present_v = acc_v + x[k] * v[k]; // update value
        
        if(present_v <= T && present_v + knapsack_c(v, k+1, T) > best_v){ // if is feasible and is promising
            expanded_nodes++;
            Backtracking(v, T, k+1, x, present_v, best_v);
        }
        else {
            discarded_nodes++;
        }
    }
}

int Backtracking(vector<int> &v, int T)
{
    vector<int> idx(v.size());
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx), [&v] (int x, int y){
        return v[x] > v[y];
    });

    vector<int> sorted_values(v.size());

    for(size_t i=0;i<v.size();i++){
        sorted_values[i] = v[idx[i]]; // valores ordenados.
    }

    vector<unsigned> x(v.size());
    int best_v = knapsack_d(v,0,T);
    Backtracking(sorted_values, T, 0, x, 0, best_v);
    v = sorted_values;
    return best_v;
}

/*
    Función auxiliar para mostrar los valores seleccionados.
*/
void showSelection(const vector<int> &v)
{
    for(unsigned int i = 0;i<v.size();i++){
        if(selection[i] == 1) {
            cout << v[i] << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    int n, T, backT;
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
            cout << "maxsum-bt -f file" << endl;
            exit(-1);
        }
    }

    readFile(filename, n, T, valores); // Leer fichero.
    
    auto start = clock();
    backT = Backtracking(valores, T);
    auto end = clock();

    cout << "Backtracking: " << backT << endl;
    cout << "Selection: ";
    showSelection(valores); // Mostrar los valores seleccionados.
    cout << "Expanded nodes: " << expanded_nodes <<endl;
    cout << "Discarded nodes: " << discarded_nodes << endl;

    cout << "CPU time (ms): " << 1000.0 * (end-start) / CLOCKS_PER_SEC << endl;
    return 0;
}