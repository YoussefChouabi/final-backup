#include "Map.h"

Map InitMap(int windowWidth,int windowHeight){
    Map map;
    map.blockTexture = LoadTexture("Map/grass.png");
    map.block2Texture = LoadTexture("Map/dirt.png");
    map.CloudTexture = LoadTexture("Map/cloud.png");
    map.TreeTexture = LoadTexture("Map/Tree.png");
    map.WinBlockTexture = LoadTexture("Map/coin.png"); 
    map.blockWidth = (float)map.blockTexture.width;
    map.blockHight = (float)map.blockTexture.height;

    for (int i = 0; i < TREE_COUNT; i++)
    {
        map.treePosition[i] = {i *300.0f,280.0f};
    }


    // map.winBlockPosition = {windowWidth + 500.0f, 280.0f};
    map.winBlockPosition = {
        (windowWidth - map.WinBlockTexture.width*0.5f) /2 + 425,  // Center X
        400.0f  // Same Y position as trees
    };

    return map;
}

void updateMap(Map* map){
    float treeSpeed = 0.2f;
    for (int i = 0; i < TREE_COUNT; i++)
    {
        map->treePosition[i].x -= treeSpeed;

        if (map->treePosition[i].x < -map->TreeTexture.width* 0.2f)
        {
            map->treePosition[i].x = GetScreenWidth();
        }
        
    }
    
}

void drawMap(Map* map){
    float scale = 0.1f;
    float scaleWidth = map->blockWidth * scale;
    float scaleHight = map->blockHight * scale;

    // float x = (GetScreenWidth() - scaleWidth) / 2;
    float y = GetScreenWidth() * 0.6f;
    float y2 = y + scaleHight;

    int blockcountx = GetScreenWidth() / scaleWidth + 1;

    int blockcounty = GetScreenHeight() / scaleHight + 1;

    for (int i = 0; i < TREE_COUNT; i++)
    {
        float x =  i* 250;
        DrawTextureEx(map->TreeTexture,map->treePosition[i],0.0f,0.375f,WHITE); 
    
    }

    for (int i = 0; i < blockcountx; i++)
    {
        float x = i * scaleWidth;
        DrawTextureEx(map->blockTexture,{x,y},0.0f,scale,WHITE);
    }
    for (int j = 1; j < blockcounty; j++)
    {
        float rowy = y + j * scaleHight;
        for (int i = 0; i < blockcountx; i++)
        {
            float x = i * scaleWidth;
            DrawTextureEx(map->block2Texture,{x,rowy},0.0f,scale,WHITE);
       }
    }
    
    DrawTexture(map->CloudTexture,0,-50,WHITE); 
    DrawTextureEx(map->WinBlockTexture, map->winBlockPosition, 0.0f, 0.1f, WHITE);
    
    
    
}