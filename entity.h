#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>
#include <QPainter>

class TileMap;

class Entity
{
public:
    Entity(TileMap*);
    void setX(int);
    int getX();
    void setY(int);
    int getY();
    int getWidth();
    int getHeight();
    QRect getBoundingBox();
    bool isDead();
    TileMap* getMap();
    virtual void updatePhysics();
    virtual void die();
    virtual void updateLogic();
    virtual QString getType();
    virtual void render(QPainter*);
    virtual void init();
protected:
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    float velocityX = 0;
    float velocityY = 0;
    float friction = 0.2f;
private:
    bool dead = false;
    TileMap* map;
};

#endif // ENTITY_H
