# Copyright 2025 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
Usage:
  docker_run.py [options]
"""

import argparse
import datetime
import logging
import os
import subprocess
import sys

from google.cloud import storage

# Configure logging to display all messages at or above INFO level
logging.basicConfig(level=logging.INFO)

BENCHMARK_SET = 'comparison'
FREQUENCY_LABEL = 'daily'
RUN_TIMEOUT = 300
SUB_DIR = 'default'
MODEL = 'vertex_ai_gemini-1-5'
DELAY = 0
NUM_SAMPLES = 10
LLM_FIX_LIMIT = 5
MAX_ROUND = 100
DATA_DIR = '/experiment/data-dir/'
BUCKET_NAME = 'oss-fuzz-gcb-experiment-run-logs'


def _parse_args(cmd) -> argparse.Namespace:
  """Parses the command line arguments."""
  parser = argparse.ArgumentParser(description='Run experiments')
  parser.add_argument(
      '-pj',
      '--project',
      default='',
      help='The name of the project to run fuzzing trials for')

  parser.add_argument(
      '-sd',
      '--sub-dir',
      type=str,
      default=SUB_DIR,
      help=
      f'The subdirectory for the generated report in GCS, default: {SUB_DIR}.')

  parser.add_argument(
      '-a',
      '--approach',
      default=['ofg', 'bluebird_ofg', 'promefuzz', 'bluebird_promefuzz'],
      nargs="+",
      help='Fuzz the harnesses for each given approach')

  parser.add_argument(
      '-nt',
      '--num-trials',
      default=1,
      help='The number of fuzzing trials to run')

  parser.add_argument(
      '-ps',
      '--pool-size',
      default=8,
      help='The number of fuzzing trials to run concurrently')

  parser.add_argument(
      '-l',
      '--frequency-label',
      type=str,
      default=FREQUENCY_LABEL,
      help=(f'Used as part of Cloud Build tags and GCS report directory, '
            f'default: {FREQUENCY_LABEL}.'))
                    
  parser.add_argument(
      '-to',
      '--run-timeout',
      type=int,
      default=RUN_TIMEOUT,
      help=f'Fuzzing timeout in seconds, default: {RUN_TIMEOUT} seconds.')

  parser.add_argument(
      '-rd',
      '--redirect-outs',
      type=str,
      default="false",
      help=
      'Redirects experiments stdout/stderr to file. Set to "true" to enable.')

  args, additional_args = parser.parse_known_args(cmd)

  # Arguments after the first element ("--") separator.
  args.additional_args = additional_args[1:]

  return args


def _run_command(command: list[str], shell=False):
  """Runs a command and return its exit code."""
  process = subprocess.run(command, shell=shell, check=False)
  return process.returncode


def _authorize_gcloud():
  """Authorizes to gcloud"""
  # When running the docker container locally we need to activate the service
  # account from the env variable.
  # When running on GCP this step is unnecessary.
  google_creds = os.environ.get('GOOGLE_APPLICATION_CREDENTIALS', '')
  if google_creds:
    logging.info("GOOGLE APPLICATION CREDENTIALS set: %s.", google_creds)
    _run_command([
        'gcloud', 'auth', 'activate-service-account',
        'LLM-EVAL@oss-fuzz.iam.gserviceaccount.com', '--key-file', google_creds
    ])
  else:
    # TODO: Set GOOGLE_APPLICATION_CREDENTIALS and ensure cloud build uses it.
    logging.info("GOOGLE APPLICATION CREDENTIALS is not set.")

def _log_common_args(args):
  """Prints args useful for logging"""
  logging.info("Target project is %s.", args.project)
  logging.info("Harnesses for approach %s is being fuzzed.", ', '.join(args.approach))
  logging.info("Frequency label is %s.", args.frequency_label)
  logging.info("Fuzzing for a total of %s(s).", args.run_timeout)
  logging.info("Num trials: %s.", args.num_trials)
  logging.info("Pool size: %s.", args.pool_size)

def main(cmd=None):
  """Main entrypoint"""
  run_fuzz_trial(cmd)

def run_fuzz_trial(cmd=None):
  """Run fuzzing trials on supplied harnesses."""
  args = _parse_args(cmd)

  # Uses python3 by default and /venv/bin/python3 for Docker containers.
  python_path = "/venv/bin/python3" if os.path.exists(
      "/venv/bin/python3") else "python3"
  os.environ["PYTHON"] = python_path

  _authorize_gcloud()
  _log_common_args(args)

  date = datetime.datetime.now().strftime('%Y-%m-%d')
  local_results_dir = 'results'
  os.makedirs(local_results_dir, exist_ok=True)

  # Example directory: 2023-12-02-daily-comparison
  experiment_name = f"{date}-{args.frequency_label}-{args.project}"
  gcs_report_dir = f"{args.sub_dir}/{experiment_name}"
  report_cmd = [
      "bash", "report/upload_fuzz_report.sh", local_results_dir, gcs_report_dir
  ]

  # Generate a report and upload it to GCS
  report_process = subprocess.Popen(report_cmd)


  # Experiment name is used to label the Cloud Builds and as part of the
  # GCS directory that build logs are stored in.

  # Prepare the command to run experiments
  run_cmd = [
    python_path, "run_driver.py", 
    "--project", args.project,
    "--approach", *args.approach,
    "--fuzz-timeout", str(args.run_timeout), 
    "--num-trials", str(args.num_trials), 
    "--pool-size", str(args.pool_size), 
    "--cloud-experiment-name", experiment_name,
    "--cloud-experiment-bucket", BUCKET_NAME,
    "--results-dir", local_results_dir,
  ]

  # Run the experiment and redirect to file if indicated.
  if args.redirect_outs:
    local_output_path = f"{local_results_dir}/logs-from-run.txt"
    with open(local_output_path, "w") as outfile:
      process = subprocess.run(run_cmd,
                               stdout=outfile,
                               stderr=outfile,
                               check=False)
      ret_val = process.returncode
      logging.info("Finished run_driver.py")

      upload_log_to_bucket_cmd = [
        "gsutil",
        "cp",
        f"{local_results_dir}/logs-from-run.txt",
        f"gs://{BUCKET_NAME}/Result-reports/{gcs_report_dir}/"
      ]

  else:
    process = subprocess.run(run_cmd, check=False)
    ret_val = process.returncode

  os.environ["ret_val"] = str(ret_val)


  with open("/experiment_ended", "w"):
    pass

  # Exit with the return value of `./run_all_experiments`.
  return ret_val

if __name__ == "__main__":
  sys.exit(main())
