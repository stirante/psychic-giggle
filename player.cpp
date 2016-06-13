#include "player.h"
#include "tilemap.h"

Player::Player(TileMap *m):Entity(m)
{
    width = 13;
    height = 13;
    texture1 = new QPixmap(":assets/gracz.png");
    texture2 = new QPixmap(":assets/gracz2.png");
}

Player::~Player()
{
    delete texture1;
    delete texture2;
}

void Player::die()
{

}

void Player::updateLogic()
{
    if (cooldown > 0) cooldown--;
    if (velocityX != 0 || velocityY != 0)
        texIndex++;
    if (texIndex >= 16) texIndex = 0;
    if (getMap()->isKeyDown(Qt::Key_Up)) {
        velocityY -= speed;
        dir = 0;
    }
    else if (getMap()->isKeyDown(Qt::Key_Down)) {
        velocityY += speed;
        dir = 2;
    }
    if (getMap()->isKeyDown(Qt::Key_Right)) {
        velocityX += speed;
        dir = 1;
    }
    else if (getMap()->isKeyDown(Qt::Key_Left)) {
        velocityX -= speed;
        dir = 3;
    }
    QRect finish(getMap()->maxX*16, getMap()->maxY*16, 16, 16);
    if (getMap()->contains(finish, getBoundingBox())) {
        changeMap = true;
    }
    if (cooldown <= 0) {
        if (getMap()->collides(this) != NULL) {
            cooldown = 20;
            health--;
            if (health <= 0) die();
        }
    }
}

QString Player::getType()
{
    return QString("Player");
}

void Player::render(QPainter *p)
{
    QPixmap* tx = texIndex > 8 ? texture1 : texture2;
    QPixmap tex = tx->transformed(QTransform()
                                  .translate(-width/2, -height/2)
                                  .rotate(dir*90)
                                  .translate(width/2, height/2));
    p->drawPixmap(getX() + getMap()->offsetX, getY() + getMap()->offsetY, tex);
}

void Player::init()
{

}
