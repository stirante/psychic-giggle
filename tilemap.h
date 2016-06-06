#ifndef TILEMAP_H
#define TILEMAP_H

#include "renderable.h"
#include <map>

class TileMap : public Renderable
{
    int** map;
    std::map<int, QPixmap*> textures;
    int width, height;
public:
    TileMap();
    bool load(QString);
    virtual void render(QPainter *);
    virtual void update();
    virtual void onMousePressed(int x, int y, Qt::MouseButton button);
    virtual void onMouseReleased(int x, int y, Qt::MouseButton button);
    virtual void onMouseMove(int x, int y);
    int offsetX = 0, offsetY = 0;
};

#endif // TILEMAP_H
