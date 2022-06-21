
set (INCLUDE_SRC ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Entity)

set (TARGET zappy_gui_entity)

set (SRC
    ${INCLUDE_SRC}/Entity.hpp
    ${INCLUDE_SRC}/Entity.cpp
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_SRC}
)