# Práctica 4: Divide y Vencerás

**Asignatura**: Fundamentos de Análisis de Algoritmos  
**Autor**: José Luis Salvador Martín  
**Fecha**: Abril 2025

## Descripción general

Esta práctica explora el paradigma "Divide y Vencerás" mediante la implementación, análisis teórico y evaluación empírica de diferentes algoritmos:

- Búsquedas binarias (estándar, primera ocurrencia, interpolación).
- Variantes iterativas y recursivas.
- Análisis de complejidad y operaciones elementales.
- Merge Sort híbrido y optimizado.
- Aplicación práctica para encontrar elementos únicos o que aparecen exactamente _k_ veces.

El objetivo es contrastar tanto el rendimiento teórico como práctico de las soluciones implementadas.

---

## Estructura del proyecto

- `Documentación.pdf`: Informe teórico original
- `README.md`: Este archivo explicativo
- `analisis.md`: Análisis individual adicional
- `estudio_busquedas.csv`: Resultados empíricos del estudio de búsqueda binaria
- `graph.py`: Script en Python para generar gráficas desde el CSV
- `grafica_exponencial.png`: Gráfica generada para distribución exponencial
- `grafica_normal.png`: Gráfica generada para distribución normal
- `grafica_uniforme.png`: Gráfica generada para distribución uniforme
- `ejercicio2.cpp`: Estudio empírico con distribuciones
- `ejercicio3.cpp`: Comparación entre versiones recursiva e iterativa
- `ejercicio4.cpp`: Merge Sort híbrido, optimizado y análisis de mejor k
- `ejercicio5.cpp`: Resolución de problemas con aparición exacta de k veces

---

## Algoritmos implementados

### Búsqueda binaria (3 variantes)
- **Variante 1**: Búsqueda estándar.
- **Variante 2**: Primera ocurrencia.
- **Variante 3**: Interpolación.

Cada una ha sido implementada en versión recursiva e iterativa, y se han medido operaciones elementales para evaluar eficiencia real.

### Merge Sort híbrido
- Combinación de Merge Sort y Insertion Sort a partir de un umbral _k_.
- Se estudia empíricamente cuál es el mejor valor de _k_ en función del tamaño del array.

### Merge Sort optimizado
- Se reutiliza un único array auxiliar en lugar de crear subarrays en cada llamada a `merge()`.
- Se comparan operaciones elementales frente al Merge Sort híbrido clásico.

---

## Aplicaciones prácticas

### Elementos únicos
Se implementa un algoritmo para encontrar todos los elementos que aparecen exactamente una vez.  
Coste total:  
- **Temporal**: O(n log n)  
- **Espacial**: O(n)

### Elementos que aparecen k veces
Versión generalizada que permite buscar elementos que aparecen exactamente _k_ veces.  
También basada en ordenación + recorrido lineal.

---

## Instrucciones de compilación y ejecución

Compilar:
```bash
g++ -std=c++17 archivo.cpp -o ejecutable
