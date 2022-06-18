# set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)
# set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/Network)

set (TARGET zappy_gui_network)

# set (SRC
#     ${SRC_ROOT}/Unpack.cpp
#     ${INCLUDE_ROOT}/Unpack.hpp
# )

# add_library(${TARGET}_unpack ${SRC})

# target_include_directories(${TARGET}_unpack
#     PUBLIC ${INCLUDE_ROOT}
#     PRIVATE ${SRC_ROOT}
# )

add_subdirectory(api)
add_subdirectory(net_utils)

target_link_libraries(${TARGET}_unpack
    PUBLIC zappy_gui_exception
)
