#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int heigth)
{
    this->rect.x = x; this->rect.y = y; this->rect.w = width; this->rect.h = heigth;
}

Rectangle::Rectangle(int x, int y, int width, int heigth, float vx, float vy, int color)
{
    this->rect.x = x; this->rect.y = y; this->rect.w = width; this->rect.h = heigth; this->vx = vx; this->vy = vy; this->color = color;
}

Rectangle::~Rectangle()
{
}

void Rectangle::FillRectangle(SDL_Surface * surface, int color){
    SDL_FillRect(surface, &rect, color);
};
void Rectangle::EraseRectangle(SDL_Surface * surface){
    SDL_FillRect(surface, &rect, COLOR_BLACK);
};
bool Rectangle::CheckCollisionWithRightEdge(Rectangle r){
    if(r.rect.x + r.rect.w >= 1.0f * SCREEN_WIDTH){ return true; }
    else { return false; }
}
bool Rectangle::CheckCollisionWithLeftEdge(Rectangle r){
    if(r.rect.x <= 0.0f){ return true; }
    else { return false; }
}
bool Rectangle::CheckCollisionWithBottomEdge(Rectangle r){
    if(r.rect.y + r.rect.h >= 1.0f * SCREEN_HEIGHT){ return true; }
    else { return false; }
}
bool Rectangle::CheckCollisionWithTopEdge(Rectangle r){
    if(r.rect.y <= 0.0f){ return true; }
    else { return false; }
}

void Rectangle::MoveRectangleUniformly(SDL_Surface * surface, Rectangle &r, float &vx, float & vy){
    r.EraseRectangle(surface);
    if(CheckCollisionWithBottomEdge(r)){
        r.vy = - r.vy;
    }
    else if(CheckCollisionWithTopEdge(r)){
        r.vy = -r.vy;
    }
    if(CheckCollisionWithLeftEdge(r)){
        r.vx = - r.vx;
    }
    else if(CheckCollisionWithRightEdge(r)){
        r.vx = - r.vx;
    }
    r.rect.x = r.rect.x + r.vx;
    r.rect.y = r.rect.y + r.vy;
    r.FillRectangle(surface, r.color);
}

void Rectangle::MoveRectangleUnderGravity(SDL_Surface * surface, Rectangle &r, float &vx, float & vy){
    r.EraseRectangle(surface);
    int current_y = rect.y; // save current position
    // if collision, modify position 
    if(CheckCollisionWithBottomEdge(r)){ 
        // std::cout << "i'm here.\n";
        r.rect.y = SCREEN_HEIGHT - r.rect.h;
        r.vy = -r.vy * FRICTION_AFTER_BOUNCE;
    }
    else{
        r.vy = r.vy + GRAVITY_CONSTANT;
    }
    r.rect.y = (int) ceil(1.0f * r.rect.y + r.vy); // update position
    FillRectangle(surface, color);
    if(CheckCollisionWithBottomEdge(r)) { return; }
}