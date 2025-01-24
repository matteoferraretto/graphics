#pragma once;
#include <SDL.h>
#include <SDL_ttf.h>
#include "Rectangle.h"
#include "Circle.h"
#include <sstream>
#include <string>

class Pong
{
private:
    SDL_Window * window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    SDL_Renderer * renderer = SDL_CreateSoftwareRenderer(surface);
    TTF_Font * font = TTF_OpenFont("C:\\Users\\matte\\C++_libraries\\fonts\\pixelletters-font\\Pixellettersfull-BnJ5.ttf", 24);
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    std::string textScore = "SCORE : ";
    int score = 0;

public:
    Pong(/* args */);

    void init(void);

    ~Pong();
};

Pong::Pong(/* args */)
{
}

Pong::~Pong()
{
}
