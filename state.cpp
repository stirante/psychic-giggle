#include "state.h"

State::State()
{

}


QString State::getName()
{
    return QString("undefined");
}

void State::init()
{

}

void State::render(QPainter *)
{

}

void State::update()
{

}

void State::onKeyPressed(int)
{

}

void State::onKeyReleased(int)
{

}

void State::onMousePressed(int, int, Qt::MouseButton)
{

}

void State::onMouseReleased(int, int, Qt::MouseButton)
{

}

void State::onMouseMove(int, int)
{

}

void State::onMouseScroll(QPoint)
{

}

void State::internal_render(QPainter * painter)
{
    render(painter);
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->render(painter);
    }
}

void State::internal_update()
{
    update();
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->update();
    }
}

void State::internal_onKeyPressed(int key)
{
    onKeyPressed(key);
}

void State::internal_onKeyReleased(int key)
{
    onKeyReleased(key);
}

void State::internal_onMousePressed(int x, int y, Qt::MouseButton button)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMousePressed(x, y, button);
    }
    onMousePressed(x, y, button);
}

void State::internal_onMouseReleased(int x, int y, Qt::MouseButton button)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMouseReleased(x, y, button);
    }
    onMouseReleased(x, y, button);
}

void State::internal_onMouseMove(int x, int y)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMouseMove(x, y);
    }
    onMouseMove(x, y);
}

void State::internal_onMouseScroll(QPoint angleDelta)
{
    onMouseScroll(angleDelta);
}

void State::internal_init()
{
    init();
}
