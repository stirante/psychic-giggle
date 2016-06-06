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

void GameState::init()
{
    escMenu = new RenderableGroup();
    SimpleButton* exit = new SimpleButton();
    exit->setText("Exit");
    exit->setX(400 - exit->getWidth()/2);
    exit->setY(300 - exit->getHeight()/2);
    escMenu->renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
}

void GameState::render(QPainter *p)
{
    p->drawText(400, 300, "This is game state");
    if (escClicked) {
        p->fillRect(p->window(), QBrush(QColor(0, 0, 0, 128)));
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
        escMenu->onMousePressed(x, y, button);
    }
}

void GameState::onMouseReleased(int x, int y, Qt::MouseButton button)
{

    if (escClicked) {
        escMenu->onMouseReleased(x, y, button);
    }
}

void GameState::onMouseMove(int x, int y)
{

    if (escClicked) {
        escMenu->onMouseMove(x, y);
    }
}

void GameState::onMouseScroll(QPoint angleDelta)
{

}

void GameState::onExit()
{
    setState(new MainMenuState());
}
