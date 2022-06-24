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

    /// \brief Class for core exception.
    class UnpackException : public ZappyGuiException {
        public:
            /// \brief  The exception of the core.
            UnpackException(std::string title = "Unpack Exception", std::string description = "Unknown error");
    };

    /// \brief Class for the server communication exception.
    class ServerCommunicationException : public ZappyGuiException {
        public:
            /// \brief  The exception of the server communication.
            ServerCommunicationException(std::string title = "Server Communication Exception", std::string description = "Unknown error");
    };

    /// \brief Class for the inventory exception.
    class InventoryException : public ZappyGuiException {
        public:
            /// \brief  The exception of the inventory.
            InventoryException(std::string title = "Inventory Exception", std::string description = "Unknown error");
    };

    /// \brief Class for the Tile exception.
    class TileException : public ZappyGuiException {
        public:
            /// \brief The exception of the server communication.
            TileException(std::string title = "Server Communication Exception", std::string description = "Unknown error");
    };

    /// \brief Class for the Animation exception. Use it only if an error occurs in the Animation class.
    class AnimationException : public ZappyGuiException {
        public:
            /// \brief The constructor of the Animation exception.
            /// \param title The title of the exception. `Animation Exception` is set by default.
            /// \param description The description of the exception. `Unknown error` is set by default.
            AnimationException(std::string title = "Animation Exception", std::string description = "Unknown error");
    };

    /// \brief Class for the Map exception. Use it only if an error occurs in the Map class.
    class MapException : public ZappyGuiException {
        public:
            /// \brief The constructor of the Map exception.
            /// \param title The title of the exception. `Map Exception` is set by default.
            /// \param description The description of the exception. `Unknown error` is set by default.
            MapException(std::string title = "Map Exception", std::string description = "Unknown error");
    };
} //namespace gui

#endif /* !ZAPPYGUIEXCEPTION_HPP_ */
