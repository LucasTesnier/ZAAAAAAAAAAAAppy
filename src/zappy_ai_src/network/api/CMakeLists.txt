set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_ai_src/network/api/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_ai_src/network/api)

set (TARGET ${PROJECT_NAME}_ai_api)

set (SRC
    ${SRC_ROOT}/authentification.c

    ${INCLUDE_ROOT}/api.h
)

add_library(${TARGET} ${SRC})

target_include_directories(${TARGET}
    PUBLIC ${INCLUDE_ROOT}
    PRIVATE ${SRC_ROOT}
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_ai_net_utils
)