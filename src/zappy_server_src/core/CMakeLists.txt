set (INC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_server_src/core)

set (TARGET ${PROJECT_NAME}_server_core)

add_subdirectory(entity)
add_subdirectory(commands)

set (SRC
    ${SRC_ROOT}/server_run.c
    ${SRC_ROOT}/server_data.c
    ${SRC_ROOT}/server_init.c
    ${SRC_ROOT}/my_zappy_server.c
    ${SRC_ROOT}/command_hold.c
    ${COMMANDS_SOURCES}
    ${SRC_ROOT}/scheduler.c
    ${SRC_ROOT}/player_life.c
    ${SRC_ROOT}/scheduler_delete.c
    ${SRC_ROOT}/argument_handling.c
    ${SRC_ROOT}/ressource_generation.c
    ${SRC_ROOT}/container_utils.c
    ${SRC_ROOT}/map.c
    ${SRC_ROOT}/team.c
    ${SRC_ROOT}/teams_remove.c
    ${ENTITY_SRC}

    ${INC_ROOT}/entrypoint.h
    ${INC_ROOT}/my_zappy_server.h
    ${INC_ROOT}/server.h
    ${INC_ROOT}/command_hold.h
    ${INC_ROOT}/rcodes.h
    ${INC_ROOT}/scheduler/scheduler.h
    ${INC_ROOT}/argument_handling.h
    ${INC_ROOT}/container.h
    ${INC_ROOT}/map.h
    ${INC_ROOT}/team.h
)

set (ENTITY_INTERFACE_SRC
    ${INC_ROOT}/container.h
    ${INC_ROOT}/container_manip.h
    ${INC_ROOT}/entity/entity.h
    ${INC_ROOT}/entity/player.h
    ${INC_ROOT}/entity/tile.h
    ${INC_ROOT}/entity/eggs.h
    ${INC_ROOT}/entity/entity_types.h
    ${SRC_ROOT}/cmake_error.c
)

set (TARGET_ENTITY_INTERFACE ${PROJECT_NAME}_entity_interface)

add_library(${TARGET_ENTITY_INTERFACE} ${ENTITY_INTERFACE_SRC})

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INC_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PRIVATE net_utils
    PRIVATE ${TARGET_ENTITY_INTERFACE}
    PRIVATE uuid
    PRIVATE m
)