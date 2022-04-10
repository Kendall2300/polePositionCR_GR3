#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <raylib.h>
#include <string.h>
#include <winsock2.h>
#define LIMITE 50

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

//--PLAYER 1-----------------------------------------------------------------------------------------------------------
void mainGameP1(char p1Dir[]){
    const int WIDTH = 480;
    const int HEIGHT = 640;


    srand(time(NULL));

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");
    SetTargetFPS(60);

    // creating the players

    Sprite carP1;
    carP1.tex = LoadTexture(p1Dir);
    carP1.pos.x = WIDTH/2 - carP1.tex.width/2-30;
    carP1.pos.y = HEIGHT*3/5;
    int car_speed = 4;

    //int diffy = 50;
    Sprite carP2;
    carP2.tex = LoadTexture("..\\res\\car2.png");
    carP2.pos.x = WIDTH/2 - carP2.tex.width/2+50;
    carP2.pos.y = HEIGHT*3/5 ;
    //int car2_speed = 4;

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

    int Turbo_txt1=1, Hueco_txt1=1, Past_txt1=1;
    int lives = 3;
    int scoreP = 0;
    int scoreP2 = 0;
    int gameTimer = 60;
    double timeScore = 0;
    double vulnerable_time, no_turbo_time, livesDowntimeTime = 0;
    bool gameOver = false;
    bool gameWon = false;
    bool vulnerable, no_turbo, livesDowntime = true;
    while(!WindowShouldClose()){



        //Lectura variables carro 2
        char inicio_2_txt [LIMITE];
        char vidas_2_txt [LIMITE];
        char score_2_txt [LIMITE];
        char xpos_2_txt [LIMITE];
        char ypos_2_txt [LIMITE];
        char turbo_2_txt [LIMITE];
        char hueco_2_txt [LIMITE];
        char pasto_2_txt [LIMITE];
        FILE* fichero2r;
        fichero2r = fopen("..\\Server\\src\\Variables\\out2.txt", "rt");
        fgets (inicio_2_txt, LIMITE, fichero2r);
        fgets (vidas_2_txt, LIMITE, fichero2r);
        fgets (score_2_txt, LIMITE, fichero2r);
        fgets (xpos_2_txt, LIMITE, fichero2r);
        fgets (ypos_2_txt, LIMITE, fichero2r);
        fgets (hueco_2_txt, LIMITE, fichero2r);
        fgets (pasto_2_txt, LIMITE, fichero2r);
        fclose(fichero2r);
        int aaaa = atoi(xpos_2_txt);
        int aaaaa = atoi(ypos_2_txt);


        if(!gameOver) {
            // process events
            if(IsKeyDown(KEY_LEFT)) {
                carP1.pos.x -= car_speed;
            } else if(IsKeyDown(KEY_RIGHT)) {
                carP1.pos.x += car_speed;
            } else if(IsKeyDown(KEY_DOWN)) {
                car_speed = dx/2;
            }
            /*if(IsKeyDown(KEY_A)) {
                carP2.pos.x -= car2_speed;
            } else if(IsKeyDown(KEY_D)) {
                carP2.pos.x += car2_speed;
            } else if(IsKeyDown(KEY_W)) {
                carP2.pos.y -= car2_speed;
            } else if(IsKeyDown(KEY_S)) {
                car2_speed = dx/2;
            }*/

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
                    Rectangle recP2 = { carP2.pos.x, carP2.pos.y, carP2.tex.width-10, carP2.tex.height };
                    if(CheckCollisionRecs(recP2, shoot[i].rect)) {
                        shoot[i].active = false;
                        scoreP += 100;
                    }
                    else {
                        shoot[i].rect.y += shoot[i].speed.y;
                    }
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
                        if (lives == 5){
                            lives = 5;
                        }
                        else {
                            lives += 1;
                            scoreP += 3;
                        }
                        livesDowntime = false;
                    }
                }
            }


            if(!vulnerable) {
                vulnerable_time += GetFrameTime();
                if(vulnerable_time > 1) {
                    vulnerable = true;
                    vulnerable_time = 0;
                    Hueco_txt1 =1;
                }
            }

            if(!no_turbo) {
                no_turbo_time += GetFrameTime();
                if(no_turbo_time > 1) {
                    no_turbo = true;
                    no_turbo_time = 0;
                    Turbo_txt1 = 1;
                    scoreP += 2;
                }
            }
            if(!livesDowntime) {
                livesDowntimeTime += GetFrameTime();
                if(livesDowntimeTime > 1) {
                    livesDowntime = true;
                    livesDowntimeTime = 0;

                }
            }


            if(lives <= 0) {
                gameOver = true;
            }
            int nopastotxt1 = atoi(pasto_2_txt);
            if (nopastotxt1 == 2) {
                carP2.pos.y += 4;
            }
            if(carP1.pos.x+10 < WIDTH/3 || carP1.pos.x + carP1.tex.width-10 > WIDTH*2/3) {
                car_speed=dx/2;
                carP2.pos.y -= 4;
                Past_txt1 = 2;
            }
            else {
                car_speed = dx;
                Past_txt1=1;
            }




            timeScore += GetFrameTime();
            if(timeScore > 1) {
                scoreP++;
                gameTimer--;
                timeScore = 0;
            }

            if(scoreP > 99999) {
                gameWon = true;
                gameOver = true;
            }

