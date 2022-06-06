/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Raylib
*/

#include "Raylib.hpp"

Raylib::Raylib()
{
    InitWindow(1920, 1080, "Raylib");
    SetTargetFPS(60);
    _camera.position.x = 0;
    _camera.position.y = 10;
    _camera.position.z = 10;
    _camera.target.x = 0;
    _camera.target.y = 0;
    _camera.target.z = 0;
    _camera.up.x = 0;
    _camera.up.y = 1;
    _camera.up.z = 0;
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
    _cubePosition.x = 0;
    _cubePosition.x = 0;
    _cubePosition.x = 0;
    SetCameraMode(_camera, CAMERA_FREE);
    ShowCursor();
}

void Raylib::run()
{
    while (!WindowShouldClose()) {
        UpdateCamera(&_camera);
        BeginDrawing();
            ClearBackground(WHITE);
            BeginMode3D(_camera);
                DrawGrid(10, 1.0f);
            EndMode3D();
        EndDrawing();
    }
}

Raylib::~Raylib()
{
    CloseWindow();
}
