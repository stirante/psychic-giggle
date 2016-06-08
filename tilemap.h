#ifndef TILEMAP_H
#define TILEMAP_H

#include "renderable.h"
#include <map>
#include <list>
#include "entity.h"

class TileMap : public Renderable
{
    int** map;
    std::map<int, QPixmap*> textures;
    int width, height;
    bool loaded = false;
    bool contains(QRect, QRect);
    std::list<Entity*> entities;
public:
    TileMap();
    bool load(QString);
    void render(QPainter *);
    void update();
    void onMousePressed(int x, int y, Qt::MouseButton button);
    void onMouseReleased(int x, int y, Qt::MouseButton button);
    void onMouseMove(int x, int y);
    void addEntity(Entity*);
    int offsetX = 0, offsetY = 0;
    std::map<int, bool>* keys;
};

#endif // TILEMAP_H
