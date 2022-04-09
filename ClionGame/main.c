#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>
#include <string.h>

typedef struct Sprite {
    Texture2D tex;
    Vector2 pos;
} Sprite;

typedef struct Shoot
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
} Shoot;

#define NUM_SHOOTS 50
static int shootRate;
static Shoot shoot[NUM_SHOOTS];


void mainGame(char p1Dir[]){
    const int WIDTH = 480;
    const int HEIGHT = 640;
    int diffy = 0;

    srand(time(NULL));

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");
    SetTargetFPS(60);

    // creating the players

    Sprite carP1;
    carP1.tex = LoadTexture(p1Dir);
    carP1.pos.x = WIDTH/2 - carP1.tex.width/2-50;
    carP1.pos.y = HEIGHT*3/5;
    int car_speed = 4;

    Sprite carP2;
    carP2.tex = LoadTexture("..\\res\\car.png");
    carP2.pos.x = WIDTH/2 - carP2.tex.width/2+50;
    carP2.pos.y = HEIGHT*3/5;
    int car2_speed = 4;

    int dx = 4;


    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rect.x = carP1.pos.x;
        shoot[i].rect.y = carP1.pos.y + HEIGHT / 4;
        shoot[i].rect.width = 5;
        shoot[i].rect.height = 10;
        shoot[i].speed.x = 0;
        shoot[i].speed.y = -10;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }

    // creating trees
    Texture2D ttrees = LoadTexture("..\\res\\trees.png");
    Rectangle srect[3];
    for(int i = 0; i < sizeof(srect)/sizeof(srect[0]); i++) {
        srect[i].width = srect[i].height = 48;
        srect[i].x = i*srect[i].width;
        srect[i].y = 0;
    }

    // randomizing positions of trees
    int trees_num = rand()%18 + 10;
    Vector2 trees_pos[trees_num];
    for(int i = 0; i < trees_num; i++) {
        if(i < (int)trees_num/2) {
            trees_pos[i].x = rand()%WIDTH/3 + 1;

            if(trees_pos[i].x + ttrees.width/3 > WIDTH/3) {
                trees_pos[i].x -= ttrees.width/3;
            }
        } else {
            trees_pos[i].x = rand()%WIDTH/3 + 2*WIDTH/3;

            if(trees_pos[i].x + ttrees.width/3 > WIDTH) {
                trees_pos[i].x -= ttrees.width/3;
            }
        }

        trees_pos[i].y = rand()%HEIGHT;
        if(trees_pos[i].y + ttrees.height > HEIGHT) {
            trees_pos[i].y -= ttrees.height;
        }
    }

    // creating items, randomizing positions of items
    Texture2D thole = LoadTexture("..\\res\\cars.png");
    Rectangle srect_hole[2];
    Vector2 hole_pos[2];
    float hole_speed[2] = { 0 };
    for(int i = 0; i < 2; i++) {
        srect_hole[i].width = 16;
        srect_hole[i].height = 16;
        srect_hole[i].x = i*srect_hole[i].width;
        srect_hole[i].y = 0;

        int randnum = rand()%3+1;
        if(randnum == 1) {
            hole_pos[i].x = WIDTH/3 + WIDTH/18 - thole.width/12;
        } else if(randnum == 2) {
            hole_pos[i].x = WIDTH/2 - thole.width/12;
        } else {
            hole_pos[i].x = WIDTH*2/3 - WIDTH/18 - thole.width/12;
        }

        hole_pos[i].y = rand()%HEIGHT;
        if(hole_pos[i].y + thole.width/12 > HEIGHT) {
            hole_pos[i].y -= thole.width/12;
        }

        hole_speed[i] = 2;
    }

    Texture2D tturbo = LoadTexture("..\\res\\3.png");
    Rectangle srect_turbo[2];
    Vector2 turbo_pos[2];
    float turbo_speed[2] = { 0 };
    for(int i = 0; i < 2; i++) {
        srect_turbo[i].width = 16;
        srect_turbo[i].height = 16;
        srect_turbo[i].x = i*srect_turbo[i].width;
        srect_turbo[i].y = 0;

        int randnum2 = rand()%3+1;
        if(randnum2 == 1) {
            turbo_pos[i].x = WIDTH/3 + WIDTH/18 - tturbo.width/12;
        } else if(randnum2 == 2) {
            turbo_pos[i].x = WIDTH/2 - tturbo.width/12;
        } else {
            turbo_pos[i].x = WIDTH*2/3 - WIDTH/18 - tturbo.width/12;
        }

        turbo_pos[i].y = rand()%HEIGHT;
        if(turbo_pos[i].y + tturbo.width/12 > HEIGHT) {
            turbo_pos[i].y -= tturbo.width/12;
        }

        turbo_speed[i] = 2;
    }

    Texture2D theart = LoadTexture("..\\res\\heart.png");
    Rectangle srect_heart[1];
    Vector2 heart_pos[1];
    float heart_speed[1] = { 0 };
    for(int i = 0; i < 1; i++) {
        srect_heart[i].width = 16;
        srect_heart[i].height = 16;
        srect_heart[i].x = i*srect_heart[i].width;
        srect_heart[i].y = 0;

        int randnum2 = rand()%3+1;
        if(randnum2 == 1) {
            heart_pos[i].x = WIDTH/3 + WIDTH/18 - theart.width/12;
        } else if(randnum2 == 2) {
            heart_pos[i].x = WIDTH/2 - theart.width/12;
        } else {
            heart_pos[i].x = WIDTH*2/3 - WIDTH/18 - theart.width/12;
        }

        heart_pos[i].y = rand()%HEIGHT;
        if(heart_pos[i].y + theart.width/12 > HEIGHT) {
            heart_pos[i].y -= theart.width/12;
        }

        heart_speed[i] = 2;
    }




    // dark screen
    Rectangle rmuteScreen = { 0, 0, WIDTH, HEIGHT };

    int lives = 3;
    int score = 0;
    double time = 0;
    double vulnerable_time, no_turbo_time, livesDowntimeTime = 0;
    bool gameOver = false;
    bool gameWon = false;
    bool vulnerable, no_turbo, livesDowntime = true;
    while(!WindowShouldClose()){
        if(!gameOver) {
            // process events
            if(IsKeyDown(KEY_LEFT)) {
                carP1.pos.x -= car_speed;
            } else if(IsKeyDown(KEY_RIGHT)) {
                carP1.pos.x += car_speed;
            } else if(IsKeyDown(KEY_DOWN)) {
                car_speed = dx/2;
            }
            if(IsKeyDown(KEY_A)) {
                carP2.pos.x -= car2_speed;
            } else if(IsKeyDown(KEY_D)) {
                carP2.pos.x += car2_speed;
            } else if(IsKeyDown(KEY_W)) {
                carP2.pos.y -= car2_speed;
            } else if(IsKeyDown(KEY_S)) {
                car2_speed = dx/2;
            }

            if (IsKeyDown(KEY_SPACE))
            { shootRate += 5;
                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!shoot[i].active && shootRate % 40 == 0)
                    {
                        shoot[i].rect.x = carP1.pos.x+12;
                        shoot[i].rect.y = carP1.pos.y;
                        shoot[i].active = true;
                        break;
                    }
                }
            }
            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    shoot[i].rect.y += shoot[i].speed.y;
                }
            }

            // update
            for(int i = 0; i < trees_num; i++) {
                trees_pos[i].y += car_speed;

                if(trees_pos[i].y > HEIGHT) {
                    trees_pos[i].y = -ttrees.height;
                }
            }

            for(int i = 0; i < sizeof(hole_pos)/sizeof(hole_pos[0]); i++) {
                hole_pos[i].y += car_speed;
                if(hole_pos[i].y > HEIGHT) {
                    hole_pos[i].y = -thole.height;
                    int randnum = rand()%3+1;
                    if(randnum == 1) {
                        hole_pos[i].x = WIDTH/3 + WIDTH/18 - thole.width/12;
                    } else if(randnum == 2) {
                        hole_pos[i].x = WIDTH/2 - thole.width/12;
                    } else {
                        hole_pos[i].x = WIDTH*2/3 - WIDTH/18 - thole.width/12;
                    }
                    hole_speed[i] = 2;
                }
                Rectangle rec1 = { carP1.pos.x, carP1.pos.y, carP1.tex.width-10, carP1.tex.height };
                Rectangle rec2 = { hole_pos[i].x, hole_pos[i].y, thole.width/6, thole.height };
                if(CheckCollisionRecs(rec1, rec2)) {
                    if(vulnerable) {
                        lives -= 1;
                        vulnerable = false;
                    }
                }
            }


            for(int i = 0; i < sizeof(turbo_pos)/sizeof(turbo_pos[0]); i++) {
                turbo_pos[i].y += car_speed;
                if(turbo_pos[i].y > HEIGHT) {
                    turbo_pos[i].y = -tturbo.height;
                    int randnum2 = rand()%3+1;
                    if(randnum2 == 1) {
                        turbo_pos[i].x = WIDTH/3 + WIDTH/18 - tturbo.width/12;
                    }
                    else if(randnum2 == 2) {
                        turbo_pos[i].x = WIDTH/2 - tturbo.width/12;
                    }
                    else {
                        turbo_pos[i].x = WIDTH*2/3 - WIDTH/18 - tturbo.width/12;
                    }
                    turbo_speed[i] = 2;
                }
                Rectangle rec1 = { carP1.pos.x, carP1.pos.y, carP1.tex.width, carP1.tex.height };
                Rectangle rec3 = { turbo_pos[i].x, turbo_pos[i].y, tturbo.width/6, tturbo.height };
                if(CheckCollisionRecs(rec1, rec3)) {
                    if(no_turbo) {
                        no_turbo = false;
                    }

                }
            }

            for(int i = 0; i < sizeof(heart_pos)/sizeof(heart_pos[0]); i++) {
                heart_pos[i].y += car_speed;
                if(heart_pos[i].y > HEIGHT) {
                    heart_pos[i].y = -theart.height;
                    int randnum2 = rand()%3+1;
                    if(randnum2 == 1) {
                        heart_pos[i].x = WIDTH/3 + WIDTH/18 - theart.width/12;
                    }
                    else if(randnum2 == 2) {
                        heart_pos[i].x = WIDTH/2 - theart.width/12;
                    }
                    else {
                        heart_pos[i].x = WIDTH*2/3 - WIDTH/18 - theart.width/12;
                    }
                    heart_speed[i] = 2;
                }
                Rectangle rec1 = { carP1.pos.x, carP1.pos.y, carP1.tex.width, carP1.tex.height };
                Rectangle rec4 = { heart_pos[i].x, heart_pos[i].y, theart.width/6, theart.height };
                if(CheckCollisionRecs(rec1, rec4)) {
                    if(livesDowntime) {
                        livesDowntime = false;
                    }
                }
            }




            if(!vulnerable) {
                vulnerable_time += GetFrameTime();
                if(vulnerable_time > 1) {
                    vulnerable = true;
                    vulnerable_time = 0;
                }
            }
            if(!no_turbo) {
                no_turbo_time += GetFrameTime();
                if(no_turbo_time > 1) {
                    no_turbo = true;
                    no_turbo_time = 0;
                }
            }
            if(!livesDowntime) {
                livesDowntimeTime += GetFrameTime();
                if(livesDowntimeTime > 1) {
                    if (lives == 7){
                        lives = 7;
                    }
                    else {
                        lives += 1;
                    }
                    livesDowntime = true;
                    livesDowntimeTime = 0;
                }
            }


            if(lives <= 0) {
                gameOver = true;
            }

            if(carP1.pos.x+10 < WIDTH/3 || carP1.pos.x + carP1.tex.width-10 > WIDTH*2/3) {
                car_speed=dx/2;
            }
            else {
                car_speed = dx;
            }

            time += GetFrameTime();
            if(time > 1) {
                score++;
                time = 0;
            }

            if(score > 999) {
                gameWon = true;
                gameOver = true;
            }
        }

        // draw
        BeginDrawing();
        ClearBackground(WHITE);

        // draw background
        DrawRectangle(0, 0, WIDTH/3, HEIGHT, GREEN);
        DrawRectangle(WIDTH*2/3, 0, WIDTH/3, HEIGHT, GREEN);
        DrawRectangle(WIDTH/3, 0, WIDTH/3, HEIGHT, GRAY);
        DrawRectangle(WIDTH/3 + WIDTH/9 - 1, 0, 2, HEIGHT, BLACK);
        DrawRectangle(WIDTH/3 + WIDTH*2/9 - 1, 0, 2, HEIGHT, BLACK);

        if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP1.tex, carP1.pos.x, carP1.pos.y, col);
            car_speed = dx/2;
        } else {
            DrawTexture(carP1.tex, carP1.pos.x, carP1.pos.y, WHITE);
        }
        if(!no_turbo) {
            car_speed = dx*2;
        }

        if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, col);
        } else {
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, WHITE);
        }

        for(int i = 0; i < 2; i++) {
            DrawTextureRec(thole, srect_hole[i], hole_pos[i], WHITE);
        }
        for(int i = 0; i < 2; i++) {
            DrawTextureRec(tturbo, srect_turbo[i], turbo_pos[i], WHITE);
        }
        for(int i = 0; i < 1; i++) {
            DrawTextureRec(theart, srect_heart[i], heart_pos[i], WHITE);
        }

        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (shoot[i].active)
                DrawRectangleRec(shoot[i].rect, shoot[i].color);
        }

        for(int i = 0; i < trees_num; i++) {
            if(i%2 == 0) {
                DrawTextureRec(ttrees, srect[0], trees_pos[i], WHITE);
            } else if(i%3 == 0) {
                DrawTextureRec(ttrees, srect[1], trees_pos[i], WHITE);
            } else {
                DrawTextureRec(ttrees, srect[2], trees_pos[i], WHITE);
            }
        }

        const char *str2 = "\n";
        char scoring[12] = { " " };
        sprintf(scoring, "%d", score);
        DrawText(scoring, 10, 0, 60, WHITE);

        sprintf(scoring, "%d", lives);
        DrawText(scoring, WIDTH-50, 0, 60, WHITE);

        const char* filename = "out.txt";

        FILE* output_file = fopen(filename, "w+");
        if (!output_file) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        fwrite(scoring, 1, strlen(scoring), output_file);
        fwrite(str2, 1, strlen(str2), output_file);
        fwrite(scoring, 1, strlen(scoring), output_file);



        fclose(output_file);

        if(gameOver) {
            Color color = { 0, 0, 0, 180 };
            DrawRectangle(rmuteScreen.x, rmuteScreen.y, rmuteScreen.width, rmuteScreen.height, color);
            if(gameWon) {
                DrawText("You Won!", WIDTH/11, HEIGHT/3, 90, WHITE);
            } else {
                DrawText("Game Over!", WIDTH/11, HEIGHT/3, 70, WHITE);
            }
        }

        EndDrawing();
    }

    UnloadTexture(thole);
    UnloadTexture(ttrees);
    UnloadTexture(theart);
    UnloadTexture(carP1.tex);
    CloseWindow();
}

