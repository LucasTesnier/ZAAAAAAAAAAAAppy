set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src/zappy_gui)

set (TARGET zappy_gui)

set (SRC
    ${SRC_DIR}/main.cpp
)

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_DIR}
)

target_link_libraries(${TARGET}
    PUBLIC ${TARGET}_core
)

add_subdirectory(Core)
add_subdirectory(network)
