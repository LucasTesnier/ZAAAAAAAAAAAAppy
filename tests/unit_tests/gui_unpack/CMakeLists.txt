set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/gui_unpack)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/gui_unpack)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/TestsUnpack.cpp
)

create_test(
    TEST_NAME unpack_test
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_gui_core
    # Note the test is automatically linked to the testing framework and added to the test suite
)