#pragma once

#include "raylib.h"
#include <stdio.h>

struct Ball{
    float x,y;
    float speedX,speedY;
    float radius;

    void Draw(){
        DrawCircle((int)x, (int)y,radius,RED);
    }
};


struct Paddle{
    float x,y;
    float speed;
    float height,width;

    Rectangle getRect(){
        return Rectangle{
            x-width/2, y-height/2,100,10
        };
    }

    void Draw(){
        DrawRectangleRec(getRect(),WHITE);
    }

};


struct Brick{
    float x,y;
    float height = 30;
    float width = 100;
    float health = 1;
    Color brickColor = YELLOW;
    bool isAlive = true;

    Rectangle getRect(){
        return Rectangle{
            x-width/2,y-height/2,width,height
        };
    }

    void Draw(){
        DrawRectangleRec(getRect(),brickColor);
    }

    bool checkCol(Ball &ball){
        if(isAlive) {
            if(CheckCollisionCircleRec(Vector2{ball.x,ball.y} , ball.radius , getRect())){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }

    void setBrickLife(){
        brickColor = BLACK;
        isAlive = false;
    }
};
