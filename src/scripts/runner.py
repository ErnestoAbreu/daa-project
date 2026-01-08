import os
import subprocess
import time
import pandas as pd
import sys

# Get the directory where this script is located
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
TESTS_DIR = os.path.join(SCRIPT_DIR, "..", "tests")
BIN_DIR = os.path.join(SCRIPT_DIR, "..", "bin")
RESULT_DIR = os.path.join(SCRIPT_DIR, "..", "results")
TIMEOUT = 5  # segundos

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

def main():
    results = []
    output_name = sys.argv[1] if len(sys.argv) > 1 else "results"

    test_files = sorted( f for f in os.listdir(TESTS_DIR) if f.endswith(".txt") )
    executables = sorted( f for f in os.listdir(BIN_DIR) if f.endswith(".exe") )

    for test_file in test_files:
        with open(os.path.join(TESTS_DIR, test_file), "r", encoding="utf-8") as f:
            input_data = f.read()

        for exe in executables:
            exe_path = os.path.join(BIN_DIR, exe)

            output, exec_time = run_executable(exe_path, input_data)
            
            Vraw = test_file.split("_")[2]
            Kraw = test_file.split("_")[3].replace(".txt", "")

            results.append({
                "V": Vraw,
                "K": Kraw,
                "Algorithm": exe[:-4] if exe.endswith(".exe") else exe,
                "Output": output,
                "Time (s)": exec_time
            })

    df = pd.DataFrame(results)

    df.to_csv(os.path.join(RESULT_DIR, output_name + ".csv"), index=False)
    

if __name__ == "__main__":
    main()
