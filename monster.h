#ifndef MONSTER_H
#define MONSTER_H

#include "tilemap.h"

class Monster : public Entity
{
    int xChange, yChange, lastX, lastY, counter;
    int texIndex = 0;
    QPixmap* texture1;
    QPixmap* texture2;
    int dir = 0;
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
