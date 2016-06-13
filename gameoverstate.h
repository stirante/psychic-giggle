#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "state.h"
#include "fadeelement.h"

class GameOverState : public State
{
    Q_OBJECT

    bool exitClicked = false;
    FadeElement* fade;
public:
    GameOverState();
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
    void onFadeEnd();
};

#endif // GAMEOVERSTATE_H
