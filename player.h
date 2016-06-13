#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <QPixmap>
#include "pathfinder.h"

class Player : public Entity
{
    float speed = 20;
//    int startX;
//    int startY;
//    QString path = "";
public:
    Player(TileMap*);
    ~Player();
    void die();
    void updateLogic();
    QString getType();
    void render(QPainter*);
    void init();
    bool changeMap = false;
};

#endif // PLAYER_H
