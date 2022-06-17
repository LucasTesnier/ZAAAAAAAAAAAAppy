set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core/commands)

set (COMMANDS_SOURCES
    ${SRC_ROOT}/auth_command.c
    ${SRC_ROOT}/join_command.c
    ${SRC_ROOT}/inventory_command.c
    ${SRC_ROOT}/forward_command.c
    ${SRC_ROOT}/turn_command.c
    ${SRC_ROOT}/look_command.c
    ${SRC_ROOT}/broadcast_command.c
    ${SRC_ROOT}/connectnbr_command.c
    ${SRC_ROOT}/fork_command.c
    ${SRC_ROOT}/eject_command.c

    PARENT_SCOPE
)