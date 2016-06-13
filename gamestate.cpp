#include "gamestate.h"

#include "simplebutton.h"
#include "mainmenustate.h"
#include "player.h"
#include "monster.h"

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
    map = new TileMap(this);
    map->generateMaze(mazeWidth, mazeHeight, easy);
    pl = new Player(map);
    pl->setX(map->minX*16);
    pl->setY(map->minY*16);
    map->addEntity(pl);
    Monster* m = new Monster(map);
    m->setX(map->maxX*16);
    m->setY(map->maxY*16);
    map->addEntity(m);
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
        if (pl->changeMap) {
            delete map;
            if (!easy) {
                easy = !easy;
                mazeHeight += 5;
                mazeWidth += 5;
            }
            else {
                easy = !easy;
            }
            map = new TileMap(this);
            map->generateMaze(mazeWidth, mazeHeight, easy);
            pl = new Player(map);
            pl->setX(map->minX*16);
            pl->setY(map->minY*16);
            map->addEntity(pl);
            Monster* m = new Monster(map);
            m->setX(map->maxX*16);
            m->setY(map->maxY*16);
            map->addEntity(m);
        }
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
        //debug change map
        //        map = new TileMap();
        //        map->generateMaze(30, 25);
        //        pl = new Player(map);
        //        map->addEntity(pl);
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

Player *GameState::getPlayer()
{
    return pl;
}

void GameState::onExit()
{
    setState(new MainMenuState());
}
