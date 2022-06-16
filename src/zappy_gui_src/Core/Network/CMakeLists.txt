set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)

set (TARGET zappy_gui)

set (SRC
    ${SRC_ROOT}/Unpack.cpp
    ${INCLUDE_ROOT}/Unpack.hpp
)

add_library(${TARGET}_unpack ${SRC})

target_include_directories(${TARGET}_unpack
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

# target_link_libraries(${TARGET}_unpack
#     PUBLIC ${TARGET}_map
#     PUBLIC ${TARGET}_interface
# )

# add_subdirectory(Map)
# add_subdirectory(Interface)
# add_subdirectory(WrapperSFML)
