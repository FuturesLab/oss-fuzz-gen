import json
import sys

if __name__ == "__main__":
    path = sys.argv[1]
    branch_count = 0

    with open(path, "r") as f:
        report = json.load(f)

    total_branches = 0
    covered_branches = 0

    for entry in report.get("data", []):
        for file in entry.get("files", []):
            branches = file.get("summary", {}).get("branches", {})
            total_branches += branches.get("count", 0)
            covered_branches += branches.get("covered", 0)

    print(f"Covered branches: {covered_branches}")
    print(f"Total branches: {total_branches}")

    if total_branches > 0:
        percent = covered_branches / total_branches * 100
        print(f"Branch coverage: {percent:.2f}%")
    else:
        print("No branches found")