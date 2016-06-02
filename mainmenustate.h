#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"

class MainMenuState : public State
{
    Q_OBJECT

public:
    MainMenuState();
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

#endif // MAINMENUSTATE_H
