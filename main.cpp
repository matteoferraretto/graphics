#include <SDL.h>
#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Rectangle.h"

/*
bool collision_with_floor(SDL_Rect rect){
    if(rect.y + rect.h > SCREEN_HEIGHT) {return true;}
    else { return false; }
}

void move_rectangle(SDL_Surface * surface, SDL_Rect & rect, float & vy){
    int current_y = rect.y; // save current position
    SDL_FillRect(surface, &rect, COLOR_BLACK);
    // if collision, modify position 
    if(collision_with_floor(rect)){ 
        // std::cout << "i'm here.\n";
        rect.y = SCREEN_HEIGHT - rect.h;
        vy = -vy * FRICTION_AFTER_BOUNCE;
    }
    else{
        vy = vy + GRAVITY_CONSTANT;
    }
    rect.y = (int) ceil(1.0f * rect.y + vy); // update position
    SDL_FillRect(surface, &rect, COLOR_NICE_ORANGE);
    if(collision_with_floor(rect)) { return; }
    //std::cout << vy << "\t" << rect.y + rect.h << "\n";
}
*/

int main(int argc, char* argv[]){
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    Rectangle rectangle = Rectangle(100, 100, 100, 100, 0.0f, 4.0f, COLOR_NICE_ORANGE);
    //SDL_Rect rect = {100, 100, 100, 100};
    float vx = 4.0f;
    float vy = 4.0f;
    Circle circle = Circle(600.0f, 100.0f, 40.0f, vx, vy, COLOR_NICE_ORANGE);
    //SDL_FillRect(surface, &rect, COLOR_NICE_ORANGE);


    bool running = true;
    SDL_Event event;

    while(running){
        // check if user wants to exit the application
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) { running = false; }
        }

        //move_rectangle(surface, rect, vy);
        rectangle.MoveRectangleUnderGravity(surface, rectangle, vx, vy);
        circle.MoveCircleUniformly(surface, circle, vx, vy);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(SCREEN_REFRESH_TIME);
    }
    
    return 0;
}