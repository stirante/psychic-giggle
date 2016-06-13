#ifndef MONSTER_H
#define MONSTER_H

#include "tilemap.h"

class Monster : public Entity
{
    int xChange, yChange, lastX, lastY, counter;
public:
    Monster(TileMap*);
    ~Monster();
    void die();
    void updateLogic();
    QString getType();
    void render(QPainter*);
    void init();
    void updatePhysics();
};

#endif // MONSTER_H
