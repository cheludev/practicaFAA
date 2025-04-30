#include <iostream>
#include <vector>
using namespace std;

// Merge entre dos mitades usando un array auxiliar
void mergeOptimizado(vector<int>& A, vector<int>& aux, int izq, int medio, int der) {
    for (int i = izq; i <= der; i++) {
        aux[i] = A[i];
    }

    int i = izq, j = medio + 1, k = izq;

    while (i <= medio && j <= der) {
        if (aux[i] <= aux[j]) {
            A[k++] = aux[i++];
        } else {
            A[k++] = aux[j++];
        }
    }

    while (i <= medio) {
        A[k++] = aux[i++];
    }
}

// Merge Sort optimizado que usa un único array auxiliar
void mergeSortOptimizado(vector<int>& A, vector<int>& aux, int izq, int der) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;
        mergeSortOptimizado(A, aux, izq, medio);
        mergeSortOptimizado(A, aux, medio + 1, der);
        mergeOptimizado(A, aux, izq, medio, der);
    }
}

// Función que devuelve los elementos que aparecen exactamente una vez
vector<int> elementosUnicos(vector<int> A) {
    int n = A.size();
    if (n == 0) return {};

    vector<int> aux(n);
    mergeSortOptimizado(A, aux, 0, n - 1);

    vector<int> resultado;
    for (int i = 0; i < n; ++i) {
        bool unico = true;
        if (i > 0 && A[i] == A[i - 1]) unico = false;
        if (i < n - 1 && A[i] == A[i + 1]) unico = false;
        if (unico)
            resultado.push_back(A[i]);
    }

    return resultado;
}

// Función auxiliar para imprimir un vector
void imprimirVector(const vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i != v.size() - 1) cout << " ";
    }
    cout << endl;
}

// Main con ejemplos para verificar
int main() {
    vector<vector<int>> ejemplos = {
        {4, 5, 4, 6, 7, 5, 8},
        {10, 20, 30, 40, 50},
        {1, 1, 1, 2, 2, 3},
        {5, 5, 5, 5, 5},
        {},
        {3, 1, 2, 2, 1, 3, 5, 6},
        {100, 200, 100, 300, 200, 400, 500}
    };

    for (const auto& ejemplo : ejemplos) {
        cout << "Array original: ";
        imprimirVector(ejemplo);

        vector<int> unicos = elementosUnicos(ejemplo);

        cout << "Elementos únicos: ";
        imprimirVector(unicos);
        cout << "---------------------------------" << endl;
    }

    return 0;
}
