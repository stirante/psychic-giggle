#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <QPixmap>
#include "pathfinder.h"

class Player : public Entity
{
    float speed = 20;
    int texIndex = 0;
    QPixmap* texture1;
    QPixmap* texture2;
    int dir = 0;
    int cooldown = 0;
public:
    Player(TileMap*);
    ~Player();
    void die();
    void updateLogic();
    QString getType();
    void render(QPainter*);
    void init();
    bool changeMap = false;
    int health = 2;
};

#endif // PLAYER_H
