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
bool Circle::CheckCollisionWithRightEdge(void){
    if(this->x0 + this->r >= 1.0f * SCREEN_WIDTH){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithLeftEdge(void){
    if(this->x0 - this->r <= 0.0f){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithBottomEdge(void){
    if(this->y0 + this->r >= 1.0f * SCREEN_HEIGHT){ return true; }
    else { return false; }
}
bool Circle::CheckCollisionWithTopEdge(void){
    if(this->y0 - this->r <= 0.0f){ return true; }
    else { return false; }
}
void Circle::CheckCollisionWithRectangle(SDL_Surface * surface, Circle &circle, Rectangle rectangle){
    // relevant coordinates of the rectangle
    float x_left = (float) rectangle.rect.x;
    float x_right = (float) (rectangle.rect.x + rectangle.rect.w);
    float y_top = (float) rectangle.rect.y;
    float y_bottom = (float) rectangle.rect.y + rectangle.rect.h;
    // simple quick condition which guarantees no collision
    if(x_left > circle.x0 + circle.r || x_right < circle.x0 - circle.r || y_top > circle.y0 + circle.r || y_bottom < circle.y0 - circle.r){
        return;
    }
    else{
        float r_squared = circle.r * circle.r;
        // check left-edge of the rectangle
        if(x_left <= circle.x0 + circle.r){
            for(float y = y_top; y <= y_bottom; y += 1.0f){
                if((x_left-circle.x0)*(x_left-circle.x0) + (y-circle.y0)*(y-circle.y0) <= r_squared){
                    circle.EraseCircle(surface);
                    circle.x0 = x_left - circle.r;
                    circle.vx = - circle.vx;
                    circle.FillCircle(surface, circle.color);
                    return;
                }
            }
        }
        // check right-edge of the rectangle
        if(x_right >= circle.x0 - circle.r){
            for(float y = y_top; y <= y_bottom; y += 1.0f){
                if((x_right-circle.x0)*(x_right-circle.x0) + (y-circle.y0)*(y-circle.y0) <= r_squared){
                    circle.EraseCircle(surface);
                    circle.x0 = x_right + circle.r;
                    circle.vx = - circle.vx;
                    circle.FillCircle(surface, circle.color);
                    return;
                }
            }
        }
        // check top-edge of the rectangle
        if(y_top <= circle.y0 + circle.r){
            for(float x = x_left; x <= x_right; x += 1.0f){
                if((x-x0)*(x-x0) + (y_top-y0)*(y_top-y0) <= r_squared){
                    circle.EraseCircle(surface);
                    circle.y0 = y_top - circle.r;
                    circle.vy = - circle.vy;
                    circle.FillCircle(surface, circle.color);
                    return;
                }
            }
        }
        // check bottom-edge of the rectangle
        if(y_bottom >= circle.y0 - circle.r){
            for(float x = x_left; x <= x_right; x += 1.0f){
                if((x-x0)*(x-x0) + (y_bottom-y0)*(y_bottom-y0) <= r_squared){
                    circle.EraseCircle(surface);
                    circle.y0 = y_bottom + circle.r;
                    circle.vy = - circle.vy;
                    circle.FillCircle(surface, circle.color);
                    return;
                }
            }
        }
    }
    // in all the other cases ...
    return;
}


void Circle::MoveCircleUniformly(SDL_Surface * surface, Circle &circle, float &vx, float & vy){
    circle.EraseCircle(surface);
    if(circle.CheckCollisionWithBottomEdge()){
        circle.vy = - circle.vy;
    }
    else if(circle.CheckCollisionWithTopEdge()){
        circle.vy = -circle.vy;
    }
    if(circle.CheckCollisionWithLeftEdge()){
        circle.vx = - circle.vx;
    }
    else if(circle.CheckCollisionWithRightEdge()){
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
    if(circle.CheckCollisionWithBottomEdge()){ 
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
