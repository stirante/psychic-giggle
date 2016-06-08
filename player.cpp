#include "player.h"
#include "tilemap.h"

Player::Player(TileMap *m):Entity(m)
{
    width = 13;
    height = 13;
    x = 5 * 16;
    y = 5 * 16;
}

void Player::die()
{

}

void Player::updateLogic()
{
    if ((*(getMap()->keys))[Qt::Key_Up]) {
        velocityY -= speed;
    }
    else if ((*(getMap()->keys))[Qt::Key_Down]) {
        velocityY += speed;
    }
    if ((*(getMap()->keys))[Qt::Key_Right]) {
        velocityX += speed;
    }
    else if ((*(getMap()->keys))[Qt::Key_Left]) {
        velocityX -= speed;
    }
}

QString Player::getType()
{
    return QString("Player");
}

void Player::render(QPainter *p)
{
    p->fillRect(x + getMap()->offsetX, y + getMap()->offsetY, width, height, QBrush(QColor(255, 0, 0)));
}

void Player::init()
{

}
