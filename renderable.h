#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <QPainter>
#include <Qt>

class Renderable
{
    int x = 0;
    int y = 0;
public:
    Renderable();
    virtual void render(QPainter *);
    virtual void update();
    virtual void onMousePressed(int x, int y, Qt::MouseButton button);
    virtual void onMouseReleased(int x, int y, Qt::MouseButton button);
    virtual void onMouseMove(int x, int y);
    int getX();
    void setX(int value);
    int getY();
    void setY(int value);
};

#endif // RENDERABLE_H
