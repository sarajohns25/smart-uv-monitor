from pathlib import Path
import argparse
import pandas as pd

def summarize(path):
    df = pd.read_csv(path)
    if "dose_j_m2" not in df:
        raise ValueError("CSV must contain dose_j_m2")
    return {"samples": len(df), "final_dose_j_m2": float(df.dose_j_m2.iloc[-1]),
            "peak_uv_index": float(df.uv_index.max()) if "uv_index" in df else None}

if __name__ == "__main__":
    p=argparse.ArgumentParser()
    repo = Path(__file__).resolve().parents[1]
    p.add_argument("--input",default=str(repo / "data" / "exposure_log.csv"))
    print(summarize(p.parse_args().input))
