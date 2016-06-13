#ifndef TILEMAP_H
#define TILEMAP_H

#include "renderable.h"
#include <map>
#include <list>
#include "entity.h"

class Pathfinder;
class GameState;

class TileMap : public Renderable
{
    int** map;
    std::map<int, QPixmap*> textures;
    int width, height;
    bool loaded = false;
    //int wallId = 2;
    //int groundId = 1;
    std::list<Entity*> entities;
    Pathfinder* finder;
    GameState* game;
    int getGround();
    int getWall();
    void registerTile(int, QString);
public:
    TileMap(GameState*);
    ~TileMap();
    bool load(QString);
    void generateMaze(int, int, bool);
    void render(QPainter *);
    void update();
    void onMousePressed(int x, int y, Qt::MouseButton button);
    void onMouseReleased(int x, int y, Qt::MouseButton button);
    void onMouseMove(int x, int y);
    void addEntity(Entity*);
    bool contains(QRect, QRect);
    bool isWalkable(int);
    bool isWalkable(int, int);
    int getTile(int, int);
    int offsetX = 0, offsetY = 0;
    bool isKeyDown(int);
    int getWidth();
    int getHeight();
    Pathfinder* getPathfinder();
    GameState* getGameState();
    Entity* collides(Entity*);
    std::map<int, bool>* keys = new std::map<int, bool>();
    int minX = 2000;
    int minY = 2000;
    int maxX = 0;
    int maxY = 0;
};

#endif // TILEMAP_H
