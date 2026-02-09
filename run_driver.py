import os
import argparse
import logging

from experiment.benchmark import Benchmark
from experiment.workdir import WorkDirs
from experiment import oss_fuzz_checkout
from experiment.evaluator import Evaluator
import experiment.builder_runner as builder_runner_lib

logger = logging.getLogger(__name__)


APPROACHES = ["bluebird", "OFG", "promefuzz", "liberator"]
NUM_TRIALS = 1
RUN_TIMEOUT = 30
oss_fuzz_checkout.ENABLE_CACHING = True
LOG_FMT = ('%(asctime)s.%(msecs)03d %(levelname)s '
           '%(module)s - %(funcName)s: %(message)s')

def setup_evaluator(args, benchmark, workdir):
    if args.cloud_experiment_name:
      builder_runner = builder_runner_lib.CloudBuilderRunner(
          benchmark=benchmark,
          work_dirs=workdir,
          run_timeout=RUN_TIMEOUT,
          experiment_name=args.cloud_experiment_name,
          experiment_bucket=args.cloud_experiment_bucket,
          use_afl_engine=True,
      )
    else:
      builder_runner = builder_runner_lib.BuilderRunner(
          benchmark=benchmark,
          work_dirs=workdir,
          run_timeout=RUN_TIMEOUT,
          use_afl_engine=True,
      )

    evaluator = Evaluator(builder_runner, benchmark, workdir)

    return evaluator

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--project", type=str, required=True)
    parser.add_argument("-a", "--approach", type=str, choices=["bluebird", "OFG", "promefuzz", "liberator"])
    parser.add_argument("-cn", "--cloud-experiment-name", type=str)

    return parser.parse_args()
    
if __name__ == "__main__":
    args = parse_args()
    benchmarks = Benchmark.from_yaml(os.path.join("targets", f"{args.project}.yaml"))
    benchmark = benchmarks[0]
    oss_fuzz_checkout.clone_oss_fuzz(os.path.abspath("./oss-fuzz"))
    workdir_base = "./results"

    logging.basicConfig(
      level="INFO",
      format=LOG_FMT,
      datefmt='%Y-%m-%d %H:%M:%S',
    )
    # Set the base logger level
    logging.getLogger('').setLevel("INFO")


    approaches = APPROACHES
    if args.approach:
        approaches = [args.approach]

    for trial in range(0, NUM_TRIALS):
        for appr in approaches:
            source_dir = os.path.join("target_src", args.project, appr)
            build_script_path = os.path.join("target_src", args.project, "build.sh")
            test_name = f"{args.project}-{appr}-{trial}".lower()
            workdir = WorkDirs(os.path.join(workdir_base, f'output-{test_name}'))
            evaluator = setup_evaluator(args, benchmark, workdir)
            Evaluator.create_ossfuzz_project_batched_harness(benchmark, test_name, source_dir, build_script_path)


            result = evaluator.builder_runner.build_and_run(test_name, source_dir, 0, benchmark.language,
                      cloud_build_tags=[
                            trial,
                            'Execution',
                            appr,
                            # TODO(dongge): Tag function name, compatible with tag format.
                            benchmark.project,
                        ]
                    )