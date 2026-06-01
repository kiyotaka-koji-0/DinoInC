#include "raylib.h"
#include "raymath.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <stdbool.h>
#include <stddef.h>

#define winheight 500
#define winwidth 900
#define gravity 800.0f
#define dinoRunVel 200.0f
#define dinoJumpVel 500.0f
#define CameraStartingX 700
#define dinoScale 0.10f
#define cactiScale 0.15f

static const size_t totalCactus = 15;

Texture2D cactustTex = {};
bool isGameOver = false;

typedef struct Dino {
  Texture2D asset;
  Vector2 pos;
  bool isOnGround;
  float velocity;
} Dino;

typedef struct Obstacle {
  bool isActive;
  Vector2 pos;

} Obstacle;

Obstacle cacti[15];


void ResetGame(Dino *dino);
bool CollisionCheck(Dino *dino, Obstacle *cacti);
void ControlDino(Dino *dino);

void UpdateGame(Dino *dino) {
  float dt = GetFrameTime();
  float groundY = (float)winheight / 2 + (dino->asset.height * dinoScale) - 50;
  

  float farthestX = 0.0f;

  if (dino->isOnGround == false) {
    dino->velocity += gravity * dt;
    dino->pos.y += dino->velocity * dt;
    if (dino->pos.y >= groundY) {
      dino->pos.y = groundY;
      dino->velocity = 0.0f;
      dino->isOnGround = true;
    }
  } else {
    dino->pos.y = groundY;
    dino->velocity = 0.0f;
  }

  for (size_t i = 0; i < totalCactus; i++) {
    if (cacti[i].isActive && cacti[i].pos.x > farthestX) {
      farthestX = cacti[i].pos.x;
    }
  }

  for (size_t i = 0; i < totalCactus; i++) {
    if (cacti[i].isActive == true) {
      cacti[i].pos.x -= 150 * dt;
      if(CollisionCheck(dino, &cacti[i])) isGameOver = true;
    }

    if (cacti[i].isActive &&
        cacti[i].pos.x + (cactustTex.width * cactiScale) < 0)
      cacti[i].isActive = false;

    if (!cacti[i].isActive) {
      float gap = GetRandomValue(190, 400);
      cacti[i].pos.x = farthestX + gap;
      cacti[i].pos.y = (float)winheight / 2+(cactustTex.height*cactiScale);
      cacti[i].isActive = true;
      farthestX = cacti[i].pos.x;
    }
  }


  
}

bool CollisionCheck(Dino *dino, Obstacle *cacti){
    Rectangle obsBounding = {cacti->pos.x, cacti->pos.y,
                               cactustTex.width * cactiScale,
                               cactustTex.height * cactiScale};

    Rectangle dinoBounding = {
        dino->pos.x,
        dino->pos.y,
        dino->asset.width*dinoScale-100,
        dino->asset.height*dinoScale
    };

    if (CheckCollisionRecs(obsBounding, dinoBounding)) return true; else return false;
}

void ControlDino(Dino *dino){
  if (IsKeyPressed(KEY_SPACE) && dino->isOnGround) {
    dino->isOnGround = false;
    dino->velocity = -dinoJumpVel;
  }
}

void Loading(Dino *dino) {
  Image cactusImg = LoadImage("assets/cactus.png");
  Image dinoImage = LoadImage("assets/dino.png");
  dino->asset = LoadTextureFromImage(dinoImage);
  cactustTex = LoadTextureFromImage(cactusImg);
  UnloadImage(cactusImg);
  UnloadImage(dinoImage);
}

void ResetGame(Dino *dino) {
  dino->pos = (Vector2){0 + 20, ((float)winheight / 2 + (dino->asset.height*dinoScale))};
  dino->isOnGround = true;
  float farthestX = 500.0f;
  for (size_t i = 0; i < totalCactus; i++) {
    cacti[i].isActive = true;
    cacti[i].pos = (Vector2){farthestX, (float)winheight / 2+(cactustTex.height*cactiScale)};
    float gap = GetRandomValue(200, 300);
    farthestX += gap;
  }

  isGameOver = false;
}

void Unloading(Dino *dino) {
  UnloadTexture(dino->asset);
  UnloadTexture(cactustTex);
}

void Draw(Dino *dino) {

  for (size_t i = 0; i < totalCactus; i++) {
    if (cacti[i].isActive) {

      Rectangle obsBounding = {cacti[i].pos.x, cacti[i].pos.y,
                               cactustTex.width * cactiScale,
                               cactustTex.height * cactiScale};
    
    DrawTextureEx(cactustTex, cacti[i].pos, 0.0f, cactiScale, RAYWHITE);
    DrawRectangleLinesEx(obsBounding,5.0f, GREEN);

    DrawTextureEx(dino->asset, dino->pos, 0.0f , dinoScale, RAYWHITE);
    DrawLineDashed((Vector2){0, (float)winheight/2+(dino->asset.height*dinoScale)+50}, (Vector2){winwidth, (float)winheight/2+(dino->asset.height*dinoScale)+50}, 5.0f, 1.0f, BLACK);

  };
}
}

int main() {
  InitWindow(winwidth, winheight, "Dino");
  SetTargetFPS(60);
  Dino dino;
  Camera2D camera = {0};
  camera.offset = (Vector2){(float)winwidth * 0.35f, (float)winheight * 0.5f};
  camera.target = (Vector2){0.0f, 0.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  Loading(&dino);

  ResetGame(&dino);

  while (!WindowShouldClose()) {

    ControlDino(&dino);
    camera.target = (Vector2){dino.pos.x, dino.pos.y};

    if(isGameOver){
      ResetGame(&dino);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);

    BeginMode2D(camera);
    UpdateGame(&dino);
    EndMode2D();
    Draw(&dino);
    EndDrawing();
  }
  Unloading(&dino);

  CloseWindow();
  return 0;
}