#include <raylib.h>

#define TREE_COUNT 3
typedef struct 
{
    Vector2 treePosition[TREE_COUNT];
    Vector2 winBlockPosition;
    float blockWidth;
    float blockHight;
    Texture2D blockTexture;
    Texture2D block2Texture;
    Texture2D CloudTexture;
    Texture2D TreeTexture;
    Texture2D WinBlockTexture; 
}Map;

Map InitMap(int windowWidth,int WindowHight);
void updateMap(Map* map);
void drawMap(Map* map);