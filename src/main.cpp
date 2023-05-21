/*******************************************************************************************
*
*   raylib [audio] example - Sound loading and playing
*
*   Example originally created with raylib 1.1, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <iostream>
#include <cmath>
#include "raylib.h"
#include "raylib-cpp.hpp"

#define WHITE_MODE true
// if white mode true, then every key are mapped to white keys.

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - sound loading and playing");

    //InitAudioDevice();      // Initialize audio device
    raylib::AudioDevice audiodevice;      // Initialize audio device

    raylib::Sound A4("resources/A4.wav");         // Load WAV audio file

    raylib::Sound Keys[40][3];
    float volume[40][3] = {0,};
    int rotation[40] = {0,};
    int Keymap[40] = {'Z', 'X', 'C', 'V', 'B', 'A', 'S', 'D', 'F', 'G', 'Q', 'W', 'E', 'R', 'T', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'Y', 'U', 'I', 'O', 'P', 'H', 'J', 'K', 'L', ';', 'N', 'M', ',', '.', '/'};
    int whiteIndex[] = {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 33, 35, 36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65};
    float sustain = 0.99;
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 3; j++){
            // I have A4, and A5, A6.
            // A4 is 440Hz, A5 is 880Hz.
            // A4 is 9th key, A5 is 21st key.
            #ifndef WHITE_MODE // if white mode true, then every key are mapped to white keys.
            if(i<21) {
                Keys[i][j].Load("resources/A4.wav");
                Keys[i][j].SetPitch(std::pow(2, (i-9)/12.0));
            }else if(i<33){
                Keys[i][j].Load("resources/A5.wav");
                Keys[i][j].SetPitch(std::pow(2, (i-21)/12.0));
            }else{
                Keys[i][j].Load("resources/A6.wav");
                Keys[i][j].SetPitch(std::pow(2, (i-33)/12.0));
            }
            #else
            if(whiteIndex[i]<21) {
                Keys[i][j].Load("resources/A4.wav");
                Keys[i][j].SetPitch(std::pow(2, (whiteIndex[i]-9-12)/12.0));
            }else if(whiteIndex[i]<33){
                Keys[i][j].Load("resources/A5.wav");
                Keys[i][j].SetPitch(std::pow(2, (whiteIndex[i]-21-12)/12.0));
            }else{
                Keys[i][j].Load("resources/A6.wav");
                Keys[i][j].SetPitch(std::pow(2, (whiteIndex[i]-33-12)/12.0));
            }
            #endif
        }
    }

    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        for(int i = 0; i < 40; i++){
            if(IsKeyPressed(Keymap[i])){
                volume[i][rotation[i]] = 1.0f;
                Keys[i][rotation[i]].SetVolume(volume[i][rotation[i]]);
                Keys[i][rotation[i]].Play();
            }else if(IsKeyReleased(Keymap[i])){
                rotation[i] = (rotation[i] + 1) % 3;
            }
            // decrease volume over time for not selected sounds
            for(int j = 0; j < 3; j++){
                if(j != rotation[i]){
                    volume[i][j] = std::max(0.0f, volume[i][j]*sustain);
                    Keys[i][j].SetVolume(volume[i][j]);
                }
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, LIGHTGRAY);
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();     // Close audio device

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}