from pathlib import Path
import argparse
import pandas as pd
import matplotlib.pyplot as plt

def generate(input_csv, output_dir="../images"):
    df = pd.read_csv(input_csv)
    out = Path(output_dir); out.mkdir(parents=True, exist_ok=True)
    x = pd.to_datetime(df["timestamp"]) if "timestamp" in df else range(len(df))
    if "uv_index" in df:
        plt.figure(figsize=(9,4)); plt.plot(x, df.uv_index); plt.ylabel("UV Index")
        plt.xlabel("Time"); plt.title("UV Index Readings"); plt.tight_layout()
        plt.savefig(out/"uv_readings_plot.png", dpi=160); plt.close()
    dose_col = "dose_j_m2" if "dose_j_m2" in df else None
    if dose_col:
        plt.figure(figsize=(9,4)); plt.plot(x, df[dose_col]); plt.ylabel("Dose (J/m²)")
        plt.xlabel("Time"); plt.title("Cumulative UV Exposure Dose"); plt.tight_layout()
        plt.savefig(out/"exposure_analysis.png", dpi=160); plt.close()

if __name__ == "__main__":
    p=argparse.ArgumentParser()
    repo = Path(__file__).resolve().parents[1]
    p.add_argument("--input",default=str(repo / "data" / "exposure_log.csv"))
    p.add_argument("--output-dir",default=str(repo / "images"))
    a=p.parse_args(); generate(a.input,a.output_dir)
