add_subdirectory(network)

set(AI_SRC ${PROJECT_SOURCE_DIR}/src/zappy_ai_src/zappy_ai)
set(AI_EXECUTABLE ${PROJECT_SOURCE_DIR}/zappy_ai)

execute_process(COMMAND ln -sf ${AI_SRC} ${AI_EXECUTABLE})