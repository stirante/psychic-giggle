#include "entity.h"
#include "tilemap.h"

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
    velocityX *= 0.3;
    velocityY *= 0.3;
    if (velocityX < 0.05 && velocityX > -0.05) velocityX = 0;
    if (velocityY < 0.05 && velocityY > -0.05) velocityY = 0;
    x += velocityX;
    y += velocityY;
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


