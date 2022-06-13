set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/wrapper)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/wrapper)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/wrapper_tests.c
)

create_test(
    TEST_NAME wrapper_test
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_server_core
)
