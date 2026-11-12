import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "analysis"))
import pandas as pd
from calibration_analysis import analyze

def test_calibration_metrics(tmp_path):
    p=tmp_path/"cal.csv"
    pd.DataFrame({"uv_index":[1,2,3],"reference_uv_index":[1,2,2]}).to_csv(p,index=False)
    m=analyze(p)
    assert m["n"] == 3
    assert m["mae"] > 0
    assert m["rmse"] >= m["mae"]
