#include "player.h"
#include "tilemap.h"

Player::Player(TileMap *m):Entity(m)
{
    width = 13;
    height = 13;
}

Player::~Player()
{

}

void Player::die()
{

}

void Player::updateLogic()
{
    if (getMap()->isKeyDown(Qt::Key_Up)) {
        velocityY -= speed;
    }
    else if (getMap()->isKeyDown(Qt::Key_Down)) {
        velocityY += speed;
    }
    if (getMap()->isKeyDown(Qt::Key_Right)) {
        velocityX += speed;
    }
    else if (getMap()->isKeyDown(Qt::Key_Left)) {
        velocityX -= speed;
    }
    QRect finish(getMap()->maxX*16, getMap()->maxY*16, 16, 16);
    if (getMap()->contains(finish, getBoundingBox())) {
        changeMap = true;
    }
}

QString Player::getType()
{
    return QString("Player");
}

void Player::render(QPainter *p)
{
    int x = startX;
    int y = startY;
    for (int i = 0; i < path.length()-1;i++) {
        x = Pathfinder::translateX(i, x, path);
        y = Pathfinder::translateY(i, y, path);
        p->fillRect(x*16 + getMap()->offsetX, y*16 + getMap()->offsetY, 16, 16, QBrush(QColor(0, 0, 255)));
    }
    p->fillRect(getX() + getMap()->offsetX, getY() + getMap()->offsetY, width, height, QBrush(QColor(0, 255, 0)));
}

void Player::init()
{
    startX = getX()/16;
    startY = getY()/16;
    path = getMap()->getPathfinder()->findPath(startX, startY, getMap()->maxX, getMap()->maxY);
}
