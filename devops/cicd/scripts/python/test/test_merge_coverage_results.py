import os
import pytest
from vcast import merge_coverage_results


@pytest.fixture
def tests_folder():
    folder_path, _ = os.path.split(__file__)
    return folder_path


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
