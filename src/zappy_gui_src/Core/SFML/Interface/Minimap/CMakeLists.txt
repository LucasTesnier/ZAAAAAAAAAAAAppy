set (INCLUDE_MINIMAP ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Minimap)
set (SRC_MINIMAP ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Minimap)

set (MINIMAP_SRC
    ${SRC_MINIMAP}/Minimap.cpp
    ${INCLUDE_MINIMAP}/Minimap.hpp
    PARENT_SCOPE
)
