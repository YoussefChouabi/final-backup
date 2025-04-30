#include "Player.h"

Player InitPlayer(int windowWidth,int windowHeigh){

    Player player;
    player.playerTexture = LoadTexture("Player/player.png");
    


    player.size = { player.playerTexture.width * 1.0f,player.playerTexture.height *1.0f };

    player.position = {
        (windowWidth - player.size.x) /2 -250,
        (windowHeigh - player.size.y) /2 + 110
    };
    player.speed =0.1f;

    player.gravity =800.0f;
    player.isJumping = false;
    player.velectiy = 0;
    player.groundy = player.position.y;
    player.JumpForce =-400.0f;

    player.isactive =true;
    return player;
}
void drawPlayer(Player* player){

    DrawTextureEx(player->playerTexture, player->position,0.0f,0.5f,WHITE);
}

void updateplayer(Player* player) {
    float dt = GetFrameTime();
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();

    // Horizontal movement with boundary check
    if (IsKeyDown(KEY_RIGHT)) {
        player->position.x += player->speed;
        // Prevent going beyond right edge (considering player size)
        if (player->position.x > windowWidth - player->size.x * 0.5f) {
            player->position.x = windowWidth - player->size.x * 0.5f;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        player->position.x -= player->speed;
        // Prevent going beyond left edge
        if (player->position.x < 0) {
            player->position.x = 0;
        }
    }
    
    // Jumping logic
    if (!player->isJumping && IsKeyPressed(KEY_UP)) {
        player->velectiy = player->JumpForce;
        player->isJumping = true;
    }

    // Apply gravity
    player->velectiy += player->gravity * dt;
    player->position.y += player->velectiy * dt;

    // Ground check
    if (player->position.y >= player->groundy) {
        player->position.y = player->groundy;
        player->velectiy = 0;
        player->isJumping = false;
    }

    // Prevent falling through the bottom (optional safety check)
    if (player->position.y > windowHeight - player->size.y * 0.5f) {
        player->position.y = windowHeight - player->size.y * 0.5f;
        player->velectiy = 0;
        player->isJumping = false;
    }
}
    