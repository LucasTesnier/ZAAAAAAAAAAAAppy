set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core)

set (TARGET zappy_gui)

set (SRC
    ${SRC_ROOT}/Core.cpp
    ${INCLUDE_ROOT}/Core.hpp
)

add_library(${TARGET}_core SHARED ${SRC})

target_include_directories(${TARGET}_core
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}_core
    PUBLIC zappy_gui_sfml
    PUBLIC zappy_gui_exception
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# add_subdirectory(Network)
add_subdirectory(SFML)
