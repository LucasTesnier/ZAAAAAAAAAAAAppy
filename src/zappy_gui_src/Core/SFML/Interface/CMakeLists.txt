find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface)

set (TARGET zappy_gui_interface)

add_subdirectory(Minimap)
add_subdirectory(Inventory)

set (SRC
    ${INCLUDE_ROOT}/Interface.hpp
    ${SRC_ROOT}/Interface.cpp
    ${MINIMAP_SRC}
    ${INVENTORY_SRC}
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PUBLIC ${INCLUDE_ROOT}/Minimap
    PUBLIC ${INCLUDE_ROOT}/Inventory
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC wrapper_sfml
)
