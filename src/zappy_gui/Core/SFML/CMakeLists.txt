set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/Core/SFML)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/Core/SFML)

set (TARGET zappy_gui)

set (SRC
    ${SRC_ROOT}/SFML.cpp
    ${INCLUDE_ROOT}/SFML.hpp
)

add_library(${TARGET}_sfml ${SRC})

target_include_directories(${TARGET}_sfml
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}_sfml
    PUBLIC ${TARGET}_map
    PUBLIC ${TARGET}_interface
)

add_subdirectory(Map)
add_subdirectory(Interface)
add_subdirectory(WrapperSFML)
