from pathlib import Path
import argparse
import pandas as pd
import numpy as np

def analyze(path):
    df = pd.read_csv(path)
    required = {"uv_index", "reference_uv_index"}
    if not required.issubset(df.columns):
        raise ValueError(f"CSV must contain {sorted(required)}")
    error = df["uv_index"] - df["reference_uv_index"]
    return {"n": len(df), "bias": float(error.mean()),
            "mae": float(error.abs().mean()),
            "rmse": float(np.sqrt(np.mean(error**2))),
            "max_abs_error": float(error.abs().max())}

if __name__ == "__main__":
    p=argparse.ArgumentParser()
    repo = Path(__file__).resolve().parents[1]
    p.add_argument("--input",default=str(repo / "data" / "calibrated_uv_readings.csv"))
    a=p.parse_args()
    print(analyze(a.input))
