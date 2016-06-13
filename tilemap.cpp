#include "tilemap.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <list>
#include <QDebug>
#include "pathfinder.h"
#include "gamestate.h"

int TileMap::getGround()
{
    return (rand() % 6) + 4;
}

int TileMap::getWall()
{
    return (rand() % 3) + 1;
}

void TileMap::registerTile(int id, QString texture)
{
    QPixmap* pix = new QPixmap();
    pix->load(":assets/" + texture);
    textures[id] = pix;
}

TileMap::TileMap(GameState *g)
{
    registerTile(1, "1.png");
    registerTile(2, "2.png");
    registerTile(3, "3.png");
    registerTile(4, "1a.png");
    registerTile(5, "1b.png");
    registerTile(6, "1c.png");
    registerTile(7, "1aa.png");
    registerTile(8, "1bb.png");
    registerTile(9, "1cc.png");
    registerTile(10, "klapa.png");
    game = g;
}

TileMap::~TileMap()
{
    for(int i = 0; i < height; ++i)
        delete [] map[i];
    delete [] map;
    for (std::map<int, QPixmap*>::iterator i = textures.begin();i != textures.end();i++) {
        delete i->second;
    }
    for (std::list<Entity*>::iterator i = entities.begin();i != entities.end();i++) {
        Entity *ent = dynamic_cast<Entity*>(*&*i);
        delete ent;
    }
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
    finder = new Pathfinder(this);
    return true;
}
//Code from http://www.roguebasin.com/index.php?title=Simple_maze and modified to our needs
void TileMap::generateMaze(int mazeWidth, int mazeHeight, bool easy) {
    qDebug() << "Generating maze " << mazeWidth << "x" << mazeHeight << " with difficulty: " << (easy ? "easy" : "hard");
    srand(time(0));
    width=mazeWidth;
    height=mazeHeight;
    map = new int*[height+2];
    for(int i = 0; i < height+2; ++i) {
        map[i] = new int[width+2];
    }
    std::list<std::pair<int, int>> drillers;
    for (size_t x=0;x<width+2;x++)
        for (size_t y=0;y<height+2;y++)
            map[y][x]=getWall();

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
                if ((*m).second<0 || isWalkable(map[(*m).second+1][(*m).first+1]))
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second+2][(*m).first+1]=getGround();
                break;
            case 1:
                (*m).second+=2;
                if ((*m).second>=height-2 || isWalkable(map[(*m).second+1][(*m).first+1]))
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second][(*m).first+1]=getGround();
                break;
            case 2:
                (*m).first-=2;
                if ((*m).first<0 || isWalkable(map[(*m).second+1][(*m).first+1]))
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second+1][(*m).first+2]=getGround();
                break;
            case 3:
                (*m).first+=2;
                if ((*m).first>=width-2 || isWalkable(map[(*m).second+1][(*m).first+1]))
                {
                    remove_driller=true;
                    break;
                }
                map[(*m).second+1][(*m).first]=getGround();
                break;
            }
            if (remove_driller)
                m = drillers.erase(m);
            else
            {
                drillers.push_back(std::make_pair((*m).first,(*m).second));
                if (rand()%2 && easy)
                    drillers.push_back(std::make_pair((*m).first,(*m).second));
                else if (!easy)
                    drillers.push_back(std::make_pair((*m).first,(*m).second));
                map[(*m).second+1][(*m).first+1]=getGround();
                ++m;
            }
        }
    }
    width += 2;
    height += 2;
    for(int y=1; y<height-1; ++y) {
        for(int x=1; x<width-1; ++x) {
            if (isWalkable(x, y)) {
                if (minX * minY > x * y) {
                    minX = x;
                    minY = y;
                }
                else if (maxX * maxY < x * y) {
                    maxX = x;
                    maxY = y;
                }
            }
        }
    }
    map[maxY][maxX] = 10;
//    map[minY][minX] = 0;

    finder = new Pathfinder(this);
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

bool TileMap::isWalkable(int id)
{
    switch (id) {
    case 0:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        return true;
    case 1:
    case 2:
    case 3:
        return false;
    }
}

bool TileMap::isWalkable(int x, int y)
{
    return isWalkable(getTile(x, y));
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
    e->init();
}

int TileMap::getTile(int x, int y)
{
    if (y >= height) return 0;
    if (x >= width) return 0;
    if (y < 0) return 0;
    if (x < 0) return 0;
    return map[y][x];
}

bool TileMap::isKeyDown(int keycode)
{
    return (*keys)[keycode];
}

int TileMap::getWidth()
{
    return width;
}

int TileMap::getHeight()
{
    return height;
}

Pathfinder *TileMap::getPathfinder()
{
    return finder;
}

GameState *TileMap::getGameState()
{
    return game;
}

Entity *TileMap::collides(Entity *e)
{
    QRect box = e->getBoundingBox();
    for (std::list<Entity*>::iterator i = entities.begin();i != entities.end();i++) {
        Entity *ent = dynamic_cast<Entity*>(*&*i);
        if (ent != e) {
            if (contains(box, ent->getBoundingBox())) return ent;
        }
    }
    return NULL;
}
