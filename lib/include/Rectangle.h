#pragma once;
#include <SDL.h>
#include "Constants.h"

class Rectangle
{
private:
    /* data */
public:
    SDL_Rect rect;
    float vx; float vy;
    int color;

    // constructors
    Rectangle(int x, int y, int width, int heigth);
    Rectangle(int x, int y, int width, int heigth, float vx, float vy, int color);

    // methods
    bool CheckCollisionWithLeftEdge(Rectangle r);
    bool CheckCollisionWithRightEdge(Rectangle r);
    bool CheckCollisionWithBottomEdge(Rectangle r);
    bool CheckCollisionWithTopEdge(Rectangle r);
    void FillRectangle(SDL_Surface * surface, int color);
    void EraseRectangle(SDL_Surface * surface);
    void MoveRectangleUniformly(SDL_Surface * surface, Rectangle & r, float & vx, float & vy);
    void MoveRectangleUnderGravity(SDL_Surface * surface, Rectangle & r, float & vx, float & vy);

    ~Rectangle();
};
