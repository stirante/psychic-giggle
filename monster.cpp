#include "monster.h"
#include "gamestate.h"
#include "player.h"
#include <QDebug>

Monster::Monster(TileMap *m):Entity(m)
{
    width = 13;
    height = 13;
    texture1 = new QPixmap(":assets/wrog.png");
    texture2 = new QPixmap(":assets/wrog2.png");
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
    if (counter >= 2) {
        counter = 0;
        setX(getX() + xChange);
        setY(getY() + yChange);
    }
    texIndex++;
    if (texIndex >= 32) texIndex = 0;
    if (xChange > 0) {
        dir = 1;
    }
    else if (xChange < 0) {
        dir = 3;
    }
    if (yChange > 0) {
        dir = 2;
    }
    if (yChange < 0) {
        dir = 0;
    }
}

QString Monster::getType()
{
    return QString("Monster");
}

void Monster::render(QPainter *p)
{
    QPixmap* tx = texIndex > 8 ? texture1 : texture2;
    QPixmap tex = tx->transformed(QTransform()
                                .translate(-width/2, -height/2)
                                .rotate(dir*90)
                                .translate(width/2, height/2));
    p->drawPixmap(getX() + getMap()->offsetX, getY() + getMap()->offsetY, tex);
}

void Monster::init()
{
    counter = 0;
}

void Monster::updatePhysics()
{

}
