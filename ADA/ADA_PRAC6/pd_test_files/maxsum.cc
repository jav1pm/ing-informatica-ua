// FRANCISCO JAVIER PEREZ MARTINEZ  DNI: 74384305M
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

const int SENTINEL = -1;

vector<vector<int>> Table; // Variable global del almacen utilizada para mostrar la tabla.

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
        cout << "maxsum [-t] [--ignore_naive] -f file" << endl;
        exit(-1);
    }
}

void mostrarTabla(int n, int T)
{
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= T; j++) {
            cout << Table[i][j] << " ";
        }
        cout << endl;
    }
}

void Solutions(int sinAlmacen, int Memo, int iterativeTABLE, int iterativeVECTOR, bool checkNaive, bool checkF)
{
    if(checkF) {
        if(checkNaive); //Excluir solución recursiva sin almacén.
        else if(!checkNaive) {
            cout << "Naive: " << sinAlmacen << endl;
        }

        cout << "Memoization: " << Memo << endl;
        cout << "Iterative (table): " << iterativeTABLE << endl;
        cout << "Iterative (vector): " << iterativeVECTOR << endl;
    }
}

int Naive(int n, int T, const vector<int> &valores)
{   
    if(n == 0 || T == 0) return 0;

    int S1 = Naive(n-1, T, valores);
    int S2 = numeric_limits<int>::lowest();

    if(valores[n-1] <= T) {
        S2 = valores[n-1] + Naive(n-1, T-valores[n-1], valores);
    }
    return max(S1,S2);
}

int Memoization(int n, int T, const vector<int> &valores, vector<vector<int>> &storage)
{
    if(storage[n][T] != SENTINEL) return storage[n][T];
    if(n == 0 || T == 0) return storage[n][T] = 0;

    int S1 = Memoization(n-1, T, valores, storage);
    int S2 = numeric_limits<int>::lowest();

    if(valores[n-1] <= T) {
        S2 = valores[n-1] + Memoization(n-1, T-valores[n-1], valores, storage);
    }
    return storage[n][T] = max(S1,S2); // store and return the solution
}

int Memoization(int n, int T, const vector<int> &valores)
{
    vector<vector<int>> storage(n+1, vector<int>(T+1, SENTINEL)); // init.
    return Memoization(n, T, valores, storage);
}

int IterativoConAlmacenTABLA(int last_n, int last_T, const vector<int> &valores, bool showTable)
{
    vector<vector<int>> storage(last_n+1, vector<int>(last_T+1));

    for(int T = 0; T <= last_T; T++) storage[0][T] = 0; // no objects

    for(int n = 1; n <= last_n; n++) {
        for(int T = 1; T  <= last_T; T++) {
            int S1 = storage[n-1][T];
            int S2 = numeric_limits<int>::lowest();
            if(T >= valores[n-1]) {
                S2 = valores[n-1] + storage[n-1][T-valores[n-1]];
            }
            storage[n][T] = max(S1,S2);
        }
    }
    if(showTable == true) {
        Table = storage; // Guardamos en nuestro almacen global los resultados parciales.
        return storage[last_n][last_T];
    }
    else {
        return storage[last_n][last_T];
    }
}

int IterativoVECTOR(int last_n, int last_T, const vector<int> &valores)
{
    vector<int> v0(last_T+1);
    vector<int> v1(last_T+1);

    for(int T = 0; T <= last_n; T++) v0[T] = 0; // no objects

    for(int n = 1; n <= last_n; n++) {
        for(int T = 1; T <= last_T; T++) {
            int S1 = v0[T];
            int S2 = numeric_limits<int>::lowest();
            if(T >= valores[n-1]) {
                S2 = valores[n-1] + v0[T-valores[n-1]];
            }
            v1[T] = max(S1,S2);
        }
        swap(v0,v1);
    }
    return v0[last_T];
}

