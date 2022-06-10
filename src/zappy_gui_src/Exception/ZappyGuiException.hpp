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

class ZappyGuiException : std::exception {
    public:
        ZappyGuiException(std::string title = "ZappyGui", std::string description = "Unknown error");
        const char *what() const noexcept override;
    private:
        std::string _title;
        std::string _description;
        std::string _what;
};

class CoreException : public ZappyGuiException {
    public:
        CoreException(std::string title = "Core Exception", std::string description = "Unknown error");
};

#endif /* !ZAPPYGUIEXCEPTION_HPP_ */
