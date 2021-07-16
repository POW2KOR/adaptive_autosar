import os
import sys

import pytest

from vcast import merge_coverage_results
from .common import tests_folder, read_lines


@pytest.fixture
def expected_testinss(tests_folder):
    testinss_file = os.path.join(tests_folder, "resources/TESTINSS.DAT")
    with open(testinss_file, "r") as f:
        expected_testinss = f.readlines()
    return [line.strip() for line in expected_testinss]


@pytest.fixture
def out_testinss_path(tests_folder):
    out_test_instrumented = os.path.join(tests_folder, "resources/OUT_TESTINSS.DAT")
    yield out_test_instrumented
    os.remove(out_test_instrumented)


def test_is_vcast_coverage():
    """Tests whether commonly known Vcast test logs are detected"""
    assert merge_coverage_results.is_vcast_coverage("2000a1 1 1")
    assert merge_coverage_results.is_vcast_coverage("2000 3")
    assert merge_coverage_results.is_vcast_coverage("2000b0 3 3")
    assert merge_coverage_results.is_vcast_coverage("2000b0 0 3")


def test_is_not_vcast_coverage():
    """Tests whether commonly known Bazel test logs are ignored"""
    assert not merge_coverage_results.is_vcast_coverage(
        "Running main() from gmock_main.cc"
    )
    assert not merge_coverage_results.is_vcast_coverage(
        "[----------] 2 tests from CalcTest"
    )
    assert not merge_coverage_results.is_vcast_coverage("[ RUN      ] CalcTest.Add")
    assert not merge_coverage_results.is_vcast_coverage("[  PASSED  ] 2 tests.")
    assert not merge_coverage_results.is_vcast_coverage("0 3 2000b0")


def test_get_merged_coverage(tests_folder):
    """Tests whether all the Vcast log lines are retrieved"""
    test_logs_path = os.path.join(tests_folder, "resources")
    cov_results = merge_coverage_results.get_merged_coverage(test_logs_path)
    num_expected_vcast_logs = 17
    assert len(cov_results) == num_expected_vcast_logs


def test_main(monkeypatch, tests_folder, out_testinss_path, expected_testinss):
    """Tests the main method of the module"""
    with monkeypatch.context() as m:
        m.setattr(
            sys,
            "argv",
            [
                "",
                "--test_logs",
                os.path.join(tests_folder, "resources"),
                "--output_file",
                out_testinss_path,
            ],
        )
        merge_coverage_results.main()
        assert expected_testinss == read_lines(out_testinss_path)
