import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "simulation"))
from exposure_simulation import simulate
import pandas as pd

def test_dose_increases_with_positive_uv(tmp_path):
    src=tmp_path/"in.csv"; out=tmp_path/"out.csv"
    pd.DataFrame({"timestamp":["2026-01-01 10:00:00","2026-01-01 10:01:00"],
                  "uv_index":[4,4]}).to_csv(src,index=False)
    result=simulate(src,out)
    assert result.dose_j_m2.iloc[-1] > result.dose_j_m2.iloc[0]
    assert result.upper_dose_j_m2.iloc[-1] >= result.dose_j_m2.iloc[-1]

def test_zero_uv_gives_zero_dose(tmp_path):
    src=tmp_path/"in.csv"; out=tmp_path/"out.csv"
    pd.DataFrame({"timestamp":["2026-01-01 10:00:00","2026-01-01 10:01:00"],
                  "uv_index":[0,0]}).to_csv(src,index=False)
    result=simulate(src,out)
    assert result.dose_j_m2.iloc[-1] == 0
