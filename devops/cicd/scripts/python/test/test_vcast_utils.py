import os
import pytest
from vcast import utils


@pytest.fixture
def target_file_out():
    target_file_out = "vcast_commands.txt"
    yield target_file_out
    os.remove(target_file_out)


@pytest.fixture
def vcast_commands():
    vcast_commands = [
        "dir::/workspace_dir",
        "cmd::/usr/bin/gcc",
        "cmd::/usr/bin/ar",
    ]
    return vcast_commands


def _read_lines(file: str):
    with open(file, "r") as f:
        content = f.readlines()
    return content


def test_write_list_to_text(target_file_out, vcast_commands):
    """Tests the creation of a text file from a provided list"""
    utils.write_list_to_text(target_file_out, vcast_commands)
    written_commands = _read_lines(target_file_out)

    assert len(written_commands) == 1
    assert (
        written_commands[0] == vcast_commands[0] + vcast_commands[1] + vcast_commands[2]
    )


def test_write_list_to_text_with_char(target_file_out, vcast_commands):
    """Tests the creation of a text file from a provided list adding newline character"""
    append_char = "\n"
    utils.write_list_to_text(target_file_out, vcast_commands, end_char="\n")
    written_commands = _read_lines(target_file_out)

    assert len(written_commands) == len(vcast_commands)
    assert written_commands[0] == f"{vcast_commands[0]}{append_char}"
    assert written_commands[1] == f"{vcast_commands[1]}{append_char}"
    assert written_commands[2] == f"{vcast_commands[2]}{append_char}"
