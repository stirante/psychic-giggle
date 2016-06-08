#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
    float speed = 20;
public:
    Player(TileMap*);
    void die();
    void updateLogic();
    QString getType();
    void render(QPainter*);
    void init();
};

#endif // PLAYER_H
