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
    ${SRC_ROOT}/fork_utils.c
    ${SRC_ROOT}/eject_command.c
    ${SRC_ROOT}/take_command.c
    ${SRC_ROOT}/place_command.c
    ${SRC_ROOT}/incantation_command.c
    ${SRC_ROOT}/unexpected_send.c
    ${SRC_ROOT}/game_status.c
    ${SRC_ROOT}/map_info.c
    ${SRC_ROOT}/entity_info.c
    ${SRC_ROOT}/start_information.c
    ${SRC_ROOT}/broadcast_process.c
    ${SRC_ROOT}/look_process.c
    ${SRC_ROOT}/look_utils.c
    ${SRC_ROOT}/eject_process.c

    PARENT_SCOPE
)