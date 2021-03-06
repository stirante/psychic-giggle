#ifndef RENDERABLEGROUP_H
#define RENDERABLEGROUP_H

#include <QPainter>

class Renderable;

class RenderableGroup
{
public:
    RenderableGroup();
    virtual void render(QPainter *);
    virtual void update();
    virtual void onMousePressed(int x, int y, Qt::MouseButton button);
    virtual void onMouseReleased(int x, int y, Qt::MouseButton button);
    virtual void onMouseMove(int x, int y);
    std::list<Renderable*> renderables;
};

#endif // RENDERABLEGROUP_H
