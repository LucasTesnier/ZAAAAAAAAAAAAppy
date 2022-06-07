/*
** EPITECH PROJECT, 2022
** PLAZZAMIRROR
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

namespace gui {
    class Exception : public std::exception {
        public:

        ///\brief Construct a new Exception object
        ///\param message the message wich is throw by the exception
        ///\param component name of the component where the exception have been throw
        explicit Exception(std::string const &message, std::string const &component = "Unknow") : _component(component), _message(message){}

        ///\brief override of the what() function
        ///\return const char*
        [[nodiscard]] const char *what() const noexcept override {return _message.data();}

        ///\brief Get the component
        ///\return const std::string&
        [[nodiscard]] const std::string &getComponent() const noexcept{return _component;}

        protected:
        private:

        ///\brief name of the component (function for example) where the exception has been raised
        std::string const _component;

        ///\brief message describing the exception
        std::string const _message;
    };

    class ErrorArgs : public Exception {
        public:

        ///\brief Construct a new Error Args object
        ///\param message the message wich is throw by the exception
        ///\param component name of the component where the exception have been throw
        explicit ErrorArgs(std::string const &message, std::string const &component = "Unknow") : gui::Exception(message, component) {}
    };
};
