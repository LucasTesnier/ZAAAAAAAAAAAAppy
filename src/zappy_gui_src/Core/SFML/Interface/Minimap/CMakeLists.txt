set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Minimap)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Minimap)

set (MINIMAP_SRC
    ${SRC_ROOT}/Minimap.cpp
    ${INCLUDE_ROOT}/Minimap.hpp
    PARENT_SCOPE
)