selectCar(){
    const int WIDTH = 840;
    const int HEIGHT = 480;

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");

    SetTargetFPS(60);
    Sprite car1, car2, car3, car4, selectSqr;
    car1.tex = LoadTexture("..\\res\\car1BIG.png");
    car1.pos.x = WIDTH*1/6;
    car1.pos.y = HEIGHT/2 - car1.tex.height/2;

    car2.tex = LoadTexture("..\\res\\car2BIG.png");
    car2.pos.x = WIDTH*2/6;
    car2.pos.y = HEIGHT/2 - car2.tex.height/2;

    car3.tex = LoadTexture("..\\res\\car3BIG.png");
    car3.pos.x = WIDTH*3/6;
    car3.pos.y = HEIGHT/2 - car3.tex.height/2;

    car4.tex = LoadTexture("..\\res\\car4BIG.png");
    car4.pos.x = WIDTH*4/6;
    car4.pos.y = HEIGHT/2 - car4.tex.height/2;

    selectSqr.tex = LoadTexture("..\\res\\selecting.png");
    selectSqr.pos.x = WIDTH*1/6;
    selectSqr.pos.y = HEIGHT/2 - selectSqr.tex.height/2;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (IsKeyPressed(KEY_LEFT) || IsGestureDetected(GESTURE_TAP))
        {
            if(selectSqr.pos.x == WIDTH*1/6){
                selectSqr.pos.x = WIDTH*1/6;
            }
            else {
                selectSqr.pos.x -= WIDTH * 1 / 6;
            }
        }

        if (IsKeyPressed(KEY_RIGHT) || IsGestureDetected(GESTURE_TAP))
        {

            if(selectSqr.pos.x == WIDTH*4/6){
                selectSqr.pos.x = WIDTH*4/6;
            }
            else {
                selectSqr.pos.x += WIDTH*1/6;
            }
        }

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            if(selectSqr.pos.x == WIDTH*1/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                mainGame("..\\res\\car1.png");
            }
            if(selectSqr.pos.x == WIDTH*2/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                mainGame("..\\res\\car2.png");
            }
            if(selectSqr.pos.x == WIDTH*3/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                mainGame("..\\res\\car3.png");
            }
            if(selectSqr.pos.x == WIDTH*4/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                mainGame("..\\res\\car4.png");
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);


        DrawRectangle(0, 0, WIDTH, HEIGHT, DARKPURPLE);
        DrawText("ELIJA UN AUTO", 20, 20, 40, LIGHTGRAY);
        //DrawText("BRRRRUUUUUUUUUHHHH", 290, 220, 20, BLUE);

        DrawTexture(car1.tex, car1.pos.x, car1.pos.y, WHITE);
        DrawTexture(car2.tex, car2.pos.x, car2.pos.y, WHITE);
        DrawTexture(car3.tex, car3.pos.x, car3.pos.y, WHITE);
        DrawTexture(car4.tex, car4.pos.x, car4.pos.y, WHITE);

        DrawTexture(selectSqr.tex, selectSqr.pos.x, selectSqr.pos.y, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadTexture(car1.tex);
    UnloadTexture(car2.tex);
    UnloadTexture(car3.tex);
    UnloadTexture(car4.tex);
    UnloadTexture(selectSqr.tex);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

int main(void) {

    //mainGame();
    selectCar();
    return 0;
}