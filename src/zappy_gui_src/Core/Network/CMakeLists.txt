set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)

set (TARGET zappy_gui_network)

set (SRC
    ${SRC_ROOT}/Unpack.cpp
    ${INCLUDE_ROOT}/Unpack.hpp
)

add_library(${TARGET}_unpack ${SRC})

target_include_directories(${TARGET}_unpack
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

add_subdirectory(api)
add_subdirectory(net_utils)

target_link_libraries(${TARGET}_unpack
    PUBLIC zappy_gui_exception
)


set (TARGET_TEST ${PROJECT_NAME}_gui_test)

set (SRC_TEST
    ${SRC_ROOT}/entrypoint.c
)

add_executable(${TARGET_TEST} ${SRC_TEST})

target_include_directories(${TARGET_TEST}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET_TEST}
    PUBLIC ${PROJECT_NAME}_gui_api
)

set_target_properties(${TARGET_TEST} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)