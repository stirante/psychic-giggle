#include "player.h"
#include "tilemap.h"

Player::Player(TileMap *m):Entity(m)
{

}

void Player::die()
{

}

void Player::updateLogic()
{
    if ((*(getMap()->keys))[Qt::Key_Up]) {
        velocityY -= 10;
    }
    else if ((*(getMap()->keys))[Qt::Key_Down]) {
        velocityY += 10;
    }
    if ((*(getMap()->keys))[Qt::Key_Right]) {
        velocityX += 10;
    }
    else if ((*(getMap()->keys))[Qt::Key_Left]) {
        velocityX -= 10;
    }
}

QString Player::getType()
{
    return QString("Player");
}

void Player::render(QPainter *p)
{
    p->fillRect(x + getMap()->offsetX, y + getMap()->offsetY, 16, 16, QBrush(QColor(255, 0, 0)));
}

void Player::init()
{

}
