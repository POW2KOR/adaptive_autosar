import os

import pytest


def read_lines(file_path):
    with open(file_path, "r") as f:
        content = f.readlines()
    return [line.strip() for line in content]


@pytest.fixture
def tests_folder():
    folder_path, _ = os.path.split(__file__)
    return folder_path
