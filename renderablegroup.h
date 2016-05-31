#ifndef RENDERABLEGROUP_H
#define RENDERABLEGROUP_H

#include <QPainter>

class Renderable;

class RenderableGroup
{
    std::list<Renderable*> renderables;
public:
    RenderableGroup();
    virtual void render(QPainter *);
    virtual void update();
    virtual void onMousePressed(int x, int y, Qt::MouseButton button);
    virtual void onMouseReleased(int x, int y, Qt::MouseButton button);
    virtual void onMouseMove(int x, int y);
};

#endif // RENDERABLEGROUP_H
