import sys
import argparse
import logging
from pathlib import Path
from typing import List, Optional
import re

from vcast.utils import setup_logging
from vcast.utils import write_list_to_text


def _make_parser() -> argparse.ArgumentParser:
    """Defines the command line arguments for the module"""
    parser = argparse.ArgumentParser(
        description="Aggregates Vectorcast coverage results displayed in consolse output"
    )
    parser.add_argument(
        "--test_logs",
        help="Path to Bazel test log files",
        type=str,
        required=True,
    )
    parser.add_argument(
        "--output_file",
        help="Path to Bazel test log files",
        type=str,
        default="TESTINSS.DAT",
    )
    return parser


def is_vcast_coverage(line: str):
    """Determines whether the given input correpsponds to Vcast coverage information"""
    pattern = re.compile("^2000[a-z ][0-9]( [0-9] [0-9])?$")
    return True if pattern.search(line) else False


def get_coverage_lines(path: Path) -> List:
    """Retrieves the coverage related lines from a Bazel test log file"""
    with open(path.absolute(), "r") as file_:
        cov_lines = [line for line in file_.readlines() if is_vcast_coverage(line)]
    return cov_lines


def get_merged_coverage(tests_logs_folder: str) -> List:
    """Retrieves the aggregated Vcast coverage results"""
    merged_cov_lines = []
    bazel_test_log_file = "test.log"
    for path in Path(tests_logs_folder).rglob(bazel_test_log_file):
        cov_lines = get_coverage_lines(path)
        merged_cov_lines = merged_cov_lines + cov_lines
    return merged_cov_lines


def main() -> Optional[int]:
    """Creates a file with aggregated Vcast coverage results from Bazel test logs"""
    setup_logging()
    args = _make_parser().parse_args()
    merged_coverage_lines = get_merged_coverage(args.test_logs)
    logging.info(f"merged_coverage_lines {merged_coverage_lines}")
    write_list_to_text(args.output_file, merged_coverage_lines)


if __name__ == "__main__":
    sys.exit(main())
