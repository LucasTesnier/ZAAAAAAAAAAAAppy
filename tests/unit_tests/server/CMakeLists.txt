set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/server)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/tests/unit_tests/server)

set(TEST_SRC_ROOT
    ${SRC_ROOT}/server_tests.c
)

create_test(
    TEST_NAME server_test
    TEST_SRC ${TEST_SRC_ROOT}
    TEST_DEPS ${PROJECT_NAME}_server_core net_utils
)
