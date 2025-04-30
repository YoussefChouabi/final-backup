// enemy.cpp
#include "enemy.h"
#include "Player.h"

Enemy InitEnemy(int windowWidth, int windowHeight, float speed, const char* texturePath) {
    Enemy enemy;
    enemy.texture = LoadTexture(texturePath);
    float scale = 0.4f;
    enemy.size = {128 * scale, 128 * scale};
    enemy.active = true;
    enemy.speed = speed;
    
    // Position the enemy at the right edge with random Y position
    enemy.position.x = (float)windowWidth;
    enemy.position.y = (float)windowHeight * 0.57f;
    
    return enemy;
}

void UpdateEnemy(Enemy* enemy) {
    float dt = GetFrameTime();
    enemy->position.x -= enemy->speed * dt;

    // Deactivate if out of bounds
    if (enemy->position.x < -enemy->size.x) {
        enemy->active = false;
    }

    // Respawn only if inactive
    if (!enemy->active) {
        int winW = GetScreenWidth();
        int winH = GetScreenHeight();
        enemy->position.x = (float)winW;
        enemy->position.y = (float)winH * 0.57f;
        enemy->active = true;
    }
}

void DrawEnemy(Enemy* enemy) {
    if (!enemy->active) return;

    Rectangle src = {0, 0, 128, 128};
    Rectangle dst = {
        enemy->position.x,
        enemy->position.y,
        enemy->size.x,
        enemy->size.y
    };
    DrawTexturePro(enemy->texture, src, dst, {0,0}, 0.0f, WHITE);
}