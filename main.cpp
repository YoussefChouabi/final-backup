
#include <raylib.h>
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "enemy.h"

typedef enum {INTRO,PLAY,GameOver,WIN} GameState;

int main()
{
    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth,windowHeight, "my game");
    
    Player player = InitPlayer(windowWidth,windowHeight);
    Map map = InitMap(windowWidth,windowHeight);
    Camera2D camera = InitCamera(windowWidth,windowHeight);
    
    // Initialize two enemies with different speeds
    Enemy enemy1 = InitEnemy(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
    Enemy enemy2 = InitEnemy(windowWidth, windowHeight, 250.0f, "Enemy/devil.png"); // Higher speed
    
    GameState gamestate = INTRO;
    
    const char* message = "press ENTER to start game";
    const char* messageGameOver = "GAME OVER press Enter to play";
    const char* messageWin = "YOU WIN! Press Enter to play again";
    int fontSize = 30;
    int textWidth = MeasureText(message,fontSize);
    int textx = (windowWidth - textWidth) /2;
    int texty = windowHeight / 2 - 150;
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        switch (gamestate)
        {
        case INTRO:
            if (IsKeyPressed(KEY_ENTER))
            {
                gamestate = PLAY;
            }
            drawMap(&map);
            drawPlayer(&player);
            DrawText(message,textx,texty,fontSize,BLACK);
            break;
        case PLAY:
            {
                updateplayer(&player);
                updateMap(&map);
                UpdateEnemy(&enemy1);
                UpdateEnemy(&enemy2);

                // Check collisions with both enemies
                Rectangle playerRect = { player.position.x, player.position.y, player.size.x * 0.3f, player.size.y * 0.3f };
                
                if (enemy1.active) {
                    Rectangle enemyRect = { enemy1.position.x, enemy1.position.y, enemy1.size.x, enemy1.size.y };
                    if (CheckCollisionRecs(playerRect, enemyRect)) {
                        player.isactive = false;
                    }
                }
                
                if (enemy2.active) {
                    Rectangle enemyRect = { enemy2.position.x, enemy2.position.y, enemy2.size.x, enemy2.size.y };
                    if (CheckCollisionRecs(playerRect, enemyRect)) {
                        player.isactive = false;
                    }
                }

                Rectangle winBlockRect = {
                    map.winBlockPosition.x,
                    map.winBlockPosition.y,
                    map.WinBlockTexture.width * 0.5f,
                    map.WinBlockTexture.height * 0.5f
                };
                
                if (CheckCollisionRecs(playerRect, winBlockRect)) {
                    gamestate = WIN;
                }


                drawMap(&map);
                DrawEnemy(&enemy1);
                DrawEnemy(&enemy2);
                drawPlayer(&player);

                if(!player.isactive)
                    gamestate = GameOver;
            }
            break;
        case WIN:  // Add this case
            if (IsKeyPressed(KEY_ENTER)) {
                player = InitPlayer(windowWidth, windowHeight);
                enemy1 = InitEnemy(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
                enemy2 = InitEnemy(windowWidth, windowHeight, 250.0f, "Enemy/devil.png");
                map = InitMap(windowWidth, windowHeight);
                camera = InitCamera(windowWidth, windowHeight);
                gamestate = PLAY;
            }
            drawMap(&map);
            drawPlayer(&player);
            DrawText(messageWin, textx, texty, fontSize, DARKGREEN);
            break;
        case GameOver:
            if (IsKeyPressed(KEY_ENTER)) {
                player = InitPlayer(windowWidth, windowHeight);
                enemy1 = InitEnemy(windowWidth, windowHeight, 150.0f, "Enemy/zombie.png");
                enemy2 = InitEnemy(windowWidth, windowHeight, 250.0f, "Enemy/devil.png");
                camera = InitCamera(windowWidth, windowHeight);
                gamestate = PLAY;
            }
            drawMap(&map);
            drawPlayer(&player);
            DrawEnemy(&enemy1);
            DrawEnemy(&enemy2);
            DrawText(messageGameOver,textx,texty,fontSize,RED);
            break;
        }

        EndDrawing();
    }
    
    // Clean up
    UnloadTexture(map.blockTexture);
    UnloadTexture(map.block2Texture);
    UnloadTexture(map.CloudTexture);
    UnloadTexture(map.TreeTexture);
    UnloadTexture(player.playerTexture);
    UnloadTexture(enemy1.texture);
    UnloadTexture(enemy2.texture);
    UnloadTexture(map.WinBlockTexture);
    CloseWindow();
    return 0;
}
