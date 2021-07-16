import os
import sys
import logging
import argparse
import json
import itertools
from typing import List, Dict, Optional

from vcast.utils import setup_logging
from vcast.utils import write_list_to_text


def _make_parser() -> argparse.ArgumentParser:
    """Defines the command line arguments for the module"""
    parser = argparse.ArgumentParser(
        description="Aggregates Vectorcast coverage results displayed in consolse output"
    )
    parser.add_argument(
        "--aquery_file",
        help="Path to Bazel test log files",
        type=str,
        required=True,
    )
    parser.add_argument(
        "--exec_dir",
        help="Bazel execution directory",
        type=str,
        required=True,
    )
    parser.add_argument(
        "--output_file",
        help="Path to output file with Vcast build commands",
        type=str,
    )
    parser.add_argument(
        "--compiler",
        help="Path to Bazel test log files",
        type=str,
        default="gcc",
    )
    return parser


def make_vcast_cmd(args: List[str]) -> str:
    """Returns the build command from the bazel action arguments in the format expected by Vcast"""
    return f"cmd::" + " ".join(args)


def get_vcast_commands(actions_file: str, exec_dir: str) -> List[str]:
    """
    Retrieves the build commands provided by the Bazel action query in the format
    expected by Vcast. For each command, an element containing the Bazel workspace path
    is given as expected by Vcast.
    """
    bazel_actions = _read_json(actions_file)
    args_key = "arguments"
    actions_args = [
        i_action[args_key]
        for i_action in bazel_actions["actions"]
        if i_action.get(args_key, None)
    ]
    commands = [[f"dir::{exec_dir}", make_vcast_cmd(i_args)] for i_args in actions_args]
    return list(itertools.chain.from_iterable(commands))


def _read_json(file_: str) -> Dict:
    """Reads the target file path as json with context manager"""
    with open(file_, "r") as f:
        json_content = json.load(f)
    return json_content


def get_commands_filename(actions_file: str) -> str:
    """Retrieves the output file name for the target Vcast commands file"""
    _, file = os.path.split(actions_file)
    name = file.split(".")[0]
    return f"{name}.vcshell.putcommand.txt"


def main() -> Optional[int]:
    """Creates a commands file expected by Vcast as part of intrsumentationfor code coverage"""
    setup_logging()
    args = _make_parser().parse_args()

    vcast_commands = get_vcast_commands(args.aquery_file, args.exec_dir)
    logging.info(f"vcast_commands: {vcast_commands}")

    out_filename = (
        args.output_file
        if args.output_file
        else get_commands_filename(args.aquery_file)
    )
    write_list_to_text(out_filename, vcast_commands, end_char="\n")
    logging.info(f"Wrote vcast put commands to {out_filename}")


if __name__ == "__main__":
    sys.exit(main())
