find_package(Python COMPONENTS Interpreter REQUIRED)

add_test(NAME zappy_ai_unit_test
    COMMAND ${Python_EXECUTABLE} -m pytest ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src/zappy_ai_src
)