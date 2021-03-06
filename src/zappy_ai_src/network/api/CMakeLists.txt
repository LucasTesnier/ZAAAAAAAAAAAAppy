set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_ai_src/network/api/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_ai_src/network/api)

set (TARGET ${PROJECT_NAME}_ai_api)

set (SRC
    ${SRC_ROOT}/authentification.c

    ${SRC_ROOT}/ask/join.c
    ${SRC_ROOT}/ask/inventory.c
    ${SRC_ROOT}/ask/send_request.c
    ${SRC_ROOT}/ask/forward.c
    ${SRC_ROOT}/ask/turn.c
    ${SRC_ROOT}/ask/look.c
    ${SRC_ROOT}/ask/broadcast.c
    ${SRC_ROOT}/ask/connectnbr.c
    ${SRC_ROOT}/ask/fork.c
    ${SRC_ROOT}/ask/eject.c
    ${SRC_ROOT}/ask/take.c
    ${SRC_ROOT}/ask/place.c
    ${SRC_ROOT}/ask/incantation.c

    ${SRC_ROOT}/get/state.c
    ${SRC_ROOT}/get/retcode.c
    ${SRC_ROOT}/get/join.c
    ${SRC_ROOT}/get/inventory.c
    ${SRC_ROOT}/get/forward.c
    ${SRC_ROOT}/get/turn.c
    ${SRC_ROOT}/get/look.c
    ${SRC_ROOT}/get/broadcast.c
    ${SRC_ROOT}/get/connectnbr.c
    ${SRC_ROOT}/get/fork.c
    ${SRC_ROOT}/get/eject.c
    ${SRC_ROOT}/get/take.c
    ${SRC_ROOT}/get/place.c
    ${SRC_ROOT}/get/incantation.c
    ${SRC_ROOT}/get/unexpected.c

    ${INCLUDE_ROOT}/api.h
    ${INCLUDE_ROOT}/intern_data.h
)

add_library(${TARGET} SHARED ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

set_target_properties(${TARGET} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/zappy_ai_src
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_ai_net_utils
)