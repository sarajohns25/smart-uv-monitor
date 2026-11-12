from pathlib import Path
import argparse
import pandas as pd

def simulate(input_csv, output_csv, profile_threshold=300.0, uncertainty=0.15):
    df = pd.read_csv(input_csv)
    if "uv_index" not in df:
        raise ValueError("Input CSV must contain a 'uv_index' column")
    if "timestamp" in df:
        ts = pd.to_datetime(df["timestamp"])
        dt = ts.diff().dt.total_seconds().fillna(0).clip(lower=0)
        if len(dt) > 1:
            dt.iloc[0] = dt.iloc[1]
    else:
        dt = pd.Series([60.0] * len(df))
    irradiance = df["uv_index"].clip(lower=0) / 40.0
    previous = irradiance.shift(1).fillna(irradiance)
    increments = 0.5 * (irradiance + previous) * dt
    df["dose_j_m2"] = increments.cumsum()
    df["upper_dose_j_m2"] = df["dose_j_m2"] * (1 + uncertainty)
    df["dose_percent"] = 100 * df["upper_dose_j_m2"] / profile_threshold
    df["alert"] = pd.cut(df["dose_percent"], [-float("inf"), 50, 80, 100, float("inf")],
                         labels=["SAFE", "CAUTION", "HIGH", "LIMIT"])
    Path(output_csv).parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(output_csv, index=False)
    return df

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    repo = Path(__file__).resolve().parents[1]
    parser.add_argument("--input", default=str(repo / "data" / "calibrated_uv_readings.csv"))
    parser.add_argument("--output", default=str(repo / "simulation" / "simulation_results.csv"))
    parser.add_argument("--threshold", type=float, default=300.0)
    args = parser.parse_args()
    result = simulate(args.input, args.output, args.threshold)
    print(result.tail(1).to_string(index=False))
