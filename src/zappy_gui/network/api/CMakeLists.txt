set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network/api/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui/network/api)

set (TARGET ${PROJECT_NAME}_gui_api)

set (SRC
    ${SRC_ROOT}/authentification.c

    ${SRC_ROOT}/ask/restart.c

    ${SRC_ROOT}/get/retcode.c
    ${SRC_ROOT}/get/state.c
    ${SRC_ROOT}/get/restart.c
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
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/zappy_gui
)

target_link_libraries(${TARGET}
    PUBLIC ${PROJECT_NAME}_gui_net_utils
)