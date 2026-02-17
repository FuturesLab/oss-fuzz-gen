import json
import sys
import os
import argparse
from pathlib import Path

from experiment.textcov import Textcov

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--project", type=str, required=True)
    parser.add_argument("-r", "--results-dir", type=str, required=True)
    args = parser.parse_args()
    return args


def process_cov(appr, dirs: list[str]) -> dict[int, Textcov]:
    coverage_results = {}
    for d in dirs:
        print(d)
        trial_num = int(d.name.split("-")[-1])
        coverage_dir = os.path.join(d, "code-coverage-reports", appr, "textcov")
        cov_reports = list(Path(coverage_dir).rglob('*.covreport'))
        print(cov_reports)
        assert len(cov_reports) == 1
        cov_report = cov_reports[0]
        with open(cov_report, "rb") as f:
            textcov = Textcov.from_file(f)
        coverage_results[trial_num] = textcov
    return coverage_results

if __name__ == "__main__":
    args = parse_args()
    project_name = args.project
    results_dir = args.results_dir

    results_path = Path(results_dir)

    bluebird_ofg_dirs = [p for p in results_path.iterdir() if "bluebird_ofg" in p.name]
    bluebird_promefuzz_dirs = [p for p in results_path.iterdir() if "bluebird_promefuzz" in p.name]
    ofg_dirs = [p for p in results_path.iterdir() if "ofg" in p.name and not "bluebird_ofg" in p.name]
    liberator_dirs = [p for p in results_path.iterdir() if "liberator" in p.name]
    promefuzz_dirs = [p for p in results_path.iterdir() if "promefuzz" in p.name and not "bluebird_promefuzz" in p.name]

    bluebird_ofg_results = process_cov("bluebird_ofg", bluebird_ofg_dirs)
    bluebird_promefuzz_results = process_cov("bluebird_promefuzz", bluebird_promefuzz_dirs)
    ofg_results = process_cov("ofg", ofg_dirs)
    liberator_results = process_cov("liberator", liberator_dirs)
    promefuzz_results = process_cov("promefuzz", promefuzz_dirs)

# header (use same widths, avoid mixing tabs)
print(f"{'bluebird_ofg':>24} "
      f"{'bluebird_promefuzz':>24} "
      f"{'ofg':>24} "
      f"{'liberator':>24} "
      f"{'promefuzz':>24}")

fmt = ("{0:>12} {1:>12} {2:>12} {3:>12} {4:>12} "
       "{5:>12} {6:>12} {7:>12} {8:>12} {9:>12}")

for trial_num in range(5):
    b_ofg = bluebird_ofg_results.get(trial_num, Textcov())
    b_pf = bluebird_promefuzz_results.get(trial_num, Textcov())
    ofg = ofg_results.get(trial_num, Textcov())
    lib = liberator_results.get(trial_num, Textcov())
    pro = promefuzz_results.get(trial_num, Textcov())

    b_ofg_u = b_ofg.unique_branches_against(b_pf, ofg, lib, pro)
    b_pf_u  = b_pf.unique_branches_against(b_ofg, ofg, lib, pro)
    ofg_u   = ofg.unique_branches_against(b_pf, b_ofg, lib, pro)
    lib_u   = lib.unique_branches_against(b_pf, ofg, b_ofg, pro)
    pro_u   = pro.unique_branches_against(b_pf, ofg, lib, b_ofg)

    values = (
        len(b_ofg.covered_branches), len(b_ofg_u),
        len(b_pf.covered_branches), len(b_pf_u),
        len(ofg.covered_branches), len(ofg_u),
        len(lib.covered_branches), len(lib_u),
        len(pro.covered_branches), len(pro_u),
    )
    print(fmt.format(*values))





# if __name__ == "__main__":
#     path = sys.argv[1]
#     branch_count = 0

#     with open(path, "r") as f:
#         report = json.load(f)

#     total_branches = 0
#     covered_branches = 0

#     for entry in report.get("data", []):
#         for file in entry.get("files", []):
#             if "synthesized_driver" in file.get("filename", ""):
#                 continue
#             branches = file.get("summary", {}).get("branches", {})
#             print(file.get("filename", ""))
#             print(file.get("summary", {}))
#             total_branches += branches.get("count", 0)
#             covered_branches += branches.get("covered", 0)

#     print(f"Covered branches: {covered_branches}")
#     print(f"Total branches: {total_branches}")

#     if total_branches > 0:
#         percent = covered_branches / total_branches * 100
#         print(f"Branch coverage: {percent:.2f}%")
#     else:
#         print("No branches found")