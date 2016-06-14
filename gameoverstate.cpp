#include "gameoverstate.h"
#include "simplebutton.h"
#include "mainmenustate.h"

GameOverState::GameOverState()
{

}

QString GameOverState::getName()
{
    return QString("GameOver");
}

void GameOverState::init()
{
    SimpleButton* exit = new SimpleButton();
    exit->setText("Quit");
    exit->setX(400 - exit->getWidth()/2);
    exit->setY(350 + (exit->getHeight()/2 + 10));
    renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
    fade = new FadeElement();
    fade->setTime(150);
    fade->setToTransparent(true);
    renderables.push_back(fade);
    connect(&*fade, SIGNAL(onEnd()), this, SLOT(onFadeEnd()));
    fade->start();
}

void GameOverState::render(QPainter *p)
{
    p->setPen(Qt::white);
    QFont f = p->font();
    f.setPointSize(60);
    p->setFont(f);
    p->drawText(0, 0, 800, 300, Qt::AlignCenter, "GAME OVER");
}

void GameOverState::update()
{

}

void GameOverState::onKeyPressed(int)
{

}

void GameOverState::onKeyReleased(int)
{

}

void GameOverState::onMousePressed(int, int, Qt::MouseButton)
{

}

void GameOverState::onMouseReleased(int, int, Qt::MouseButton)
{

}

void GameOverState::onMouseMove(int, int)
{

}

void GameOverState::onMouseScroll(QPoint)
{

}

void GameOverState::onExit()
{
    exitClicked = true;
    fade->setTime(150);
    fade->setToTransparent(false);
    fade->start();
}

void GameOverState::onFadeEnd()
{
    if (exitClicked) setState(new MainMenuState());
}
