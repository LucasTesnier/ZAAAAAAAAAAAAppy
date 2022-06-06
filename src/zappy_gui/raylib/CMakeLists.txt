set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/raylib)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/raylib)

set(SRC
    ${SRC_ROOT}/Raylib.cpp
    ${SRC_ROOT}/Raylib.hpp
)

set(TARGET ${PROJECT_NAME}_raylib)

add_library(${TARGET} ${SRC})

target_link_libraries(${TARGET} raylib)

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)
