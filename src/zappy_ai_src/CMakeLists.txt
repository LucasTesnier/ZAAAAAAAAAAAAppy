add_subdirectory(network)

set(AI_SRC ${PROJECT_SOURCE_DIR}/src/zappy_ai_src)
set(AI_EXECUTABLE ${PROJECT_SOURCE_DIR}/zappy_ai)

execute_process(COMMAND "ln -sf " + ${AI_SRC}/zappy_ai + " " + ${AI_EXECUTABLE})