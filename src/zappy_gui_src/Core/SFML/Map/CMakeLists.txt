set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Map)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Map)

set (TARGET zappy_gui_map)

set (SRC
    ${SRC_ROOT}/Map.cpp
    ${INCLUDE_ROOT}/Map.hpp
    ${SRC_ROOT}/Tile.cpp
    ${INCLUDE_ROOT}/Tile.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC wrapper_sfml
)
