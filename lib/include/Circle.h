#pragma once;
#include <SDL.h>
#include "Constants.h"
#include "Rectangle.h"

// Class for circle
class Circle
{
private:
    /* data */
public:
    // data
    float x0; float y0; float r;
    float vx; float vy;
    int color;

    // constructors
    Circle(float x0, float y0, float r);
    Circle(float x0, float y0, float r, float vx, float vy, int color);

    // methods
    bool CheckCollisionWithLeftEdge(Circle circle);
    bool CheckCollisionWithRightEdge(Circle circle);
    bool CheckCollisionWithBottomEdge(Circle circle);
    bool CheckCollisionWithTopEdge(Circle circle);
    void CheckCollisionWithRectangle(SDL_Surface * surface, Circle &circle, Rectangle rectangle);
    void FillCircle(SDL_Surface * surface, int color);
    void EraseCircle(SDL_Surface * surface);
    void MoveCircleUniformly(SDL_Surface * surface, Circle & circle, float & vx, float & vy);
    void MoveCircleUnderGravity(SDL_Surface * surface, Circle & circle, float & vx, float & vy);
    ~Circle();
};