#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QPainter>
#include "renderable.h"

class State
{
public:
    State();
    virtual QString getName();
    virtual void init();
    virtual void render(QPainter *);
    virtual void update();
    virtual void onKeyPressed(int);
    virtual void onKeyReleased(int);
    virtual void onMousePressed(int x, int y, Qt::MouseButton button);
    virtual void onMouseReleased(int x, int y, Qt::MouseButton button);
    virtual void onMouseMove(int x, int y);
    virtual void onMouseScroll(QPoint angleDelta);

    void internal_render(QPainter *);
    void internal_update();
    void internal_onKeyPressed(int);
    void internal_onKeyReleased(int);
    void internal_onMousePressed(int x, int y, Qt::MouseButton button);
    void internal_onMouseReleased(int x, int y, Qt::MouseButton button);
    void internal_onMouseMove(int x, int y);
    void internal_onMouseScroll(QPoint angleDelta);
    void internal_init();


protected:
    std::list<Renderable*> renderables;
};

#endif // STATE_H
