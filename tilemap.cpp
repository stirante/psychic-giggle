#include "tilemap.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <list>

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

void TileMap::generateMaze() {
    srand(time(0));
    width=30;
    height=25;
    map = new int*[height];
    for(int i = 0; i < height; ++i) {
        map[i] = new int[width];
    }
    std::list<std::pair<int, int>> drillers;
    for (size_t x=0;x<width;x++)
        for (size_t y=0;y<height;y++)
            map[y][x]=1;

    drillers.push_back(std::make_pair(width/2,height/2));
    while(drillers.size()>0)
    {
        std::list<std::pair<int, int>>::iterator m,_m,temp;
        m=drillers.begin();
        _m=drillers.end();
        while (m!=_m)
        {
            bool remove_driller=false;
            switch(rand()%4)
            {
            case 0:
                (*m).second-=2;
                if ((*m).second<0 || map[(*m).second][(*m).first] == 0)
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second+1][(*m).first]=0;
                break;
            case 1:
                (*m).second+=2;
                if ((*m).second>=height || map[(*m).second][(*m).first] == 0)
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second-1][(*m).first]=0;
                break;
            case 2:
                (*m).first-=2;
                if ((*m).first<0 || map[(*m).second][(*m).first] == 0)
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second][(*m).first+1]=0;
                break;
            case 3:
                (*m).first+=2;
                if ((*m).first>=width || map[(*m).second][(*m).first] == 0)
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second][(*m).first-1]=0;
                break;
            }
            if (remove_driller)
                m = drillers.erase(m);
            else
            {
                drillers.push_back(std::make_pair((*m).first,(*m).second));
                // for easier maze
                //if (rand()%2)
                    drillers.push_back(std::make_pair((*m).first,(*m).second));

                map[(*m).second][(*m).first]=0;
                ++m;
            }
        }
    }
    loaded = true;
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
            rect.setX(x*16 + offsetX);
            rect.setY(y*16 + offsetY);
            rect.setWidth(16);
            rect.setHeight(16);
            if (contains(window, rect)) {
                QPixmap *texture = textures[tileId];
                p->drawPixmap(rect, *texture, texture->rect());
            }
        }
    }
    for (std::list<Entity*>::iterator i = entities.begin();i != entities.end();i++) {
        Entity *ent = dynamic_cast<Entity*>(*&*i);
        ent->render(p);
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
    for (std::list<Entity*>::iterator i = entities.begin();i != entities.end();i++) {
        Entity *ent = dynamic_cast<Entity*>(*&*i);
        ent->updateLogic();
        ent->updatePhysics();
    }
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

void TileMap::addEntity(Entity *e)
{
    entities.push_back(e);
}

int TileMap::getTile(int x, int y)
{
    if (y >= height) return 0;
    if (x >= width) return 0;
    if (y < 0) return 0;
    if (x < 0) return 0;
    return map[y][x];
}
