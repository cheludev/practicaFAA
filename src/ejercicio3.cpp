#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// ---------------------- Funciones de búsqueda ----------------------

// Variante 1: Búsqueda binaria recursiva estándar
int busquedaBinaria1(const vector<int> &A, int izq, int der, int x, int &operaciones)
{
    operaciones++; // Comparación izq > der
    if (izq > der)
    {
        operaciones++; // Return -1
        return -1;
    }

    operaciones += 3; // Suma, suma y división
    int medio = (izq + der) / 2;

    operaciones += 2; // Acceso y comparación
    if (A[medio] == x)
    {
        operaciones++; // Return
        return medio;
    }

    operaciones += 2; // Acceso y comparación
    if (A[medio] > x)
    {
        operaciones += 2; // Llamada recursiva
        return busquedaBinaria1(A, izq, medio - 1, x, operaciones);
    }
    else
    {
        operaciones += 2; // Llamada recursiva
        return busquedaBinaria1(A, medio + 1, der, x, operaciones);
    }
}

// Variante 1 Iterativa
int busquedaBinaria1Iterativa(const vector<int> &A, int x, int &operaciones)
{
    operaciones += 2; // Inicialización izq y der
    int izq = 0, der = A.size() - 1;

    while (izq <= der)
    {
        operaciones++; // Comparación del while

        operaciones += 3; // Suma, suma y división
        int medio = (izq + der) / 2;

        operaciones += 2; // Acceso y comparación
        if (A[medio] == x)
        {
            operaciones++; // Return
            return medio;
        }

        operaciones += 2; // Acceso y comparación
        if (A[medio] > x)
        {
            operaciones += 2; // Actualización der
            der = medio - 1;
        }
        else
        {
            operaciones += 2; // Actualización izq
            izq = medio + 1;
        }
    }
    operaciones++; // Salida fallida
    return -1;
}

// Variante 2: Búsqueda binaria recursiva primera ocurrencia
int busquedaBinaria2(const vector<int> &A, int izq, int der, int x, int &operaciones)
{
    operaciones++;
    if (izq > der)
    {
        operaciones++;
        return -1;
    }

    operaciones += 3;
    int medio = (izq + der) / 2;

    operaciones += 8;
    if (A[medio] == x && (medio == izq || A[medio - 1] != x))
    {
        operaciones++;
        return medio;
    }

    operaciones += 2;
    if (A[medio] >= x)
    {
        operaciones += 2;
        return busquedaBinaria2(A, izq, medio - 1, x, operaciones);
    }
    else
    {
        operaciones += 2;
        return busquedaBinaria2(A, medio + 1, der, x, operaciones);
    }
}

// Variante 2 Iterativa (primera ocurrencia)
int busquedaBinaria2Iterativa(const vector<int> &A, int x, int &operaciones)
{
    operaciones += 5; // Inicialización izq, der, resultado
    int izq = 0, der = A.size() - 1;
    int resultado = -1;

    while (izq <= der)
    {
        operaciones++; // Comparación while

        operaciones += 3; // Suma, suma, división
        int medio = (izq + der) / 2;

        operaciones += 2; // Acceso y comparación
        if (A[medio] == x)
        {
            resultado = medio;
            der = medio - 1;
            operaciones += 3; // Asignaciones y decremento
        }
        else
        {
            operaciones += 2; // Acceso y comparación
            if (A[medio] > x)
            {
                operaciones += 2; // Actualización der
                der = medio - 1;
            }
            else
            {
                operaciones += 2; // Actualización izq
                izq = medio + 1;
            }
        }
    }
    operaciones++; // Salida
    return resultado;
}
// Variante 3: Búsqueda binaria recursiva con interpolación
int busquedaBinariaInterpolacion(const vector<int> &A, int izq, int der, int x, int &operaciones)
{
    operaciones += 7; // Comprobaciones iniciales
    if (izq > der || x < A[izq] || x > A[der])
    {
        operaciones++;
        return -1;
    }

    int pos;
    operaciones += 10; // Cálculo interpolación
    if (A[der] == A[izq]) {
        pos = (izq + der) / 2;
    } else {
        pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
    }

    operaciones += 3; // Comprobación pos fuera de rango
    if (pos < izq || pos > der)
    {
        operaciones += 3;
        pos = (izq + der) / 2;
    }

    operaciones += 2; // Comparación ==
    if (A[pos] == x)
    {
        operaciones++;
        return pos;
    }

    operaciones += 2; // Comparación >
    if (A[pos] > x)
    {
        operaciones += 2;
        return busquedaBinariaInterpolacion(A, izq, pos - 1, x, operaciones);
    }
    else
    {
        operaciones += 2;
        return busquedaBinariaInterpolacion(A, pos + 1, der, x, operaciones);
    }
}

