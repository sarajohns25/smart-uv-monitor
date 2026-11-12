import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "simulation"))
import pandas as pd
from exposure_simulation import simulate

def test_output_file_is_created(tmp_path):
    src=tmp_path/"input.csv"; out=tmp_path/"result.csv"
    pd.DataFrame({"uv_index":[2,3]}).to_csv(src,index=False)
    result=simulate(src,out)
    assert out.exists()
    assert "alert" in result.columns
