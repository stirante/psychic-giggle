#include "gamestate.h"

#include "simplebutton.h"
#include "mainmenustate.h"

GameState::GameState()
{

}

QString GameState::getName()
{
    return QString("Game");
}
//temporary solution
qreal scale = 3.5;
int newHeight = 600/scale;
int newWidth = 800/scale;

void GameState::init()
{
    escMenu = new RenderableGroup();
    SimpleButton* exit = new SimpleButton();
    exit->setText("Exit to main menu");
    exit->setX((newWidth/2) - exit->getWidth()/2);
    exit->setY((newHeight/2) - exit->getHeight()/2);
    escMenu->renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
    map = new TileMap();
    map->load("testMap.txt");
}

void GameState::render(QPainter *p)
{
    p->scale(3.5, 3.5);
    QRect exposedRect = p->matrix().inverted().mapRect(p->window()).adjusted(-1, -1, 1, 1);
    map->render(p);
    if (escClicked) {
        p->fillRect(exposedRect, QBrush(QColor(0, 0, 0, 128)));
        escMenu->render(p);
    }
}

void GameState::update()
{
    if (escClicked) {
        escMenu->update();
    }
}

void GameState::onKeyPressed(int)
{

}

void GameState::onKeyReleased(int keycode)
{
    if (keycode == Qt::Key_Escape) {
        escClicked = !escClicked;
    }
}

void GameState::onMousePressed(int x, int y, Qt::MouseButton button)
{

    if (escClicked) {
        escMenu->onMousePressed(x/scale, y/scale, button);
    }
}

void GameState::onMouseReleased(int x, int y, Qt::MouseButton button)
{

    if (escClicked) {
        escMenu->onMouseReleased(x/scale, y/scale, button);
    }
}

void GameState::onMouseMove(int x, int y)
{

    if (escClicked) {
        escMenu->onMouseMove(x/scale, y/scale);
    }
}

void GameState::onMouseScroll(QPoint angleDelta)
{

}

void GameState::onExit()
{
    setState(new MainMenuState());
}
