#include "gamestate.h"

#include "simplebutton.h"
#include "mainmenustate.h"
#include "player.h"

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
    exit->setText("Exit to main menu");
    exit->setX(400 - exit->getWidth()/2);
    exit->setY(300 - exit->getHeight()/2);
    escMenu->renderables.push_back(exit);
    connect(&*exit, SIGNAL(onClick()), this, SLOT(onExit()));
    map = new TileMap();
//    map->load("testMap.txt");
    map->generateMaze();
    pl = new Player(map);
    map->addEntity(pl);
}

void GameState::render(QPainter *p)
{
    QPixmap* rendered = new QPixmap(800/3, 600/3);
    rendered->fill(QColor(0, 0, 0));
    QPainter* np = new QPainter(rendered);
    map->render(np);
    p->drawPixmap(p->window(), *rendered, rendered->rect());
    delete np;
    delete rendered;
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
    else {
        map->update();
        map->offsetX = 400/3 - pl->getX();
        map->offsetY = 300/3 - pl->getY();
    }
}

void GameState::onKeyPressed(int keycode)
{
    (*map->keys)[keycode] = true;
}

void GameState::onKeyReleased(int keycode)
{
    (*map->keys)[keycode] = false;
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
    else {
        //debug teleport
        pl->setX(x/3);
        pl->setY(y/3);
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
