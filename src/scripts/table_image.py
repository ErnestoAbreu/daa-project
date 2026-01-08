from pdb import main
import matplotlib.pyplot as plt
import pandas as pd
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
RESULT_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "results")

def render_table_image(df, output_image):
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
    plt.savefig(output_image, dpi=300)
    plt.close()

    print(f"\n📄 Imagen generada: {output_image}")
    
    
def main():
    input_csv = os.path.join(RESULT_DIR, "sols_results.csv")
    output_image = os.path.join(RESULT_DIR, "sols_results.png")
    
    df = pd.read_csv(input_csv)
    render_table_image(df, output_image)
    
if __name__ == "__main__":
    main()