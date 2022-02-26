// FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <queue>
#include <tuple>

using namespace std;
using namespace chrono;

size_t expanded_nodes, discarded_nodes, completed_nodes, added_nodes;
size_t discarded_promising_nodes, no_feasible_discarded_nodes, no_promising_discarded_nodes;
size_t current_best_updates_from_completed_nodes, current_best_updates_from_pessimistic_bounds;


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

int opt_b(const vector<int> &v, unsigned k, int T)
{
    int acc_v = 0;

    for(unsigned int i=k;i<v.size();i++) {
        if(v[i] > T) {
            acc_v += T;
            break;
        }
        acc_v += v[i];
        T -= v[i];
    }
    return acc_v;
}

int knapsack_d(const vector<int> &v, unsigned k, int T)
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

int RyP(const vector<int> &valores, int T)
{
    typedef vector<int> Sol;
    //         opt_bound, value, x, k
    typedef tuple<int, int, Sol, unsigned> Node; // ponemos la variable opt_bound para que la cola de prioridad ordene por el valor de la cota optimista.
    priority_queue< Node > pq; // priority queue = max-heap

    vector<int> v(valores.size());
    for(size_t i = 0;i<v.size();i++) v[i] = i;
    
    sort(v.begin(), v.end(), [&valores] (size_t x, size_t y){
        return valores[x] > valores[y];
    });

    vector<int> sorted_v(valores.size());
    for(size_t j=0;j<valores.size();j++) sorted_v[j] = valores[v[j]];


    int best_val = knapsack_d(sorted_v, 0, T);
    int opt_bound = opt_b(sorted_v, 0, T);

    pq.emplace(opt_bound, 0, Sol(sorted_v.size()), 0);

    while(!pq.empty()){
        int value;
        Sol x;
        unsigned k;
        tie(ignore,value,x,k) = pq.top();
        pq.pop();

        if(value == T) continue; // Si tenemos el valor máximo dejamos de buscar.

        int opt_bound = value + opt_b(sorted_v,k+1,T-value);
        if(opt_bound <= best_val){ // if it's not promising
            discarded_promising_nodes++; //nº de nodos que fueron prometedores, pero que finalmente se descartaron
        }
    
        if(k == v.size()){
            completed_nodes++; // nº de nodos completados
            if(value >= best_val){ // Actualizado la mejor solución con nodo completado?
                //nº de veces que la mejor solución hasta el momento se ha actualizado a partir de un nodo completado
                current_best_updates_from_completed_nodes++;
                best_val = max(best_val, value);
            }
            continue;
        }

        expanded_nodes++; // nº de nodos que han sido expandidos

        for(unsigned j=0;j<2;j++){
            x[k] = j;

            int new_value = value + x[k] * sorted_v[k];

            if(new_value <= T){ // is feasible
                //nº de veces que le mejor solución hasta el momento se ha actualizado a partir de la cota pesimista de un nodo sin completar.
                int actualMejor = best_val;
                best_val = max(best_val, new_value + knapsack_d(sorted_v,k+1,T-new_value));
                if(actualMejor != best_val){
                    current_best_updates_from_pessimistic_bounds++; 
                }

                int opt_bound = new_value + opt_b(sorted_v,k+1,T-new_value);

                if(opt_bound > best_val){ // is promising
                    // nº de nodos añadidos a la lista de nodos vivos.
                    pq.emplace(opt_bound, new_value, x, k+1);
                    added_nodes++;
                }
                else{
                    no_promising_discarded_nodes++; // nº de nodos descartados por no ser prometedores
                }
            }
            else{
                no_feasible_discarded_nodes++; // nº de nodos descartados por no ser factibles.
            }
        }
    }
    return best_val;
}

int main(int argc, char* argv[])
{
    int n, T, ramYpod;
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
    ramYpod = RyP(valores, T);
    auto end = clock();

    cout << ramYpod << endl;

    cout << expanded_nodes << " " << added_nodes << " " << no_feasible_discarded_nodes << " ";
    cout << no_promising_discarded_nodes << " " << discarded_promising_nodes << " " << completed_nodes << " ";
    cout << current_best_updates_from_completed_nodes << " " << current_best_updates_from_pessimistic_bounds << endl;
    cout << 1000.0 * (end-start) / CLOCKS_PER_SEC << endl;
    return 0;
}