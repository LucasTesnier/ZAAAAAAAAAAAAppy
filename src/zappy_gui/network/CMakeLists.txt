set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network)

set (TARGET ${PROJECT_NAME}_gui_test)

set (SRC
    ${SRC_ROOT}/entrypoint.c
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_gui_api
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_subdirectory(net_utils)
add_subdirectory(api)