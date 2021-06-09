# Bazel test

## Bazel test command

`bazel test //test:calculator_test  --test_output=streamed`

Note: **--test_output=streamed:** Output from each test is printed as the test runs.

## Run all test targets
All the test targets inside `test` folder can be executed with command:

`bazel test //test/... --test_output=streamed`

## Example Output

`$bazel test //test:calculator_test  --test_output=streamed

WARNING: Streamed test output requested. All tests will be run locally, without sharding, one at a time
INFO: Analyzed target //test:calculator_test (27 packages loaded, 368 targets configured).
INFO: Found 1 test target...
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from CalcTest
[ RUN      ] CalcTest.Add
[       OK ] CalcTest.Add (0 ms)
[ RUN      ] CalcTest.Sub
[       OK ] CalcTest.Sub (0 ms)
[----------] 2 tests from CalcTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
Target //test:calculator_test up-to-date:
  bazel-bin/test/calculator_test
INFO: Elapsed time: 5.136s, Critical Path: 3.37s
INFO: 31 processes: 10 internal, 21 linux-sandbox.
INFO: Build completed successfully, 31 total actions
//test:calculator_test                                                   PASSED in 0.1s

Executed 1 out of 1 test: 1 test passes.
There were tests whose specified size is too big. Use the --test_verbose_timeout_warnings command line option to see INFO: Build completed successfully, 31 total actions`
