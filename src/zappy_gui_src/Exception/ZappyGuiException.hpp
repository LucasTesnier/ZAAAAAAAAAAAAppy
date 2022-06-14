/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** ZappyGuiException
*/

#ifndef ZAPPYGUIEXCEPTION_HPP_
#define ZAPPYGUIEXCEPTION_HPP_

#include <exception>
#include <string>

namespace gui {
    /// \brief Global class exception for the zappy_gui.
    class ZappyGuiException : std::exception {
        public:

            /// \brief The exception of the zappy_gui.
            ZappyGuiException(std::string title = "ZappyGui", std::string description = "Unknown error");

            /// \brief Return a message corresponding of the error.
            const char *what() const noexcept override;
        private:

            /// \brief The title of the error.
            std::string _title;

            /// \brief The description of the error.
            std::string _description;

            /// \brief The message error to show when use what function.
            std::string _what;
    };

    /// \brief Class for core exception.
    class CoreException : public ZappyGuiException {
        public:
            /// \brief  The exception of the core.
            CoreException(std::string title = "Core Exception", std::string description = "Unknown error");
    };
} //namespace gui

#endif /* !ZAPPYGUIEXCEPTION_HPP_ */