int SelectionValue(int last_n, int last_T, const vector<int> &valores, vector<vector<bool>> &trace)
{
    vector<vector<int>> storage(last_n+1, vector<int>(last_T+1));
    trace = vector<vector<bool>>(last_n+1, vector<bool>(last_T+1));

    for(int T = 0; T <= last_T; T++) {
        storage[0][T] = 0; // no objects
        trace[0][T] = false; // Don't take it
    }

    for(int n = 1; n <= last_n; n++) {
        for(int T = 1; T  <= last_T; T++) {
            int S1 = storage[n-1][T];
            int S2 = numeric_limits<int>::lowest();
            if(T >= valores[n-1]) {
                S2 = valores[n-1] + storage[n-1][T-valores[n-1]];
            }
            storage[n][T] = max(S1,S2);
            trace[n][T] = S2 > S1;
        }
    }
    return storage[last_n][last_T];
}

void Parse(const vector<int> &v, const vector<vector<bool>> &trace, vector<bool> &sol)
{
    int last_n = trace.size()-1;
    int T = trace[0].size()-1;

    for(int n = last_n; n > 0; n--) {
        if(trace[n][T]) {
            sol[n-1] = true;
            T -= v[n-1];
        }
        else {
            sol[n-1] = false;
        }
    }
}

void showSelection(vector<bool> sol, const vector<int> &valores)
{
    for(unsigned int i = 0;i<sol.size();i++){
        if(sol[i]) {
            cout << valores[i] << " ";
        }
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    int sinAlmacen = 0, Memo = 0, iterativeTABLE = 0, iterativeVECTOR = 0, sValue = 0;
    int n, T;
    vector<int> valores;

    bool checkT = false, checkNaive = false, checkF = false;

    string readArgument, filename;

    for(int i=1; i<argc;i++) {
        readArgument = argv[i];

        if(readArgument == "-t") checkT = true;
        if(readArgument == "--ignore_naive") checkNaive = true;
        if(readArgument == "-f") {
            if(i + 1 < argc) {
                filename = argv[i + 1];
                i++;
            }
            checkF = true;
        }

        if(readArgument != "-t" && readArgument != "--ignore_naive" && readArgument != "-f") {
            cout << "ERROR: unknown option " << argv[i] << "." << endl;
            cout << "Usage: " << endl;
            cout << "maxsum [-t] [--ignore_naive] -f file" << endl;
            exit(-1);
        }
    }

    readFile(filename, n, T, valores); // Leer fichero.

    if(checkNaive) { // Si usamos la opción ignore_naive ...
        Memo = Memoization(n, T, valores); // Solución recursiva con almacen.
        iterativeTABLE = IterativoConAlmacenTABLA(n, T, valores, checkT); // Solución iterativa con almacen.
        iterativeVECTOR = IterativoVECTOR(n, T, valores); // Solución iterativa con almacén con complejidad espacial mejorada.
        Solutions(sinAlmacen, Memo, iterativeTABLE, iterativeVECTOR, checkNaive, checkF);

        vector<vector<bool>> trace;
        vector<bool>sol(n);

        sValue = SelectionValue(n,T,valores,trace);
        cout << "Selection: ";
        Parse(valores,trace,sol);
        showSelection(sol,valores);
        cout << "Selection value: " << sValue << endl;

        if(checkT) {
            cout << "Iterative table: " << endl;
            mostrarTabla(n, T); // Mostrar tabla.
        }
    }
    else {
        sinAlmacen = Naive(n, T, valores); // Solución recursiva sin almacen.
        Memo = Memoization(n, T, valores); // Solución recursiva con almacen.
        iterativeTABLE = IterativoConAlmacenTABLA(n, T, valores, checkT); // Solución iterativa con almacen.
        iterativeVECTOR = IterativoVECTOR(n, T, valores); // Solución iterativa con almacén con complejidad espacial mejorada.
        Solutions(sinAlmacen, Memo, iterativeTABLE, iterativeVECTOR, checkNaive, checkF);

        vector<vector<bool>> trace;
        vector<bool>sol(n);

        sValue = SelectionValue(n,T,valores,trace);
        cout << "Selection: ";
        Parse(valores,trace,sol);
        showSelection(sol,valores);
        cout << "Selection value: " << sValue << endl;

        if(checkT) {
            cout << "Iterative table: " << endl;
            mostrarTabla(n, T); // Mostrar tabla.
        }
    }
    return 0;
}