set (ENTITY_SRC_ROOT ${CMAKE_SOURCE_DIR}/src/zappy_server_src/core/entity)

set (ENTITY_SRC
    ${ENTITY_SRC_ROOT}/egg.c
    ${ENTITY_SRC_ROOT}/player.c
    ${ENTITY_SRC_ROOT}/tile.c
    ${ENTITY_SRC_ROOT}/entity.c
    PARENT_SCOPE
)