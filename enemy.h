// enemy.h
#include <raylib.h>
#include <iostream>

typedef struct Enemy
{
    Vector2 position;
    Vector2 size;
    Texture2D texture;
    float width;
    float height;
    float speed;
    bool active;      
    
}Enemy;

Enemy InitEnemy(int windowWidth, int windowHeight, float speed, const char* texturePath);
void UpdateEnemy(Enemy* enemy);
void DrawEnemy(Enemy* enemy);