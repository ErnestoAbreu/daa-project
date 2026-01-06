import os
import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt

TESTS_DIR = "tests"
BIN_DIR = "bin"
TIMEOUT = 60  # segundos
OUTPUT_IMAGE = "resultados.png"


def run_executable(exe_path, input_text):
    start = time.perf_counter()
    try:
        result = subprocess.run(
            [exe_path],
            input=input_text,
            text=True,
            capture_output=True,
            timeout=TIMEOUT
        )
        elapsed = time.perf_counter() - start
        output = result.stdout.strip()
        return output, round(elapsed, 4)

    except subprocess.TimeoutExpired:
        return "-1", TIMEOUT


def render_table_image(df):
    fig, ax = plt.subplots(figsize=(len(df.columns) * 3, len(df) * 0.6 + 2))
    ax.axis('off')

    table = ax.table(
        cellText=df.values,
        colLabels=df.columns,
        loc='center',
        cellLoc='center'
    )

    table.auto_set_font_size(False)
    table.set_fontsize(9)
    table.scale(1, 1.4)

    plt.title("Resultados de ejecución de soluciones", fontsize=14, pad=20)
    plt.tight_layout()
    plt.savefig(OUTPUT_IMAGE, dpi=300)
    plt.close()

    print(f"\n📄 Imagen generada: {OUTPUT_IMAGE}")

def main():
    results = []

    test_files = sorted(
        f for f in os.listdir(TESTS_DIR) if f.endswith(".txt")
    )
    executables = sorted(
        f for f in os.listdir(BIN_DIR) if not f.endswith(".cpp") 
    )

    for test_file in test_files:
        with open(os.path.join(TESTS_DIR, test_file), "r", encoding="utf-8") as f:
            input_data = f.read()

        for exe in executables:
            exe_path = os.path.join(BIN_DIR, exe)

            output, exec_time = run_executable(exe_path, input_data)

            results.append({
                "Archivo de prueba": test_file,
                "Ejecutable": exe[:-4] if exe.endswith(".exe") else exe,
                "Salida": output,
                "Tiempo (s)": exec_time
            })

    df = pd.DataFrame(results)
    print(df)

    render_table_image(df)




if __name__ == "__main__":
    main()
