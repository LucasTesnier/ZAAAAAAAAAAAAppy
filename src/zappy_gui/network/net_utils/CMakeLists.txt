set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network/net_utils/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network/net_utils)

set (SRC
    ${SRC_ROOT}/client_utils.c
    ${SRC_ROOT}/send_message.c
    ${SRC_ROOT}/fetch_message.c
    ${SRC_ROOT}/update_client.c
    ${SRC_ROOT}/manage_fd_sets.c
    ${INCLUDE_ROOT}/internals.h
    ${INCLUDE_ROOT}/client_utils.h
)

add_library(${PROJECT_NAME}_gui_net_utils
    ${SRC}
)

target_include_directories(${PROJECT_NAME}_gui_net_utils
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)
