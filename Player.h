#include <raylib.h>

typedef struct Player{
    Texture2D playerTexture;
    Vector2 position;
    Vector2 size;
    float speed;
   float velectiy;
   float gravity;
   float groundy;
   float JumpForce;
   bool isJumping;
   bool isactive;
   
}Player;

Player InitPlayer(int windowWidth,int windowHeight);

void drawPlayer(Player* player);


void updateplayer(Player* player);