// Variante 3 Iterativa: Búsqueda binaria con interpolación
int busquedaBinariaInterpolacionIterativa(const vector<int> &A, int x, int &operaciones)
{
    operaciones += 2; // Inicialización izq y der
    int izq = 0, der = A.size() - 1;

    while (izq <= der && x >= A[izq] && x <= A[der])
    {
        operaciones++; // Comparación del while

        operaciones += 10; // Cálculo interpolación
        int pos;
        if (A[der] == A[izq]) {
            pos = (izq + der) / 2;
        } else {
            pos = izq + ((x - A[izq]) * (der - izq)) / (A[der] - A[izq]);
        }

        operaciones += 3; // Comprobación pos fuera de rango
        if (pos < izq || pos > der)
        {
            operaciones += 3;
            pos = (izq + der) / 2;
        }

        operaciones += 2; // Comparación ==
        if (A[pos] == x)
        {
            operaciones++; // Return
            return pos;
        }

        operaciones += 2; // Comparación >
        if (A[pos] > x)
        {
            operaciones += 2; // Actualización der
            der = pos - 1;
        }
        else
        {
            operaciones += 2; // Actualización izq
            izq = pos + 1;
        }
    }

    operaciones++; // Salida fallida
    return -1;
}


void generarDatos(vector<int>& vec, const string& tipo, int n) {
    vec.clear();
    if (tipo == "uniforme") {
        for (int i = 0; i < n; ++i)
            vec.push_back(i * 2); 
    }
    else if (tipo == "exponencial") {
        for (int i = 0; i < n; ++i)
            vec.push_back(pow(2, i % 30));
        sort(vec.begin(), vec.end());
    }
    else if (tipo == "normal") {
        default_random_engine gen(42);
        normal_distribution<double> dist(5000.0, 2000.0);
        for (int i = 0; i < n; ++i)
            vec.push_back(max(0, (int)dist(gen)));
        sort(vec.begin(), vec.end());
    }
}

int main() {
    vector<int> tamanos = {1000, 10000, 100000, 1000000, 10000000};
    vector<string> distribuciones = {"uniforme", "exponencial", "normal"};

    ofstream file("estudio_busquedas.csv");
    file << "Tamano;TipoDistribucion;Algoritmo;Version;PromedioOperaciones\n";

    for (int n : tamanos) {
        for (const string& dist : distribuciones) {
            vector<int> A;
            generarDatos(A, dist, n);

            int numConsultas = 100;
            long long totalOpsBinariaRec = 0, totalOpsBinariaIter = 0;
            long long totalOpsPrimeraRec = 0, totalOpsPrimeraIter = 0;
            long long totalOpsInterpolRec = 0, totalOpsInterpolIter = 0;

            for (int i = 0; i < numConsultas; ++i) {
                int buscar = A[rand() % A.size()];

                int ops1 = 0, ops2 = 0, ops3 = 0;
                int ops4 = 0, ops5 = 0, ops6 = 0;

                busquedaBinaria1(A, 0, A.size() - 1, buscar, ops1);
                busquedaBinaria1Iterativa(A, buscar, ops2);
                busquedaBinaria2(A, 0, A.size() - 1, buscar, ops3);
                busquedaBinaria2Iterativa(A, buscar, ops4);
                busquedaBinariaInterpolacion(A, 0, A.size() - 1, buscar, ops5);
                busquedaBinariaInterpolacionIterativa(A, buscar, ops6);

                totalOpsBinariaRec += ops1;
                totalOpsBinariaIter += ops2;
                totalOpsPrimeraRec += ops3;
                totalOpsPrimeraIter += ops4;
                totalOpsInterpolRec += ops5;
                totalOpsInterpolIter += ops6;
            }

            double mediaBinariaRec = totalOpsBinariaRec / (double)numConsultas;
            double mediaBinariaIter = totalOpsBinariaIter / (double)numConsultas;
            double mediaPrimeraRec = totalOpsPrimeraRec / (double)numConsultas;
            double mediaPrimeraIter = totalOpsPrimeraIter / (double)numConsultas;
            double mediaInterpolRec = totalOpsInterpolRec / (double)numConsultas;
            double mediaInterpolIter = totalOpsInterpolIter / (double)numConsultas;

            file << n << ";" << dist << ";BusquedaBinaria1;Recursiva;" << mediaBinariaRec << "\n";
            file << n << ";" << dist << ";BusquedaBinaria1;Iterativa;" << mediaBinariaIter << "\n";
            file << n << ";" << dist << ";BusquedaBinaria2;Recursiva;" << mediaPrimeraRec << "\n";
            file << n << ";" << dist << ";BusquedaBinaria2;Iterativa;" << mediaPrimeraIter << "\n";
            file << n << ";" << dist << ";BusquedaInterpolacion;Recursiva;" << mediaInterpolRec << "\n";
            file << n << ";" << dist << ";BusquedaInterpolacion;Iterativa;" << mediaInterpolIter << "\n";
        }
    }

    file.close();
    cout << "Datos exportados a estudio_busquedas.csv" << endl;
    return 0;
}
