#include <iostream>
#include <cfloat>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

// Funciones de ordenación con conteo de operaciones
void merge(vector<int>& A, int izq, int medio, int der, long long& operaciones) {
    operaciones += 5; 

    int n1 = medio - izq + 1;
    int n2 = der - medio;

    vector<int> L(n1), R(n2); // creación no cuenta

    operaciones += 1; // inicialización i
    for (int i = 0; i < n1; i++) {
        operaciones += 7; // comparación i<n1, acceso izq, suma izq+i, acceso A[izq+i], acceso L[i], asignación, incremento i++
        L[i] = A[izq + i];
    }

    operaciones += 1; // inicialización j
    for (int j = 0; j < n2; j++) {
        operaciones += 7; // comparación j<n2, acceso medio, suma medio+1, suma (medio+1)+j, acceso A[], acceso R[], asignación, incremento j++
        R[j] = A[medio + 1 + j];
    }

    operaciones += 3; // inicializaciones i, j, k
    int i = 0, j = 0, k = izq;

    while (i < n1 && j < n2) {
        operaciones += 2; // comparaciones i<n1 y j<n2

        operaciones += 3; // acceso L[i], acceso R[j], comparación L[i] <= R[j]
        if (L[i] <= R[j]) {
            operaciones += 7; // acceso A[k], asignación, incremento i++, incremento k++
            A[k] = L[i];
            i++;
            k++;
        } else {
            operaciones += 7; // acceso A[k], asignación, incremento j++, incremento k++
            A[k] = R[j];
            j++;
            k++;
        }
    }
    operaciones += 1; // comparación
    while (i < n1) {
        operaciones += 7; // acceso L[i], acceso A[k], asignación, incrementos i++, k++
        A[k] = L[i];
        i++;
        k++;
    }

    operaciones += 1; // comparación
    while (j < n2) {
        operaciones += 7; // acceso R[j], acceso A[k], asignación, incrementos j++, k++
        A[k] = R[j];
        j++;
        k++;
    }
}

void insertionSort(vector<int>& A, int izq, int der, long long& operaciones) {
    operaciones += 1; // inicialización i
    for (int i = izq + 1; i <= der; i++) {
        operaciones += 2; // comparación i<=der y suma izq+1

        operaciones += 2; // acceso A[i], asignación key
        int key = A[i];
        operaciones += 2; // resta j=i-1
        int j = i - 1;

        operaciones += 4; 
        while (j >= izq && A[j] > key) {
            operaciones += 4; // asignación A[j+1] = A[j]
            A[j + 1] = A[j];

            operaciones += 2; // decremento j--
            j--;
        }

        operaciones += 4; // acceso A[j+1] y asignación final
        A[j + 1] = key;

        operaciones += 2; // incremento i++
    }
}

void mergeSortHibrido(vector<int>& A, int izq, int der, int k, long long& operaciones) {
    operaciones += 3; // resta der-izq+1 y comparación <=k
    if ((der - izq + 1) <= k) {
        operaciones += 1; // llamada a función insertionSort
        insertionSort(A, izq, der, operaciones);
    } else if (izq < der) {
        operaciones += 1; // comparación izq<der

        operaciones += 4; // cálculo medio: der-izq, división, suma
        int medio = izq + (der - izq) / 2;

        operaciones += 1; // llamada recursiva izquierda
        mergeSortHibrido(A, izq, medio, k, operaciones);

        operaciones += 1; // llamada recursiva derecha
        mergeSortHibrido(A, medio + 1, der, k, operaciones);

        operaciones += 1; // llamada a merge
        merge(A, izq, medio, der, operaciones);
    }
}

