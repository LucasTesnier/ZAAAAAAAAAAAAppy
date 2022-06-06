set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core)

set (TARGET ${PROJECT_NAME}_server_core)

set (SRC
    ${SRC_ROOT}/server_run.c
    ${SRC_ROOT}/server_data.c
    ${SRC_ROOT}/my_zappy_server.c
    ${SRC_ROOT}/command_hold.c

    ${INC_ROOT}/entrypoint.h
    ${INC_ROOT}/my_zappy_server.h
    ${INC_ROOT}/server.h
    ${INC_ROOT}/command_hold.h
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PRIVATE net_utils
)