import os
import argparse
import shutil
import logging
from multiprocessing import Pool
from pathlib import Path

from experiment.benchmark import Benchmark
from experiment.workdir import WorkDirs
from experiment import oss_fuzz_checkout
from experiment.evaluator import Evaluator
import experiment.builder_runner as builder_runner_lib

"""Build and run a fuzzing trial for a given approach. Runtime length and number of trials can be provided as arguments"""

logger = logging.getLogger(__name__)
FILE_DIR = Path(__file__).resolve().parent
OSS_PATH = "/home/gabe/HyHarn/deps/oss-fuzz"


APPROACHES = ["bluebird_ofg", "ofg", "bluebird_promefuzz", "promefuzz", "liberator"]
NUM_TRIALS = 1
RUN_TIMEOUT = 30
POOL_SIZE = 4

# Turn off caching to accomodate for specific dockerfile setups (i.e., sqlite since it has no git commits)
# We can enable caching for harness gen since this is not the actual fuzzing eval part.
oss_fuzz_checkout.ENABLE_CACHING = False
LOG_FMT = ('%(asctime)s.%(msecs)03d %(levelname)s '
           '%(module)s - %(funcName)s: %(message)s')

def setup_evaluator(args, benchmark, workdir, approach):
    if args.cloud_experiment_name:
      builder_runner = builder_runner_lib.CloudBuilderRunner(
          benchmark=benchmark,
          work_dirs=workdir,
          run_timeout=RUN_TIMEOUT,
          experiment_name=args.cloud_experiment_name,
          experiment_bucket=args.cloud_experiment_bucket,
          use_afl_engine=True,
          approach=approach
      )
    else:
      builder_runner = builder_runner_lib.BuilderRunner(
          benchmark=benchmark,
          work_dirs=workdir,
          run_timeout=RUN_TIMEOUT,
          use_afl_engine=True,
          approach=approach
      )

    evaluator = Evaluator(builder_runner, benchmark, workdir)

    return evaluator

def parse_args():
    global NUM_TRIALS, APPROACHES, RUN_TIMEOUT
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--project", type=str, required=True)
    parser.add_argument("-a", "--approach", type=str, choices=APPROACHES, nargs="+")
    parser.add_argument("-ft", "--fuzz-timeout", type=int)
    parser.add_argument("-nt", "--num-trials", type=int)
    parser.add_argument("-ps", "--pool-size", type=int)
    parser.add_argument("-cn", "--cloud-experiment-name", type=str)
    
    args = parser.parse_args()

    if args.approach:
        APPROACHES = args.approach

    if args.num_trials:
        NUM_TRIALS = args.num_trials

    if args.fuzz_timeout:
        RUN_TIMEOUT = args.fuzz_timeout

    if args.pool_size:
        POOL_SIZE = args.pool_size

    return args

def run_fuzz_trial(args: argparse.Namespace, workdir_base: str, appr: str, trial: int):
    """Spawn the fuzzing campaign with a specific trial and approach identifier"""
    source_dir = os.path.join(FILE_DIR, "target_src", args.project, appr)
    build_script_path = os.path.join(FILE_DIR, "target_src", args.project, "build.sh")
    test_name = f"{args.project}-{appr}-{trial}".lower()
    workdir = WorkDirs(os.path.join(workdir_base, f'output-{test_name}'))
    evaluator = setup_evaluator(args, benchmark, workdir, appr)
    Evaluator.create_ossfuzz_project_batched_harness(benchmark, test_name, source_dir, build_script_path)
    result = evaluator.builder_runner.build_and_run(test_name, source_dir, 0, benchmark.language,
            cloud_build_tags=[
                    trial,
                    'Execution',
                    appr,
                    benchmark.project,
                ]
            )
    
if __name__ == "__main__":
    args = parse_args()
    benchmarks = Benchmark.from_yaml(os.path.join("targets", f"{args.project}.yaml"))
    benchmark = benchmarks[0]
    copy_oss_path = os.path.join(FILE_DIR, "oss-fuzz")
    shutil.copytree(OSS_PATH, copy_oss_path, dirs_exist_ok=True)
    oss_fuzz_checkout.OSS_FUZZ_DIR = copy_oss_path
    # oss_fuzz_checkout.clone_oss_fuzz(os.path.join(FILE_DIR, "oss-fuzz"))
    workdir_base = os.path.join(FILE_DIR, f"results-{args.project}")

    logging.basicConfig(
      level="INFO",
      format=LOG_FMT,
      datefmt='%Y-%m-%d %H:%M:%S',
    )
    # Set the base logger level
    logging.getLogger('').setLevel("INFO")

    experiment_tasks = []
    with Pool(POOL_SIZE, maxtasksperchild=1) as p:
        for trial in range(0, NUM_TRIALS):
            for appr in APPROACHES:
                fuzz_task = p.apply_async(run_fuzz_trial, (args, workdir_base, appr, trial))
                experiment_tasks.append(fuzz_task)

        experiment_results = [task.get() for task in experiment_tasks]
        # Signal that no more work will be submitte to the pool.
        p.close()

        # Wait for all workers to complete.
        p.join()