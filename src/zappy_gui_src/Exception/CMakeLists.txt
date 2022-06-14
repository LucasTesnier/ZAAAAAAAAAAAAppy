set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Exception)
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Exception)

set (TARGET zappy_gui_exception)

set (SRC
    ${SRC_ROOT}/ZappyGuiException.cpp
    ${INCLUDE_ROOT}/ZappyGuiException.hpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)
