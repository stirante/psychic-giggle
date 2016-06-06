#include "tilemap.h"
#include <iostream>
#include <fstream>

TileMap::TileMap()
{
    QPixmap* pix = new QPixmap();
    pix->load(":assets/dirt.png");
    textures[1] = pix;
    pix = new QPixmap();
    pix->load(":assets/cobble.png");
    textures[2] = pix;
}

bool TileMap::load(QString name)
{
    std::ifstream file(name.toStdString().c_str());
    if(file.is_open() == false) return false;
    if(!(file >> width)) return false;
    if(!(file >> height)) return false;
    map = new int*[height];
    for(int i = 0; i < height; ++i) {
        map[i] = new int[width];
    }
    for(int y=0; y<height; ++y) {
        for(int x=0; x<width; ++x) {
            if(!(file >> map[y][x])) return false;
        }
    }
    return true;
}

void TileMap::render(QPainter *p)
{
    QRect rect;
    rect.setWidth(16);
    rect.setHeight(16);
    for(int y=0; y<height; ++y) {
        for(int x=0; x<width; ++x) {
            rect.setX(x*16);
            rect.setY(y*16);
            if (p->window().contains(rect)) {
                int tileId = map[y][x];
                if (tileId == 0) continue;
                QPixmap *texture = textures[tileId];
                QBrush brush(*texture);
                p->fillRect(16 * x - offsetX, 16 * y - offsetY, 16, 16, brush);
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::onMousePressed(int x, int y, Qt::MouseButton button)
{

}

void TileMap::onMouseReleased(int x, int y, Qt::MouseButton button)
{

}

void TileMap::onMouseMove(int x, int y)
{

}
