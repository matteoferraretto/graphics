#include <SDL.h>
#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Rectangle.h"


int main(int argc, char* argv[]){
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    Rectangle rectangle = Rectangle(400, 100, 100, 100, 0.0f, 4.0f, COLOR_NICE_ORANGE);
    float vx = 10.0f;
    float vy = 6.0f;
    Circle circle = Circle(150.0f, 50.0f, 40.0f, vx, vy, COLOR_NICE_ORANGE);


    bool running = true;
    SDL_Event event;

    while(running){
        // check if user wants to exit the application
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) { running = false; }
        }

        // move the rectangle
        rectangle.MoveRectangleUnderGravity(surface, rectangle, vx, vy);
        // check and manage collisions
        circle.CheckCollisionWithRectangle(surface, circle, rectangle);
        circle.MoveCircleUniformly(surface, circle, vx, vy);
        //circle.MoveCircleUnderGravity(surface, circle, vx, vy);


        SDL_UpdateWindowSurface(window);
        SDL_Delay(SCREEN_REFRESH_TIME);
    }
    
    return 0;
}