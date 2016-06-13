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
    play->setText("Start");
    play->setX(400 - play->getWidth()/2);
    play->setY(350 - (play->getHeight()/2 + 10));
    SimpleButton* exit = new SimpleButton();
    exit->setText("Quit");
    exit->setX(400 - exit->getWidth()/2);
    exit->setY(350 + (exit->getHeight()/2 + 10));
    renderables.push_back(play);
    renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
    connect(&*play, SIGNAL(onClick()), this, SLOT(onPlay()));
    fade = new FadeElement();
    fade->setTime(150);
    fade->setToTransparent(true);
    renderables.push_back(fade);
    connect(&*fade, SIGNAL(onEnd()), this, SLOT(onFadeEnd()));
    fade->start();
}

void MainMenuState::render(QPainter *p)
{
    p->setPen(Qt::white);
    QFont f = p->font();
    f.setPointSize(60);
    p->setFont(f);
    p->drawText(0, 0, 800, 300, Qt::AlignCenter, "psychic giggle");
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

void MainMenuState::onMousePressed(int, int, Qt::MouseButton)
{

}

void MainMenuState::onMouseReleased(int, int, Qt::MouseButton)
{

}

void MainMenuState::onMouseMove(int, int)
{

}

void MainMenuState::onMouseScroll(QPoint)
{

}

void MainMenuState::onExit()
{
    exitClicked = true;
    fade->setTime(150);
    fade->setToTransparent(false);
    fade->start();
}

void MainMenuState::onPlay()
{
    playClicked = true;
    fade->setTime(150);
    fade->setToTransparent(false);
    fade->start();
}

void MainMenuState::onFadeEnd()
{
    if (playClicked) setState(new GameState());
    if (exitClicked) close = true;
}
