/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Raylib
*/

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

#include "raylib.h"

class Raylib {
    public:
        Raylib();
        ~Raylib();
        void run();
    private:
        Camera3D _camera;
        Vector3 _cubePosition;
};

#endif /* !RAYLIB_HPP_ */
