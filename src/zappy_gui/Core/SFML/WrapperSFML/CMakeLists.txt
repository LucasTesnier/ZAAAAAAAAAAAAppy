set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/Core/SFML/WrapperSFML)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/Core/SFML/WrapperSFML)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

set (TARGET wrapper_sfml)

add_library(${TARGET} INTERFACE)

target_include_directories(${TARGET}
    INTERFACE ${INCLUDE_ROOT}
)

target_link_libraries(${TARGET}
    INTERFACE ${SFML_LIBRARIES}
)
