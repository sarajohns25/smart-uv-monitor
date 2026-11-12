import argparse
from pathlib import Path
import pandas as pd

def sampling_metrics(path):
    df = pd.read_csv(path)
    if "timestamp" not in df:
        raise ValueError("timestamp column required")
    t = pd.to_datetime(df.timestamp).sort_values()
    intervals = t.diff().dt.total_seconds().dropna()
    return {"sample_count": len(df), "mean_interval_s": float(intervals.mean()),
            "median_interval_s": float(intervals.median()),
            "max_gap_s": float(intervals.max())}

if __name__ == "__main__":
    p=argparse.ArgumentParser()
    repo = Path(__file__).resolve().parents[1]
    p.add_argument("--input",default=str(repo / "data" / "raw_uv_readings.csv"))
    print(sampling_metrics(p.parse_args().input))
