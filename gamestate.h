#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include "state.h"
#include "renderablegroup.h"
#include "tilemap.h"
#include "map"

class Player;

class GameState : public State
{
    Q_OBJECT
    TileMap* map;
    bool escClicked = false;
    RenderableGroup* escMenu;
    Player* pl;
public:
    GameState();
    QString getName();
    void init();
    void render(QPainter *);
    void update();
    void onKeyPressed(int);
    void onKeyReleased(int);
    void onMousePressed(int x, int y, Qt::MouseButton button);
    void onMouseReleased(int x, int y, Qt::MouseButton button);
    void onMouseMove(int x, int y);
    void onMouseScroll(QPoint angleDelta);

public slots:
    void onExit();
};

#endif // GAMESTATE_H
