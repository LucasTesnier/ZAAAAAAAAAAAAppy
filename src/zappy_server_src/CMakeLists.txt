set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src)

set (TARGET ${PROJECT_NAME}_server)

set (SRC
    ${SRC_ROOT}/entrypoint.c
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${TARGET}_core
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_subdirectory(net_utils)
add_subdirectory(core)