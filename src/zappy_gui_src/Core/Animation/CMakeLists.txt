set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Animation)
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Animation)

set (TARGET zappy_gui_animation)

set (SRC
    ${SRC_ROOT}/Animation.cpp
    ${INCLUDE_ROOT}/Animation.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC zappy_gui_exception
)
