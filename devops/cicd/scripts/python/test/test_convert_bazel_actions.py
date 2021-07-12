import os
import pytest
from vcast import convert_bazel_actions


@pytest.fixture
def tests_folder():
    folder_path, _ = os.path.split(__file__)
    return folder_path


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


def test_get_vcast_commands(tests_folder):
    """Tests the creation of build commands for Vcast from Bazel actions file"""
    actions_path = os.path.join(tests_folder, "resources/bazel_actions.json")
    workspace_path = "path/to/bazel_workspace/"
    vcast_commands = convert_bazel_actions.get_vcast_commands(
        actions_path, workspace_path
    )

    num_commands = 6
    cmd_dir = f"dir::{workspace_path}"
    cmd_compiler = f"cmd::/usr/bin/gcc"
    cmd_archive = f"cmd::/usr/bin/ar"

    assert vcast_commands[0] == cmd_dir
    assert vcast_commands[1].startswith(cmd_compiler)
    assert vcast_commands[2] == cmd_dir
    assert vcast_commands[3].startswith(cmd_archive)
    assert vcast_commands[4] == cmd_dir
    assert vcast_commands[5].startswith(cmd_compiler)
    assert len(vcast_commands) == num_commands
