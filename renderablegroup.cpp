#include "renderablegroup.h"
#include "renderable.h"

RenderableGroup::RenderableGroup()
{

}

void RenderableGroup::onMousePressed(int x, int y, Qt::MouseButton button)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMousePressed(x, y, button);
    }
}

void RenderableGroup::onMouseReleased(int x, int y, Qt::MouseButton button)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMouseReleased(x, y, button);
    }
}

void RenderableGroup::onMouseMove(int x, int y)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->onMouseMove(x, y);
    }
}
void RenderableGroup::render(QPainter * painter)
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->render(painter);
    }
}

void RenderableGroup::update()
{
    for (std::list<Renderable*>::iterator iter = renderables.begin(); iter != renderables.end(); ++iter) {
        (*&*iter)->update();
    }
}
