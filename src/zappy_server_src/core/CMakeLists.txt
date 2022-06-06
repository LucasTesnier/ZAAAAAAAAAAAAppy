set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core)

set (TARGET ${PROJECT_NAME}_server_core)

set (SRC
    ${SRC_ROOT}/server_run.c

    ${INC_ROOT}/entrypoint.h
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PRIVATE net_utils
)