set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/net_utils/fd_sets_manage)

set (SRC_FD_SET_MANAGE
    ${INCLUDE_ROOT}/fd_sets_manage.c
    ${INCLUDE_ROOT}/server_accept_new_client.c
    ${INCLUDE_ROOT}/server_read_client.c
    ${INCLUDE_ROOT}/server_write_client.c
    ${INCLUDE_ROOT}/server_close_client.c
    PARENT_SCOPE
)