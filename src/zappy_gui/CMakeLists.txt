set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/zappy_gui)

set(SRC
    ${SRC_ROOT}/main.cpp
)

set(TARGET ${PROJECT_NAME}_gui)

add_executable(${TARGET} ${SRC})

find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED

target_link_libraries(${TARGET}
    PRIVATE ${PROJECT_NAME}_raylib
)

add_subdirectory(raylib)