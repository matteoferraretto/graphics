#include <Circle.h>
#include <iostream>

Circle::Circle(float x0, float y0, float r)
{
    this->x0 = x0; this->y0 = y0; this->r = r; vx = 0.0; vy = 0.0; color = COLOR_WHITE;
}

Circle::Circle(float x0, float y0, float r, float vx, float vy, int color)
{
    this->x0 = x0; this->y0 = y0; this->r = r; this->vx = vx; this->vy = vy; this->color = color;
}

Circle::~Circle()
{
}

void Circle::FillCircle(SDL_Surface * surface, int color){
    float r_squared = r*r;
    for(float x = x0-r; x <= x0+r; x+=1.0f){
        for(float y = y0-r; y <= y0+r; y+=1.0f){
            if((x-x0)*(x-x0) + (y-y0)*(y-y0) <= r_squared){
                SDL_Rect pixel = {(int) x, (int) y, 1, 1}; // initialize single pixel in (x,y)
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
};
void Circle::EraseCircle(SDL_Surface * surface){
    float r_squared = r*r;
    for(float x = x0-r; x <= x0+r; x+=1.0f){
        for(float y = y0-r; y <= y0+r; y+=1.0f){
            if((x-x0)*(x-x0) + (y-y0)*(y-y0) <= r_squared){
                SDL_Rect pixel = {(int) x, (int) y, 1, 1}; // initialize single pixel in (x,y)
                SDL_FillRect(surface, &pixel, COLOR_BLACK);
            }
        }
    }
};
bool Circle::CheckCollisionWithRightEdge(Circle circle){
    if(circle.x0 + circle.r >= 1.0f * SCREEN_WIDTH){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithLeftEdge(Circle circle){
    if(circle.x0 - circle.r <= 0.0f){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithBottomEdge(Circle circle){
    if(circle.y0 + circle.r >= 1.0f * SCREEN_HEIGHT){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithTopEdge(Circle circle){
    if(circle.y0 - circle.r <= 0.0f){ return true; }
    else { return false; }
}

void Circle::MoveCircleUniformly(SDL_Surface * surface, Circle &circle, float &vx, float & vy){
    circle.EraseCircle(surface);
    if(CheckCollisionWithBottomEdge(circle)){
        circle.vy = - circle.vy;
    }
    else if(CheckCollisionWithTopEdge(circle)){
        circle.vy = -circle.vy;
    }
    if(CheckCollisionWithLeftEdge(circle)){
        circle.vx = - circle.vx;
    }
    else if(CheckCollisionWithRightEdge(circle)){
        circle.vx = - circle.vx;
    }
    circle.x0 = circle.x0 + circle.vx;
    circle.y0 = circle.y0 + circle.vy;
    circle.FillCircle(surface, COLOR_WHITE);
}

void Circle::MoveCircleUnderGravity(SDL_Surface * surface, Circle &circle, float &vx, float & vy){
    circle.EraseCircle(surface);
    // more efficient erasing
    //SDL_Rect rect = {(int) floor(circle.x0-circle.r), (int) floor(circle.y0-circle.r), (int) ceil(2*circle.r)+2, (int) ceil(2*circle.r)+2};
    //SDL_FillRect(surface, &rect, COLOR_BLACK);
    // if collision, modify position 
    if(CheckCollisionWithBottomEdge(circle)){ 
        circle.y0 = 1.0f*SCREEN_HEIGHT - circle.r;
        circle.vy = -circle.vy * FRICTION_AFTER_BOUNCE;
    }
    else{
        circle.vy = circle.vy + GRAVITY_CONSTANT;
    }
    circle.y0 = circle.y0 + circle.vy; // update position
    circle.FillCircle(surface, COLOR_WHITE);
    if(circle.y0 + circle.r >= 1.0f*SCREEN_HEIGHT) { return; }
}
