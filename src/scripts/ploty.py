import os
import sys
import pandas as pd
import matplotlib.pyplot as plt


def plot_by_k(csv_file):
    # Leer CSV
    df = pd.read_csv(csv_file)

    # Asegurar tipos correctos
    df["V"] = df["V"].astype(int)
    df["K"] = df["K"].astype(int)
    df["Time (s)"] = df["Time (s)"].astype(float)

    # Obtener valores únicos de K
    ks = sorted(df["K"].unique())

    for k in ks:
        df_k = df[df["K"] == k]

        plt.figure()
        for algorithm in df_k["Algorithm"].unique():
            df_alg = df_k[df_k["Algorithm"] == algorithm]
            df_alg = df_alg.sort_values("V")

            plt.plot(
                df_alg["V"],
                df_alg["Time (s)"],
                marker='o',
                label=algorithm
            )

        plt.xlabel("Tamaño de V")
        plt.ylabel("Tiempo de ejecución (s)")
        plt.title(f"Tiempo de ejecución vs V (K = {k})")
        plt.legend()
        plt.grid(True)
        plt.tight_layout()

        output_name = f"tiempo_vs_V_K_{k}.png"
        plt.savefig(output_name, dpi=300)
        plt.show()

        print(f"Gráfica generada: {output_name}")


if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(script_dir, "..", "results", "sols_results.csv")

    plot_by_k(csv_path)
