set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src/zappy_gui)

set (SRC
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/launch_gui.cpp
)

add_executable(zappy_gui ${SRC})

target_include_directories(zappy_gui
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_DIR}
)
