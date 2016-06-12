#include "player.h"
#include "tilemap.h"

Player::Player(TileMap *m):Entity(m)
{
    width = 13;
    height = 13;
    arrow = new QPixmap(":assets/arrow.png");
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
    p->fillRect(x + getMap()->offsetX, y + getMap()->offsetY, width, height, QBrush(QColor(255, 0, 0)));
}

void Player::init()
{

}
