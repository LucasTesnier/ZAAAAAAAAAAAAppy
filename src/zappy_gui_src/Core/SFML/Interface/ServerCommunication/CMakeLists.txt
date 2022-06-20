set (INCLUDE_SERVERCOMMUNICATION ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/ServerCommunication)
set (SRC_SERVERCOMMUNICATION ${PROJECT_SOURCE_DIR}/src/zappy_gui_src/Core/SFML/Interface/ServerCommunication)

set (SERVERCOMMUNICATION_SRC
    ${SRC_SERVERCOMMUNICATION}/ServerCommunication.cpp
    ${INCLUDE_SERVERCOMMUNICATION}/ServerCommunication.hpp
    PARENT_SCOPE
)
