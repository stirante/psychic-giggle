#include "entity.h"
#include "tilemap.h"
#include <QDebug>

Entity::Entity(TileMap*m)
{
    map = m;
}

void Entity::setX(int x)
{
    this->x = x;
}

int Entity::getX()
{
    return x;
}

void Entity::setY(int y)
{
    this->y = y;
}

int Entity::getY()
{
    return y;
}

int Entity::getHeight()
{
    return height;
}

QRect Entity::getBoundingBox()
{
    return QRect(x, y, width, height);
}

bool Entity::isDead()
{
    return dead;
}

TileMap *Entity::getMap()
{
    return map;
}

void Entity::updatePhysics()
{
    velocityX *= friction;
    if (velocityX < 0.05 && velocityX > -0.05) velocityX = 0;
    x += velocityX;
    //horizontal collisions
    QRect testRect;
    QRect entityRect = getBoundingBox();
    bool done = false;
    for (int tx = (x/16)-1;tx <= (x/16)+1;tx++) {
        for (int ty = (y/16)-1;ty <= (y/16)+1;ty++) {
            if (getMap()->isWalkable(tx, ty)) continue;
            testRect.setX(tx * 16);
            testRect.setY(ty * 16);
            testRect.setWidth(16);
            testRect.setHeight(16);
            if (getMap()->contains(testRect, entityRect)) {
                if (velocityX > 0) {
                    x = testRect.left() - width;
                }
                else {
                    x = testRect.right() + 1;
                }
                done = true;
                break;
            }
        }
        if (done) break;
    }
    done = false;
    velocityY *= friction;
    if (velocityY < 0.05 && velocityY > -0.05) velocityY = 0;
    y += velocityY;
    //vertical collisions
    entityRect = getBoundingBox();
    for (int tx = (x/16)-1;tx <= (x/16)+1;tx++) {
        for (int ty = (y/16)-1;ty <= (y/16)+1;ty++) {
            if (getMap()->isWalkable(tx, ty)) continue;
            testRect.setX(tx * 16);
            testRect.setY(ty * 16);
            testRect.setWidth(16);
            testRect.setHeight(16);
            if (getMap()->contains(testRect, entityRect)) {
                if (velocityY > 0) {
                    y = testRect.top() - height;
                }
                else {
                    y = testRect.bottom() + 1;
                }
                done = true;
                break;
            }
        }
        if (done) break;
    }
}

void Entity::die()
{
    dead = true;
}

void Entity::updateLogic()
{

}

QString Entity::getType()
{
    return QString("UNKNOWN");
}

void Entity::render(QPainter *)
{

}

void Entity::init()
{

}


