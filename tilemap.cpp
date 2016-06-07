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
    loaded = true;
    return true;
}

void TileMap::render(QPainter *p)
{
    if (!loaded) return;
    QRect window = p->window();
    QRect rect;
    for(int y=0; y<height; ++y) {
        for(int x=0; x<width; ++x) {
            int tileId = map[y][x];
            if (tileId == 0) continue;
            rect.setX(x*16 - offsetX);
            rect.setY(y*16 - offsetY);
            rect.setWidth(16);
            rect.setHeight(16);
            if (contains(window, rect)) {
                QPixmap *texture = textures[tileId];
                p->drawPixmap(rect, *texture, texture->rect());
            }
        }
    }
}

bool TileMap::contains(QRect rect1, QRect rect2)
{
    return rect1.contains(rect2.topLeft()) ||
            rect1.contains(rect2.topRight()) ||
            rect1.contains(rect2.bottomLeft()) ||
            rect1.contains(rect2.bottomRight());
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
