#include "mainmenustate.h"
#include "simplebutton.h"
#include "iostream"

#include "gamestate.h"

MainMenuState::MainMenuState()
{
}

QString MainMenuState::getName()
{
    return QString("MainMenu");
}

void MainMenuState::init()
{
    SimpleButton* play = new SimpleButton();
    play->setText("Play");
    play->setX(400 - play->getWidth()/2);
    play->setY(300 - (play->getHeight()/2 + 10));
    SimpleButton* exit = new SimpleButton();
    exit->setText("Exit");
    exit->setX(400 - exit->getWidth()/2);
    exit->setY(300 + (exit->getHeight()/2 + 10));
    renderables.push_back(play);
    renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
    connect(&*play, SIGNAL(onClick()), this, SLOT(onPlay()));
}

void MainMenuState::render(QPainter *)
{

}

void MainMenuState::update()
{

}

void MainMenuState::onKeyPressed(int)
{

}

void MainMenuState::onKeyReleased(int)
{

}

void MainMenuState::onMousePressed(int x, int y, Qt::MouseButton button)
{

}

void MainMenuState::onMouseReleased(int x, int y, Qt::MouseButton button)
{

}

void MainMenuState::onMouseMove(int x, int y)
{

}

void MainMenuState::onMouseScroll(QPoint angleDelta)
{

}

void MainMenuState::onExit()
{
    close = true;
}

void MainMenuState::onPlay()
{
    setState(new GameState());
}
