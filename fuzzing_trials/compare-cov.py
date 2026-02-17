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


def process_cov(appr, bluebird_dirs: list[str]) -> dict[int, Textcov]:
    coverage_results = {}
    for d in bluebird_dirs:
        trial_num = int(d.name.split("-")[-1])
        coverage_dir = os.path.join(d, "code-coverage-reports", appr, "textcov")
        cov_reports = list(Path(coverage_dir).rglob('*.covreport'))
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

    bluebird_dirs = [p for p in results_path.iterdir() if "bluebird" in p.name]
    ofg_dirs = [p for p in results_path.iterdir() if "ofg" in p.name]
    liberator_dirs = [p for p in results_path.iterdir() if "liberator" in p.name]
    promefuzz_dirs = [p for p in results_path.iterdir() if "promefuzz" in p.name]

    bluebird_results = process_cov("bluebird", bluebird_dirs)
    ofg_results = process_cov("ofg", ofg_dirs)
    liberator_results = process_cov("liberator", liberator_dirs)
    promefuzz_results = process_cov("promefuzz", promefuzz_dirs)

    print("         bluebird                ofg                  liberator       promefuzz")
    
    for trial_num in range(0, 5):
        bluebird = bluebird_results[trial_num] if trial_num in bluebird_results else Textcov()
        ofg = ofg_results[trial_num] if trial_num in ofg_results else Textcov()
        liberator = liberator_results[trial_num] if trial_num in liberator_results else Textcov()
        promefuzz = promefuzz_results[trial_num] if trial_num in promefuzz_results else Textcov()
    
        bluebird_unique = bluebird.unique_branches_against(ofg, liberator, promefuzz)
        ofg_unique = ofg.unique_branches_against(bluebird, liberator, promefuzz)
        liberator_unique = liberator.unique_branches_against(ofg, bluebird, promefuzz)
        promefuzz_unique = promefuzz.unique_branches_against(ofg, liberator, bluebird)

        print(f"\
        {len(bluebird.covered_branches)}    {len(bluebird_unique)}  \
        {len(ofg.covered_branches)}    {len(ofg_unique)}    \
        {len(liberator.covered_branches)}    {len(liberator_unique)}  \
        {len(promefuzz.covered_branches)}    {len(promefuzz_unique)}  \
        ")




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