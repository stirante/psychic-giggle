#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player(TileMap*);
    void die();
    void updateLogic();
    QString getType();
    void render(QPainter*);
    void init();
};

#endif // PLAYER_H
