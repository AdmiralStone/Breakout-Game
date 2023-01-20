#include <iostream>
#include "raylib.h"
#include "gameObjects.h"
#include <bits/stdc++.h>

using namespace std;

bool IsPaused = false;
bool IsGameOver = false;
bool WinCondition = false;
int brickCount = 0;

void createWall(vector<Brick> &wall){
    int y = 50;
    for(int row = 0;row<4;row++){  
        int x = 70;
        Brick newBrick;  
        for(int i=0;i<7;i++){
            
            newBrick.x = x;
            newBrick.y = y;

            wall.push_back(newBrick);

            x += newBrick.width + 10;

            brickCount++;
        }
        y+=newBrick.height + 10;
    }


}

int main(){

    // Set FPS CAP
    SetWindowState(FLAG_VSYNC_HINT);
    
    // Initialize main window(w,h,title)
    InitWindow(800,600,"Breakout");

    
    
    // Create the paddle;
    Paddle paddle;
    paddle.x = GetScreenWidth()/2.0f;
    paddle.y = GetScreenHeight()-40;
    paddle.width = 100;
    paddle.height = 20;
    paddle.speed = 500;



    // Create The Ball Object
    Ball ball;
    ball.x = GetScreenWidth()/2.0f;
    ball.y = paddle.y-paddle.height;
    ball.radius = 5;
    ball.speedX = 200;
    ball.speedY = -300;

    // Create Wall
    vector <Brick> wall;
    createWall(wall);


    while(!WindowShouldClose()){
        if(brickCount == 0){
            WinCondition = true;
        }
        if(!IsGameOver && !WinCondition){
            if(IsKeyPressed(KEY_P)){
                IsPaused = !IsPaused;
            }

            if(!IsPaused){
                if(ball.y >= GetScreenHeight()){
                    IsGameOver = true;
                }


                // Ball Movement Logic
                ball.x+=ball.speedX* GetFrameTime();
                ball.y+=ball.speedY* GetFrameTime();


                // DEBUGING PURPOSE ONLY
                if(ball.x > GetScreenWidth() || ball.x <= 0.0){
                    ball.speedX*=-1.0f;
                }

                if(ball.y > GetScreenHeight() || ball.y <= 0.0){
                    ball.speedY *= -1.0f;
                }

                // Paddle Movement Logic
                if(IsKeyDown(KEY_LEFT)){
                    if(paddle.x > 55){
                        paddle.x -= paddle.speed*GetFrameTime();
                    }
                }
                if(IsKeyDown(KEY_RIGHT)){
                    if(paddle.x < GetScreenWidth()-55){
                        paddle.x +=paddle.speed*GetFrameTime();
                    }
                }

                // Collission Detection
                if(CheckCollisionCircleRec(Vector2{ball.x,ball.y} , ball.radius,paddle.getRect())){
                    ball.speedX = (ball.x - paddle.x) / (paddle.width/2) * abs(ball.speedY);
                    ball.speedY *=-1.0f;
                }
        
            }
        }
            // Start Rendering Objects
            BeginDrawing();
                
                // Display Black Background
                ClearBackground(BLACK);

                for(auto it = wall.begin();it!=wall.end();it++){
                    if(it->checkCol(ball)){
                        ball.speedX = (ball.x - it->x) / (it->width/2) * abs(ball.speedY);
                        ball.speedY *=-1.0f;
                        it->setBrickLife();
                        brickCount--;
                    };
                    it->Draw();
                }

                // Draw the Ball
                ball.Draw();

                // Draw the paddle
                paddle.Draw();

                // Show FPS
                DrawFPS(10,10);

                if(IsPaused){
                    DrawText("PAUSED" ,300,300,40,YELLOW);
                }

                if(IsGameOver){
                    IsPaused = false;
                    DrawText("GAME OVER" ,300,300,40,RED);
                }

                if(WinCondition){
                    IsPaused = false;
                    DrawText("PLAYER WINS" ,300,300,40,GREEN);
                }

            EndDrawing();
    }

    // Close Window
    CloseWindow();
    return 0;
}