#include <SDL.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
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
        circle.MoveCircleUniformly(surface);
        //circle.MoveCircleUnderGravity(surface, circle, vx, vy);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(SCREEN_REFRESH_TIME);
    }
}

void Pong(void){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window * window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface * surface = SDL_GetWindowSurface(window);
    
    SDL_Renderer * renderer = SDL_CreateSoftwareRenderer(surface);
    TTF_Font * font = TTF_OpenFont("C:\\Users\\matte\\C++_libraries\\fonts\\pixelletters-font\\Pixellettersfull-BnJ5.ttf", 24);
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    std::string textScore = "SCORE : ";
    int score = 0;
    std::stringstream oss;
    oss << textScore << score; // Combine text and number
    SDL_Surface * textSurface = TTF_RenderText_Solid(font, (oss.str()).c_str(), textColor);
    SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    int racket_height = 25; float ball_radius = 20.0f; float ball_vx = 3.0f; float ball_vy = 3.0f;
    Rectangle racket2 = Rectangle(350, SCREEN_HEIGHT-55, 100, racket_height, 0.0f, 0.0f, COLOR_NICE_ORANGE);
    Circle ball = Circle(SCREEN_WIDTH/2.0, 1.0f+ball_radius, ball_radius, ball_vx, ball_vy, COLOR_WHITE);

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

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);
        // Render text
        SDL_Rect textRect = {600, 20, 100, 40}; // Position and size of the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        racket2.FillRectangle(surface, racket2.color);
        ball.CheckCollisionWithRectangle(surface, ball, racket2);
        ball.MoveCircleUniformly(surface);

        if(ball.CheckCollisionWithTopEdge()){ 
            score++;
            ball.vx += 1.0;
            oss.str(""); oss << textScore << score;
            SDL_DestroyTexture(textTexture);
            textSurface = TTF_RenderText_Solid(font, (oss.str()).c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
        else if(ball.CheckCollisionWithBottomEdge()){
            score--;
            oss.str(""); oss << textScore << score;
            SDL_DestroyTexture(textTexture);
            textSurface = TTF_RenderText_Solid(font, (oss.str()).c_str(), textColor);
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }         

        // Render updated text
        //SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        // Present the renderer
        //SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(SCREEN_REFRESH_TIME); 
    }

    // Cleanup
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[]){
    
    Pong();
    //CircleCollidingWithCube();
    
    return 0;
}