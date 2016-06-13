#include "simplebutton.h"
#include <QPainter>
#include <QColor>

int SimpleButton::getWidth()
{
    return width;
}

int SimpleButton::getHeight()
{
    return height;
}

SimpleButton::SimpleButton() : SimpleButton(190*1.5, 50*1.5)
{
}

SimpleButton::SimpleButton(int width, int height)
{
    this->width = width;
    this->height = height;
    idle = new QPixmap(width, height);
    idle->load(":assets/buttonIdle.png");
    hover = new QPixmap(width, height);
    hover->load(":assets/buttonHover.png");
    pressed = new QPixmap(width, height);
    pressed->load(":assets/buttonPress.png");
    state = idle;
}

void SimpleButton::render(QPainter * painter)
{
    painter->setPen(Qt::white);
    painter->drawPixmap(this->getX(), this->getY(), width, height, *state);
    if (text != NULL) {
        QFont font = painter->font();
        font.setPointSize(15);
        painter->setFont(font);
        painter->drawText(this->getX(), this->getY(), getWidth(), getHeight(), Qt::AlignCenter, text);
    }
}

void SimpleButton::onMousePressed(int x, int y, Qt::MouseButton)
{
    if (x >= getX() && y >= getY() && x <= getX() + getWidth() && y <= getY() + getHeight()) {
        state = pressed;
    }
}

void SimpleButton::onMouseReleased(int x, int y, Qt::MouseButton)
{
    if (x >= getX() && y >= getY() && x <= getX() + getWidth() && y <= getY() + getHeight()) {
        state = hover;
        emit onClick();
    }
    else {
        state = idle;
    }
}

void SimpleButton::onMouseMove(int x, int y)
{
    if (state != pressed && x >= getX() && y >= getY() && x <= getX() + getWidth() && y <= getY() + getHeight()) {
        state = hover;
    }
    else if (state == hover) {
        state = idle;
    }
}

void SimpleButton::setText(QString s)
{
    text = s;
}

QString SimpleButton::getText()
{
    return text;
}
