set (INCLUDE_INVENTORY ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Inventory)
set (SRC_INVENTORY ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/Inventory)

set (INVENTORY_SRC
    ${SRC_INVENTORY}/Inventory.cpp
    ${INCLUDE_INVENTORY}/Inventory.hpp
    PARENT_SCOPE
)
