#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <windows.h>

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


int main()
{
    SetConsoleOutputCP(CP_UTF8); // Para ver bien acentos en consola

    // Crear arrays de prueba
    vector<int> vacio;
    vector<int> uno = {5};
    vector<int> repetidos = {1, 2, 2, 2, 3, 4, 5};
    vector<int> uniforme;
    vector<int> no_uniforme = {1, 2, 3, 4, 100, 101, 102, 1000};

    for (int i = 0; i < 100; i++) {
        uniforme.push_back(i * 2); // 0, 2, 4, ..., 198
    }

    cout << "\n================= ESTUDIO EMPÍRICO =================\n";

    int op1, op2, op3;
    int res1, res2, res3;

    // ---------------- Array vacío ----------------
    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(vacio, 0, vacio.size() - 1, 10, op1);
    res2 = busquedaBinaria2(vacio, 0, vacio.size() - 1, 10, op2);
    res3 = busquedaBinariaInterpolacion(vacio, 0, vacio.size() - 1, 10, op3);
    cout << "\n>> Array vacío\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    // ---------------- Array de un solo elemento ----------------
    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uno, 0, uno.size() - 1, 5, op1);
    res2 = busquedaBinaria2(uno, 0, uno.size() - 1, 5, op2);
    res3 = busquedaBinariaInterpolacion(uno, 0, uno.size() - 1, 5, op3);
    cout << "\n>> Array con un solo elemento (existe)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uno, 0, uno.size() - 1, 1, op1);
    res2 = busquedaBinaria2(uno, 0, uno.size() - 1, 1, op2);
    res3 = busquedaBinariaInterpolacion(uno, 0, uno.size() - 1, 1, op3);
    cout << "\n>> Array con un solo elemento (no existe)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    // ---------------- Repetidos: principio, medio, final, no existe ----------------
    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(repetidos, 0, repetidos.size() - 1, 1, op1);
    res2 = busquedaBinaria2(repetidos, 0, repetidos.size() - 1, 1, op2);
    res3 = busquedaBinariaInterpolacion(repetidos, 0, repetidos.size() - 1, 1, op3);
    cout << "\n>> Repetidos - buscar 1 (principio)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(repetidos, 0, repetidos.size() - 1, 2, op1);
    res2 = busquedaBinaria2(repetidos, 0, repetidos.size() - 1, 2, op2);
    res3 = busquedaBinariaInterpolacion(repetidos, 0, repetidos.size() - 1, 2, op3);
    cout << "\n>> Repetidos - buscar 2 (repetido medio)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2;
    // Verificación de primera ocurrencia
    for (int i = 0; i < repetidos.size(); ++i) {
        if (repetidos[i] == 2) {
            cout << " → Primera esperada: " << i;
            if (res2 != i) cout << " [ERROR]";
            break;
        }
    }
    cout << "\n  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(repetidos, 0, repetidos.size() - 1, 5, op1);
    res2 = busquedaBinaria2(repetidos, 0, repetidos.size() - 1, 5, op2);
    res3 = busquedaBinariaInterpolacion(repetidos, 0, repetidos.size() - 1, 5, op3);
    cout << "\n>> Repetidos - buscar 5 (final)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(repetidos, 0, repetidos.size() - 1, 6, op1);
    res2 = busquedaBinaria2(repetidos, 0, repetidos.size() - 1, 6, op2);
    res3 = busquedaBinariaInterpolacion(repetidos, 0, repetidos.size() - 1, 6, op3);
    cout << "\n>> Repetidos - buscar 6 (no existe)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    // ---------------- Uniforme ----------------
    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uniforme, 0, uniforme.size() - 1, 0, op1);
    res2 = busquedaBinaria2(uniforme, 0, uniforme.size() - 1, 0, op2);
    res3 = busquedaBinariaInterpolacion(uniforme, 0, uniforme.size() - 1, 0, op3);
    cout << "\n>> Uniforme - buscar 0 (principio)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uniforme, 0, uniforme.size() - 1, 98, op1);
    res2 = busquedaBinaria2(uniforme, 0, uniforme.size() - 1, 98, op2);
    res3 = busquedaBinariaInterpolacion(uniforme, 0, uniforme.size() - 1, 98, op3);
    cout << "\n>> Uniforme - buscar 98 (medio)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uniforme, 0, uniforme.size() - 1, 198, op1);
    res2 = busquedaBinaria2(uniforme, 0, uniforme.size() - 1, 198, op2);
    res3 = busquedaBinariaInterpolacion(uniforme, 0, uniforme.size() - 1, 198, op3);
    cout << "\n>> Uniforme - buscar 198 (final)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(uniforme, 0, uniforme.size() - 1, 199, op1);
    res2 = busquedaBinaria2(uniforme, 0, uniforme.size() - 1, 199, op2);
    res3 = busquedaBinariaInterpolacion(uniforme, 0, uniforme.size() - 1, 199, op3);
    cout << "\n>> Uniforme - buscar 199 (no existe)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    // ---------------- No uniforme ----------------
    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(no_uniforme, 0, no_uniforme.size() - 1, 1000, op1);
    res2 = busquedaBinaria2(no_uniforme, 0, no_uniforme.size() - 1, 1000, op2);
    res3 = busquedaBinariaInterpolacion(no_uniforme, 0, no_uniforme.size() - 1, 1000, op3);
    cout << "\n>> No uniforme - buscar 1000 (final)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(no_uniforme, 0, no_uniforme.size() - 1, 3, op1);
    res2 = busquedaBinaria2(no_uniforme, 0, no_uniforme.size() - 1, 3, op2);
    res3 = busquedaBinariaInterpolacion(no_uniforme, 0, no_uniforme.size() - 1, 3, op3);
    cout << "\n>> No uniforme - buscar 3 (medio)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    op1 = op2 = op3 = 0;
    res1 = busquedaBinaria1(no_uniforme, 0, no_uniforme.size() - 1, 200, op1);
    res2 = busquedaBinaria2(no_uniforme, 0, no_uniforme.size() - 1, 200, op2);
    res3 = busquedaBinariaInterpolacion(no_uniforme, 0, no_uniforme.size() - 1, 200, op3);
    cout << "\n>> No uniforme - buscar 200 (no existe)\n";
    cout << "  Binaria1: " << res1 << ", OE: " << op1 << "\n";
    cout << "  Binaria2: " << res2 << ", OE: " << op2 << "\n";
    cout << "  Interpolación: " << res3 << ", OE: " << op3 << "\n";

    cout << "\n================= FIN DEL ESTUDIO =================\n";
    return 0;
}
