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

int main(void) {
    const int WIDTH = 480;
    const int HEIGHT = 640;

    srand(time(NULL));

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");
    SetTargetFPS(60);

    // creating the player
    Sprite car;
    car.tex = LoadTexture("C:\\Users\\kenda\\Desktop\\TEC\\Lenguajes\\Lenguajes\\Poll_Position\\Tarea3_Pole_Position\\ClionGame\\res\\car.png");
    car.pos.x = WIDTH/2 - car.tex.width/2;
    car.pos.y = HEIGHT*3/5;
    int car_speed = 4;

    Sprite car2;
    car2.tex = LoadTexture("C:\\Users\\kenda\\Desktop\\TEC\\Lenguajes\\Lenguajes\\Poll_Position\\Tarea3_Pole_Position\\ClionGame\\res\\car.png");
    car2.pos.x = WIDTH/2 - car2.tex.width/2;
    car2.pos.y = HEIGHT*3/5;
    int car2_speed = 4;

    int dx = 4;


    //
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rect.x = car.pos.x;
        shoot[i].rect.y = car.pos.y + HEIGHT / 4;
        shoot[i].rect.width = 5;
        shoot[i].rect.height = 10;
        shoot[i].speed.x = 0;
        shoot[i].speed.y = -10;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }

    // creating trees
    Texture2D ttrees = LoadTexture("C:\\Users\\kenda\\Desktop\\TEC\\Lenguajes\\Lenguajes\\Poll_Position\\Tarea3_Pole_Position\\ClionGame\\res\\trees.png");
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

    // creating cars, randomizing positions of cars
    Texture2D tcars = LoadTexture("C:\\Users\\kenda\\Desktop\\TEC\\Lenguajes\\Lenguajes\\Poll_Position\\Tarea3_Pole_Position\\ClionGame\\res\\cars.png");
    Rectangle srect_cars[4];
    Vector2 cars_pos[4];
    float cars_speed[4] = { 0 };
    for(int i = 0; i < 4; i++) {
        srect_cars[i].width = 16;
        srect_cars[i].height = 16;
        srect_cars[i].x = i*srect_cars[i].width;
        srect_cars[i].y = 0;

        int randnum = rand()%3+1;
        if(randnum == 1) {
            cars_pos[i].x = WIDTH/3 + WIDTH/18 - tcars.width/12;
        } else if(randnum == 2) {
            cars_pos[i].x = WIDTH/2 - tcars.width/12;
        } else {
            cars_pos[i].x = WIDTH*2/3 - WIDTH/18 - tcars.width/12;
        }

        cars_pos[i].y = rand()%HEIGHT;
        if(cars_pos[i].y + tcars.width/12 > HEIGHT) {
            cars_pos[i].y -= tcars.width/12;
        }

        cars_speed[i] = 2;
    }

    Texture2D tcars2 = LoadTexture("C:\\Users\\kenda\\Desktop\\TEC\\Lenguajes\\Lenguajes\\Poll_Position\\Tarea3_Pole_Position\\ClionGame\\res\\3.png");
    Rectangle srect_cars2[2];
    Vector2 cars_pos2[2];
    float cars_speed2[2] = { 0 };
    for(int i = 0; i < 2; i++) {
        srect_cars2[i].width = 16;
        srect_cars2[i].height = 16;
        srect_cars2[i].x = i*srect_cars2[i].width;
        srect_cars2[i].y = 0;

        int randnum2 = rand()%3+1;
        if(randnum2 == 1) {
            cars_pos2[i].x = WIDTH/3 + WIDTH/18 - tcars2.width/12;
        } else if(randnum2 == 2) {
            cars_pos2[i].x = WIDTH/2 - tcars2.width/12;
        } else {
            cars_pos2[i].x = WIDTH*2/3 - WIDTH/18 - tcars2.width/12;
        }

        cars_pos2[i].y = rand()%HEIGHT;
        if(cars_pos2[i].y + tcars2.width/12 > HEIGHT) {
            cars_pos2[i].y -= tcars2.width/12;
        }

        cars_speed2[i] = 2;
    }




    // dark screen
    Rectangle rmuteScreen = { 0, 0, WIDTH, HEIGHT };

    int lives = 3;
    int score = 0;
    double time = 0;
    double vulnerable_time, no_turbo_time = 0;
    bool gameOver = false;
    bool gameWon = false;
    bool vulnerable, no_turbo = true;
    while(!WindowShouldClose()){
        if(!gameOver) {
            // process events
            if(IsKeyDown(KEY_LEFT)) {
                car.pos.x -= car_speed;
            } else if(IsKeyDown(KEY_RIGHT)) {
                car.pos.x += car_speed;
            } else if(IsKeyDown(KEY_DOWN)) {
                car_speed = dx/2;
            }
            if(IsKeyDown(KEY_A)) {
                car2.pos.x -= car2_speed;
            } else if(IsKeyDown(KEY_D)) {
                car2.pos.x += car2_speed;
            } else if(IsKeyDown(KEY_W)) {
                car2.pos.y -= car2_speed;
            } else if(IsKeyDown(KEY_S)) {
                car2_speed = dx/2;
            }

            if (IsKeyDown(KEY_SPACE))
            { shootRate += 5;
                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!shoot[i].active && shootRate % 40 == 0)
                    {
                        shoot[i].rect.x = car.pos.x;
                        shoot[i].rect.y = car.pos.y - car.tex.height-1;
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

            for(int i = 0; i < sizeof(cars_pos)/sizeof(cars_pos[0]); i++) {
                cars_pos[i].y += car_speed;
                if(cars_pos[i].y > HEIGHT) {
                    cars_pos[i].y = -tcars.height;
                    int randnum = rand()%3+1;
                    if(randnum == 1) {
                        cars_pos[i].x = WIDTH/3 + WIDTH/18 - tcars.width/12;
                    } else if(randnum == 2) {
                        cars_pos[i].x = WIDTH/2 - tcars.width/12;
                    } else {
                        cars_pos[i].x = WIDTH*2/3 - WIDTH/18 - tcars.width/12;
                    }
                    cars_speed[i] = 2;
                }
                Rectangle rec1 = { car.pos.x, car.pos.y, car.tex.width, car.tex.height };
                Rectangle rec2 = { cars_pos[i].x, cars_pos[i].y, tcars.width/6, tcars.height };
                if(CheckCollisionRecs(rec1, rec2)) {
                    if(vulnerable) {
                        lives -= 1;
                        vulnerable = false;
                    }

                }
            }


            for(int i = 0; i < sizeof(cars_pos2)/sizeof(cars_pos2[0]); i++) {
                cars_pos2[i].y += car_speed;
                if(cars_pos2[i].y > HEIGHT) {
                    cars_pos2[i].y = -tcars2.height;
                    int randnum2 = rand()%3+1;
                    if(randnum2 == 1) {
                        cars_pos2[i].x = WIDTH/3 + WIDTH/18 - tcars2.width/12;
                    }
                    else if(randnum2 == 2) {
                        cars_pos2[i].x = WIDTH/2 - tcars2.width/12;
                    }
                    else {
                        cars_pos2[i].x = WIDTH*2/3 - WIDTH/18 - tcars2.width/12;
                    }
                    cars_speed2[i] = 2;
                }
                Rectangle rec1 = { car.pos.x, car.pos.y, car.tex.width, car.tex.height };
                Rectangle rec3 = { cars_pos2[i].x, cars_pos2[i].y, tcars2.width/6, tcars2.height };
                if(CheckCollisionRecs(rec1, rec3)) {
                    if(no_turbo) {
                        no_turbo = false;
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


            if(lives <= 0) {
                gameOver = true;
            }

            if(car.pos.x < WIDTH/3 || car.pos.x + car.tex.width > WIDTH*2/3) {
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
            DrawTexture(car.tex, car.pos.x, car.pos.y, col);
            car_speed = dx/2;
        } else {
            DrawTexture(car.tex, car.pos.x, car.pos.y, WHITE);
        }
        if(!no_turbo) {

            car_speed = dx*2;
        }
        if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(car2.tex, car2.pos.x, car2.pos.y, col);
        } else {
            DrawTexture(car2.tex, car2.pos.x, car2.pos.y, WHITE);
        }

        for(int i = 0; i < 4; i++) {
            DrawTextureRec(tcars, srect_cars[i], cars_pos[i], WHITE);
        }
        for(int i = 0; i < 2; i++) {
            DrawTextureRec(tcars2, srect_cars2[i], cars_pos2[i], WHITE);
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

    UnloadTexture(tcars);
    UnloadTexture(ttrees);
    UnloadTexture(car.tex);
    CloseWindow();

    return 0;
}