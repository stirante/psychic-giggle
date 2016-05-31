#include "renderable.h"

int Renderable::getX()
{
    return x;
}

void Renderable::setX(int value)
{
    x = value;
}

int Renderable::getY()
{
    return y;
}

void Renderable::setY(int value)
{
    y = value;
}

Renderable::Renderable()
{

}

void Renderable::render(QPainter *)
{

}

void Renderable::update()
{

}

void Renderable::onMousePressed(int, int, Qt::MouseButton)
{

}

void Renderable::onMouseReleased(int, int, Qt::MouseButton)
{

}

void Renderable::onMouseMove(int, int)
{

}
