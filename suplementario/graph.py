import pandas as pd
import matplotlib.pyplot as plt

# Cargar CSV
df = pd.read_csv('estudio_busquedas.csv', sep=';', encoding='utf-8')

# Renombrar columnas mal codificadas y limpiar
df.columns = df.columns.str.strip().str.lower()
df = df.rename(columns={'tipo': 'version', 'tama�o': 'tamano'})

# Asegurar que los datos son numéricos
df['tamano'] = pd.to_numeric(df['tamano'], errors='coerce')
df['promediooperaciones'] = pd.to_numeric(df['promediooperaciones'], errors='coerce')

# Comprobamos columnas
print("Columnas:", df.columns.tolist())

# Crear gráficas por cada tipo de distribución
for dist in df['tipodistribucion'].unique():
    df_dist = df[df['tipodistribucion'] == dist]

    plt.figure(figsize=(12, 6))

    for alg in df_dist['algoritmo'].unique():
        for version in ['Recursiva', 'Iterativa']:
            subset = df_dist[(df_dist['algoritmo'] == alg) & (df_dist['version'].str.lower() == version.lower())]
            if not subset.empty:
                plt.plot(
                    subset['tamano'], 
                    subset['promediooperaciones'], 
                    marker='o', 
                    label=f'{alg} - {version}'
                )

    plt.title(f'Rendimiento por operaciones en distribución: {dist}')
    plt.xlabel('Tamaño del array')
    plt.ylabel('Promedio de operaciones')
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which='both', linestyle='--', alpha=0.6)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f'grafica_{dist}.png')
    plt.show()