//          TODO:Cambiar para que ganador se defina por scores
            if(gameTimer <= 0){
                if (carP1.pos.y < carP2.pos.y){
                    scoreP += 2000;
                    if (scoreP > scoreP2){
                        gameWon = true;
                        gameOver = true;
                    }
                    else{
                        gameOver = true;
                    }
                }
                if (carP1.pos.y >= carP2.pos.y){
                    scoreP += 1000;
                    gameOver = true;
                    if (scoreP > scoreP2){
                        gameWon = true;
                        gameOver = true;
                    }
                    else{
                        gameOver = true;
                    }
                }
                else {
                    gameOver = true;
                }
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
        int no_huecotxt = atoi(hueco_2_txt);
        if(no_huecotxt == 2) {
            carP2.pos.y += 4;
        }
        if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP1.tex, carP1.pos.x, carP1.pos.y, col);
            car_speed = dx/2;
            carP2.pos.y -= 4;
            Hueco_txt1 = 2;

        } else {
            DrawTexture(carP1.tex, carP1.pos.x, carP1.pos.y, WHITE);

        }

        int no_turbotxt = atoi(turbo_2_txt);
        if(no_turbotxt == 2){
            carP2.pos.y -= 4;
        }

        if(!no_turbo) {
            car_speed = dx*2;
            carP2.pos.y += 4;
            Turbo_txt1 = 2;
        }

        /*if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, col);
        } else {
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, WHITE);
        }*/


        if(1){
            DrawTexture(carP2.tex, aaaa, carP2.pos.y, WHITE);
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
        char actLives[12] = { " " };
        char timeLeft[12] = { " " };
        char goText[12] = { " " };

        sprintf(scoring, "Score: %d", scoreP);
        DrawText(scoring, 10, 5, 30, WHITE);

        sprintf(actLives, "Lives: %d", lives);
        DrawText(actLives, WIDTH-120, 5, 30, WHITE);

        sprintf(timeLeft, "Time: %d", gameTimer);
        DrawText(timeLeft, 10, HEIGHT-35, 30, WHITE);

        if (gameTimer > 59){
            sprintf(goText, "Go!");
            DrawText(goText, WIDTH/2-30, HEIGHT/2-20, 40, WHITE);
        }
        //Escritura txt carro 1
        char iniciotxt1[12] ={ " "};
        char actLivestxt1[12] = { " " };
        char scoringtxt1[12] = { " " };
        char actXpostxt1[12] ={ " "};
        char actYpostxt1[12] ={ " "};
        char actTurbotxt1[12] ={ " "};
        char actHuecotxt1[12] ={ " "};
        char actPastotxt1[12] ={ " "};
        sprintf(actLivestxt1, "%d ", lives);
        sprintf(scoringtxt1, "%d", scoreP);
        sprintf(actXpostxt1, "%f", carP1.pos.x);
        sprintf(actYpostxt1, "%f", carP1.pos.y);
        sprintf(actTurbotxt1, "%d", Turbo_txt1);
        sprintf(actHuecotxt1, "%d", Hueco_txt1);
        sprintf(actPastotxt1, "%d", Past_txt1);
        const char* filename1w = "..\\Server\\src\\Variables\\out.txt";
        FILE* fichero1w = fopen(filename1w, "w+");
        if (!fichero1w) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fwrite(iniciotxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actLivestxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(scoringtxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actXpostxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actYpostxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actTurbotxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actHuecotxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fwrite(actPastotxt1, 1, strlen(scoring), fichero1w);
        fwrite(str2, 1, strlen(str2), fichero1w);
        fclose(fichero1w);










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
    UnloadTexture(carP2.tex);
    CloseWindow();
}

/*---Player 2-------------------------------------------------------------------------------------------------------------------------------*/

void mainGameP2(char p2Dir[]){
    const int WIDTH = 480;
    const int HEIGHT = 640;

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


    srand(time(NULL));

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");
    SetTargetFPS(60);

    // creating the players

    Sprite carP2;
    carP2.tex = LoadTexture(p2Dir);
    carP2.pos.x = WIDTH/2 - carP2.tex.width/2+30;
    carP2.pos.y = HEIGHT*3/5;
    int car_speed = 4;

    //int diffy = 50;
    Sprite carP1;
    carP1.tex = LoadTexture("..\\res\\car1.png");
    carP1.pos.x = WIDTH/2 - carP1.tex.width/2-50;
    carP1.pos.y = HEIGHT*3/5 ;
    //int car2_speed = 4;

    int dx = 4;


    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rect.x = carP2.pos.x;
        shoot[i].rect.y = carP2.pos.y + HEIGHT / 4;
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

    int Turbo_txt2=1, Hueco_txt2=1, Past_txt2 = 1, Dify=0;
    int lives = 3;
    int scoreP1, scoreP2 = 0;
    int gameTimer = 60;
    double timeScore = 0;
    double vulnerable_time, no_turbo_time, livesDowntimeTime = 0;
    bool gameOver = false;
    bool gameWon = false;
    bool vulnerable, no_turbo, livesDowntime = true;
    while(!WindowShouldClose()){
        //Lectura variables carro 1
        char inicio_1_txt [LIMITE];
        char vidas_1_txt [LIMITE];
        char score_1_txt [LIMITE];
        char xpos_1_txt [LIMITE];
        char ypos_1_txt [LIMITE];
        char turbo_1_txt [LIMITE];
        char hueco_1_txt [LIMITE];
        char pasto_1_txt [LIMITE];
        FILE* fichero1r;
        fichero1r = fopen("..\\Server\\src\\Variables\\out.txt", "rt");
        fgets (inicio_1_txt, LIMITE, fichero1r);
        fgets (vidas_1_txt, LIMITE, fichero1r);
        fgets (score_1_txt, LIMITE, fichero1r);
        fgets (xpos_1_txt, LIMITE, fichero1r);
        fgets (ypos_1_txt, LIMITE, fichero1r);
        fgets (hueco_1_txt, LIMITE, fichero1r);
        fgets (pasto_1_txt, LIMITE, fichero1r);
        fclose(fichero1r);
        puts(xpos_1_txt);
        puts(ypos_1_txt);

        //Lectura variables carro 2
        char inicio_2_txt [LIMITE];
        char vidas_2_txt [LIMITE];
        char score_2_txt [LIMITE];
        char xpos_2_txt [LIMITE];
        char ypos_2_txt [LIMITE];
        char turbo_2_txt [LIMITE];
        char hueco_2_txt [LIMITE];
        char pasto_2_txt [LIMITE];
        FILE* fichero2r;
        fichero2r = fopen("..\\Server\\src\\Variables\\out2.txt", "rt");
        fgets (inicio_2_txt, LIMITE, fichero2r);
        fgets (vidas_2_txt, LIMITE, fichero2r);
        fgets (score_2_txt, LIMITE, fichero2r);
        fgets (xpos_2_txt, LIMITE, fichero2r);
        fgets (ypos_2_txt, LIMITE, fichero2r);
        fgets (hueco_2_txt, LIMITE, fichero2r);
        fgets (pasto_2_txt, LIMITE, fichero2r);
        fclose(fichero2r);
        if(!gameOver) {
            // process events
            if(IsKeyDown(KEY_LEFT)) {
                carP2.pos.x -= car_speed;
            } else if(IsKeyDown(KEY_RIGHT)) {
                carP2.pos.x += car_speed;
            } else if(IsKeyDown(KEY_DOWN)) {
                car_speed = dx/2;
            }
            /*if(IsKeyDown(KEY_A)) {
                carP2.pos.x -= car2_speed;
            } else if(IsKeyDown(KEY_D)) {
                carP2.pos.x += car2_speed;
            } else if(IsKeyDown(KEY_W)) {
                carP2.pos.y -= car2_speed;
            } else if(IsKeyDown(KEY_S)) {
                car2_speed = dx/2;
            }*/

            if (IsKeyDown(KEY_SPACE))
            { shootRate += 5;
                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!shoot[i].active && shootRate % 40 == 0)
                    {
                        shoot[i].rect.x = carP2.pos.x+12;
                        shoot[i].rect.y = carP2.pos.y;
                        shoot[i].active = true;
                        break;
                    }
                }
            }
            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    Rectangle recP1 = { carP1.pos.x, carP1.pos.y, carP1.tex.width-10, carP1.tex.height };
                    if(CheckCollisionRecs(recP1, shoot[i].rect)) {
                        shoot[i].active = false;
                        scoreP2 += 100;
                    }
                    else {
                        shoot[i].rect.y += shoot[i].speed.y;
                    }
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
                Rectangle rec1 = { carP2.pos.x, carP2.pos.y, carP2.tex.width-10, carP2.tex.height };
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
                Rectangle rec1 = { carP2.pos.x, carP2.pos.y, carP2.tex.width, carP2.tex.height };
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
                Rectangle rec1 = { carP2.pos.x, carP2.pos.y, carP2.tex.width, carP2.tex.height };
                Rectangle rec4 = { heart_pos[i].x, heart_pos[i].y, theart.width/6, theart.height };
                if(CheckCollisionRecs(rec1, rec4)) {
                    if(livesDowntime) {
                        if (lives == 5){
                            lives = 5;
                        }
                        else {
                            lives += 1;
                            scoreP2 += 3;
                        }
                        livesDowntime = false;
                    }
                }
            }


            if(!vulnerable) {
                vulnerable_time += GetFrameTime();
                if(vulnerable_time > 1) {
                    vulnerable = true;
                    vulnerable_time = 0;
                    Hueco_txt2 =1;
                }
            }
            if(!no_turbo) {
                no_turbo_time += GetFrameTime();
                if(no_turbo_time > 1) {
                    no_turbo = true;
                    no_turbo_time = 0;
                    Turbo_txt2= 1;
                    scoreP2 += 2;
                }
            }
            if(!livesDowntime) {
                livesDowntimeTime += GetFrameTime();
                if(livesDowntimeTime > 1) {
                    livesDowntime = true;
                    livesDowntimeTime = 0;
                }
            }


            if(lives <= 0) {
                gameOver = true;
            }
            int nopastotxt2 = atoi(pasto_1_txt);
            if (nopastotxt2 == 2){
                carP1.pos.y += 4;
            }
//          Movimiento zacate
            if(carP2.pos.x+10 < WIDTH/3 || carP2.pos.x + carP2.tex.width-10 > WIDTH*2/3) {
                car_speed=dx/2;
                carP1.pos.y -= 4;
                Past_txt2 =2;
            }
            else {
                car_speed = dx;
                Past_txt2 = 1;
            }

            timeScore += GetFrameTime();
            if(timeScore > 1) {
                scoreP2++;
                gameTimer--;
                timeScore = 0;
            }

            if(scoreP2 > 99999) {
                gameWon = true;
                gameOver = true;
            }

//          TODO:Cambiar para que ganador se defina por scores
            if(gameTimer <= 0){
                if (carP2.pos.y < carP1.pos.y){
                    scoreP2 += 2000;
                    if (scoreP2 > scoreP1){
                        gameWon = true;
                        gameOver = true;
                    }
                    else{
                        gameOver = true;
                    }
                }
                if (carP2.pos.y >= carP1.pos.y){
                    scoreP2 += 1000;
                    gameOver = true;
                    if (scoreP2 > scoreP1){
                        gameWon = true;
                        gameOver = true;
                    }
                    else{
                        gameOver = true;
                    }
                }
                else {
                    gameOver = true;
                }
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
        int nohuecotxt2 = atoi(hueco_1_txt);
        if (nohuecotxt2==2){
            carP1.pos.y += 4;
        }
        if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, col);
            car_speed = dx/2;
            carP1.pos.y -= 4;
            Hueco_txt2=2;

        } else {
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, WHITE);
        }
        int noturbotxt2 = atoi(turbo_1_txt);
        if (noturbotxt2==2){
            carP1.pos.y -= 4;
        }
        if(!no_turbo) {
            car_speed = dx*2;
            carP1.pos.y += 4;
            Turbo_txt2 = 2;
        }

        /*if(!vulnerable) {
            Color col = { 0, 0, 0, 100 };
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, col);
        } else {
            DrawTexture(carP2.tex, carP2.pos.x, carP2.pos.y, WHITE);
        }*/

        int xtxt = atoi(xpos_1_txt);
        int ytxt = atoi(ypos_1_txt);
        if(1){
            DrawTexture(carP1.tex, xtxt, carP1.pos.y, WHITE);
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
        char actLives[12] = { " " };
        char timeLeft[12] = { " " };
        char goText[12] = { " " };

        sprintf(scoring, "Score: %d", scoreP2);
        DrawText(scoring, 10, 5, 30, WHITE);

        sprintf(actLives, "Lives: %d", lives);
        DrawText(actLives, WIDTH-120, 5, 30, WHITE);

        sprintf(timeLeft, "Time: %d", gameTimer);
        DrawText(timeLeft, 10, HEIGHT-35, 30, WHITE);

        if (gameTimer > 59){
            sprintf(goText, "Go!");
            DrawText(goText, WIDTH/2-30, HEIGHT/2-20, 40, WHITE);
        }
        char scoringtxt[12] = { " " };
        char actLivestxt[12] = { " " };
        char timeLefttxt[12] = { " " };
        sprintf(scoringtxt, "%d", scoreP2);
        sprintf(actLivestxt, "%d ", lives);
        sprintf(timeLefttxt, "%d", gameTimer);


//Escritura txt carro 2
        char iniciotxt2[12] ={ " "};
        char actLivestxt2[12] = { " " };
        char scoringtxt2[12] = { " " };
        char actXpostxt2[12] ={ " "};
        char actYpostxt2[12] ={ " "};
        char actTurbotxt2[12] ={ " "};
        char actHuecotxt2[12] ={ " "};
        char actPastotxt2[12] ={ " "};
        sprintf(actLivestxt2, "%d ", lives);
        sprintf(scoringtxt2, "%d", scoreP2);
        sprintf(actXpostxt2, "%f", carP2.pos.x);
        sprintf(actYpostxt2, "%f", carP2.pos.y);
        sprintf(actTurbotxt2, "%d", Turbo_txt2);
        sprintf(actHuecotxt2, "%d", Hueco_txt2);
        sprintf(actPastotxt2, "%d", Past_txt2);
        const char* filename2w = "..\\Server\\src\\Variables\\out2.txt";
        FILE* fichero2w = fopen(filename2w, "w+");
        if (!fichero2w) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fwrite(iniciotxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actLivestxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(scoringtxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actXpostxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actYpostxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actTurbotxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actHuecotxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fwrite(actPastotxt2, 1, strlen(scoring), fichero2w);
        fwrite(str2, 1, strlen(str2), fichero2w);
        fclose(fichero2w);



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
    UnloadTexture(carP2.tex);
    CloseWindow();
}

void selectCar(int playerID){
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
                if(playerID == 1){
                    mainGameP1("..\\res\\car1.png");
                }
                if(playerID == 2){
                    mainGameP2("..\\res\\car1.png");
                }
            }
            if(selectSqr.pos.x == WIDTH*2/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                if(playerID == 1){
                    mainGameP1("..\\res\\car2.png");
                }
                if(playerID == 2){
                    mainGameP2("..\\res\\car2.png");
                }
            }
            if(selectSqr.pos.x == WIDTH*3/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                if(playerID == 1){
                    mainGameP1("..\\res\\car3.png");
                }
                if(playerID == 2){
                    mainGameP2("..\\res\\car3.png");
                }
            }
            if(selectSqr.pos.x == WIDTH*4/6){
                UnloadTexture(car1.tex);
                UnloadTexture(car2.tex);
                UnloadTexture(car3.tex);
                UnloadTexture(car4.tex);
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                if(playerID == 1){
                    mainGameP1("..\\res\\car4.png");
                }
                if(playerID == 2){
                    mainGameP2("..\\res\\car4.png");
                }
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

void loadingPage(){
    const int WIDTH = 840;
    const int HEIGHT = 480;

    // init
    InitWindow(WIDTH, HEIGHT, "POLE POSITION");

    Sprite selectSqr;

    SetTargetFPS(60);

    selectSqr.tex = LoadTexture("..\\res\\selecting.png");
    selectSqr.pos.x = WIDTH*1/3-40;
    selectSqr.pos.y = HEIGHT/2 - selectSqr.tex.height/2;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        /*if (IsKeyPressed(KEY_P) || IsGestureDetected(GESTURE_TAP))
        {

            CloseWindow();
            selectCar();
        }*/

        if (IsKeyPressed(KEY_LEFT) || IsGestureDetected(GESTURE_TAP))
        {
            selectSqr.pos.x = WIDTH*1/3-40;
        }

        if (IsKeyPressed(KEY_RIGHT) || IsGestureDetected(GESTURE_TAP))
        {

            selectSqr.pos.x = WIDTH*2/3-30;
        }

        if (IsKeyPressed(KEY_P) || IsGestureDetected(GESTURE_TAP)) {
            if (selectSqr.pos.x == WIDTH*1/3-40) {
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                selectCar(1);
            }
            if (selectSqr.pos.x == WIDTH*2/3-30) {
                UnloadTexture(selectSqr.tex);
                CloseWindow();
                selectCar(2);
            }
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, WIDTH, HEIGHT, BLUE);

        DrawText("ELIJA UN JUGADOR (Y PRESIONA P)", 20, 20, 40, LIGHTGRAY);
        DrawText("P1", WIDTH*1/3, HEIGHT/2-30, 60, LIGHTGRAY);
        DrawText("P2", WIDTH*2/3, HEIGHT/2-30, 60, LIGHTGRAY);

        DrawTexture(selectSqr.tex, selectSqr.pos.x, selectSqr.pos.y, WHITE);
//        DrawText("CARGANDO... (PRESIONE P)", 290, 220, 25, BLACK);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    //UnloadTexture(car1.tex);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}
char SendBuff[512],RecvBuff[512];

int cliente(){

    WSADATA wsaData;
    SOCKET conn_socket;
    struct sockaddr_in server;
    struct hostent *hp;
    int resp;

    //Inicializamos la DLL de sockets
    resp=WSAStartup(MAKEWORD(1,0),&wsaData);
    if(resp){
        printf("Error al inicializar socket\n");
        getchar();return -1;
    }

    //Obtenemos la IP del servidor... en este caso
    // localhost indica nuestra propia máquina...
    hp=(struct hostent *)gethostbyname("localhost");

    if(!hp){
        printf("No se ha encontrado servidor...\n");
        getchar();WSACleanup();return WSAGetLastError();
    }

    // Creamos el socket...
    conn_socket=socket(AF_INET,SOCK_STREAM, 0);
    if(conn_socket==INVALID_SOCKET) {
        printf("Error al crear socket\n");
        getchar();WSACleanup();return WSAGetLastError();
    }

    memset(&server, 0, sizeof(server)) ;
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(9300);


    // Nos conectamos con el servidor...
    if(connect(conn_socket,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR){
        printf("Fallo al conectarse con el servidor\n");
        closesocket(conn_socket);
        WSACleanup();getchar();return WSAGetLastError();
    }
    printf("Conexion establecida con: %s\n", inet_ntoa(server.sin_addr));


    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}

int main(void) {

//    mainGame();
    //selectCar();

    cliente();
     loadingPage();
    return 0;
}