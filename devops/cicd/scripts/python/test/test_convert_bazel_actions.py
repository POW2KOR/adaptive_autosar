import os
import sys

import pytest

from devops.cicd.scripts.python.vcast import convert_bazel_actions
from common import tests_folder, read_lines


@pytest.fixture
def bazel_workspace():
    return "path/to/bazel_workspace/"


@pytest.fixture
def expected_cmd(tests_folder):
    cmd_file = os.path.join(tests_folder, "resources/vcast.vcshell.putcommand.txt")
    with open(cmd_file, "r") as f:
        expected_cmd = f.readlines()
    return [cmd.strip() for cmd in expected_cmd]


@pytest.fixture
def out_cmd_path(tests_folder):
    out_cmd_path = os.path.join(tests_folder, "resources/out.vcshell.putcommand.txt")
    yield out_cmd_path
    os.remove(out_cmd_path)


@pytest.fixture
def actions_path(tests_folder):
    return os.path.join(tests_folder, "resources/bazel_actions.json")


def test_get_commands_filename_from_file():
    """Tests the expected name of the target output file from the input actions file"""
    actions_name = "bazel_actions"
    target_out = f"{actions_name}.vcshell.putcommand.txt"

    assert target_out == convert_bazel_actions.get_commands_filename(
        f"{actions_name}.json"
    )

    assert target_out == convert_bazel_actions.get_commands_filename(
        f"/path/to/file/{actions_name}.json"
    )


def test_get_vcast_commands(actions_path, bazel_workspace, expected_cmd):
    """Tests the creation of build commands for Vcast from Bazel actions file"""
    vcast_commands = convert_bazel_actions.get_vcast_commands(
        actions_path, bazel_workspace
    )
    assert expected_cmd == vcast_commands


def test_main(monkeypatch, actions_path, bazel_workspace, expected_cmd, out_cmd_path):
    """Tests the main method of the module"""
    with monkeypatch.context() as m:
        m.setattr(
            sys,
            "argv",
            [
                "",
                "--aquery_file",
                actions_path,
                "--exec_dir",
                bazel_workspace,
                "--output_file",
                out_cmd_path,
            ],
        )
        convert_bazel_actions.main()
        assert expected_cmd == read_lines(out_cmd_path)


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))  # For Bazel
