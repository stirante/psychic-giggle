#include "monster.h"
#include "gamestate.h"
#include "player.h"
#include <QDebug>

Monster::Monster(TileMap *m):Entity(m)
{
    width = 14;
    height = 14;
}

Monster::~Monster()
{

}

void Monster::die()
{

}

void Monster::updateLogic()
{
    Player* pl = getMap()->getGameState()->getPlayer();
    int x = getX() / 16;
    int y = getY() / 16;
    if (x == (getX() + width)/16 && y == (getY() + height)/16) {
        if (lastY != y || lastX != x || (xChange == 0 && yChange == 0)) {
            lastX = x;
            lastY = y;
            QString path = getMap()->getPathfinder()->findPath(x, y, pl->getX()/16, pl->getY()/16);
            xChange = Pathfinder::translateX(0, x, path) - x;
            yChange = Pathfinder::translateY(0, y, path) - y;
        }
    }
    counter++;
    if (counter >= 5) {
        counter = 0;
        setX(getX() + xChange);
        setY(getY() + yChange);
    }
}

QString Monster::getType()
{
    return QString("Monster");
}

void Monster::render(QPainter *p)
{
    p->fillRect(getX() + getMap()->offsetX, getY() + getMap()->offsetY, width, height, QBrush(QColor(255, 0, 0)));
}

void Monster::init()
{
    counter = 0;
}

void Monster::updatePhysics()
{

}
