set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/path/to/tests/src)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/path/to/tests/src)

set(TEST_SRC_ROOT
    ${SRC_ROOT}
)

create_test(
    NAME TEST_NAME
    TEST_SRC TEST_SRC_ROOT
    TEST_DEPS Any dependencies required by the test (such as archive created by cmake etc...)
    # Note the test is automatically linked to the testing framework and added to the test suite
)