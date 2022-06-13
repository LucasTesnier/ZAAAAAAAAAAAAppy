find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface)

set (TARGET zappy_gui_interface)

set (SRC
    ${INCLUDE_ROOT}/Interface.hpp
    ${SRC_ROOT}/Interface.cpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC wrapper_sfml
)
