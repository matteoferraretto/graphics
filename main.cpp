#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include "Circle.h"
#include "Rectangle.h"

void CircleCollidingWithCube(void){
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
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                std::cout << "hello world.\n";
                circle.vx = -circle.vx; circle.vy = -circle.vy;
                break;
            }
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
}

void Pong(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface * surface = SDL_GetWindowSurface(window);

    int racket_height = 25; float ball_radius = 20.0f; float ball_vx = 3.0f; float ball_vy = 3.0f;

    Rectangle racket2 = Rectangle(350, SCREEN_HEIGHT-55, 100, racket_height, 0.0f, 0.0f, COLOR_NICE_ORANGE);
    Circle ball = Circle(SCREEN_WIDTH/2.0, 1.0f+ball_radius, ball_radius, ball_vx, ball_vy, COLOR_WHITE);

    int score = 0;
    bool running = true;
    SDL_Event event;

    while(running){
        // check if user wants to exit the application
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) { running = false; }
            else if(event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    racket2.EraseRectangle(surface);
                    racket2.rect.x -= 50;
                    break;

                case SDLK_RIGHT:
                    racket2.EraseRectangle(surface);
                    racket2.rect.x += 50;
                    break; 
                
                default:
                    break;
                }
            }
        }

        racket2.FillRectangle(surface, racket2.color);

        ball.CheckCollisionWithRectangle(surface, ball, racket2);
        ball.MoveCircleUniformly(surface, ball, ball.vx, ball.vy);
        if(ball.CheckCollisionWithTopEdge()){ 
            score++;
            ball.vx += 0.25;
            std::cout << "score = " << score << "\n";
        }
        else if(ball.CheckCollisionWithBottomEdge()){
            score--;
            std::cout << "score = " << score << "\n";
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(SCREEN_REFRESH_TIME);
    }
}


int main(int argc, char* argv[]){
    
    Pong();
    //CircleCollidingWithCube();
    
    return 0;
}