// Merge usando un array auxiliar
void mergeOptimizado(vector<int>& A, vector<int>& aux, int izq, int medio, int der, long long& operaciones) {
    for (int i = izq; i <= der; i++) {
        operaciones += 4; 
        aux[i] = A[i];
        operaciones++;
    }

    int i = izq, j = medio + 1, k = izq;
    operaciones += 4; // inicializaciones

    while (i <= medio && j <= der) {
        operaciones += 3; // comparación i<=medio y j<=der

        operaciones += 3; // acceso aux[i], aux[j], comparación
        if (aux[i] <= aux[j]) {
            operaciones += 6; // acceso A[k], asignación, incremento
            A[k++] = aux[i++];
        } else {
            operaciones += 6; // acceso A[k], asignación, incremento
            A[k++] = aux[j++];
        }
    }

    operaciones += 1; // comparación
    while (i <= medio) {
        operaciones += 6; // acceso A[k], aux[i], asignación, incremento
        A[k++] = aux[i++];
    }
    // No es necesario copiar lo de la derecha (ya están en su sitio)
}

// Merge Sort usando array auxiliar
void mergeSortOptimizado(vector<int>& A, vector<int>& aux, int izq, int der, int k, long long& operaciones) {
    operaciones += 3; // resta der-izq+1 y comparación <=k
    if ((der - izq + 1) <= k) {
        operaciones += 1; // llamada insertionSort
        insertionSort(A, izq, der, operaciones);
    } else if (izq < der) {
        operaciones += 1; // comparación izq < der

        operaciones += 4; // cálculo medio
        int medio = izq + (der - izq) / 2;

        operaciones += 1;
        mergeSortOptimizado(A, aux, izq, medio, k, operaciones);

        operaciones += 1;
        mergeSortOptimizado(A, aux, medio + 1, der, k, operaciones);

        operaciones += 1;
        mergeOptimizado(A, aux, izq, medio, der, operaciones);
    }
}


// Función para generar el array aleatorio
void generarArray(vector<int>& A, int n) {
    A.clear();
    for (int i = 0; i < n; i++) {
        A.push_back(rand() % 1000000); // valores aleatorios entre 0 y 999999
    }
}
int main() {
    srand(time(NULL)); // Semilla para aleatoriedad

    vector<int> tamanos = {1000, 5000, 10000, 20000, 50000};
    vector<int> posiblesK = {2, 4, 8, 16, 24, 32, 40, 64, 80, 100};

    for (int n : tamanos) {
        cout << "Probando tamaño n = " << n << endl;

        vector<int> base;
        generarArray(base, n);

        int mejorK = -1;
        long long minOperaciones = LLONG_MAX;

        // Buscar el mejor k (solo con mergeSortHibrido normal)
        for (int k : posiblesK) {
            vector<int> A = base; // Copia del array base
            long long operaciones = 0;

            mergeSortHibrido(A, 0, A.size() - 1, k, operaciones);

            cout << "  k = " << k << ", operaciones = " << operaciones << endl;

            if (operaciones < minOperaciones) {
                minOperaciones = operaciones;
                mejorK = k;
            }
        }

        cout << "=> Mejor k para n = " << n << " es " << mejorK << " (" << minOperaciones << " operaciones)" << endl;
        cout << "--------------------------------------------------" << endl;

        // Ahora, usando ese mejor k, COMPARAR las dos versiones (normal vs optimizado)

        long long operaciones_normal = 0;
        vector<int> A1 = base;
        mergeSortHibrido(A1, 0, A1.size() - 1, mejorK, operaciones_normal);

        long long operaciones_opt = 0;
        vector<int> A2 = base;
        vector<int> aux(A2.size());
        mergeSortOptimizado(A2, aux, 0, A2.size() - 1, mejorK, operaciones_opt);

        cout << "  -> MergeSort normal (hibrido) con k=" << mejorK << ": " << operaciones_normal << " operaciones" << endl;
        cout << "  -> MergeSort optimizado con k=" << mejorK << ": " << operaciones_opt << " operaciones" << endl;
        cout << "==================================================" << endl;
    }

    return 0;
}
