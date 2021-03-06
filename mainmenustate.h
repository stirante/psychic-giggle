#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"
#include "fadeelement.h"

class MainMenuState : public State
{
    Q_OBJECT

    FadeElement* fade;
    bool playClicked = false;
    bool exitClicked = false;
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
    void onPlay();
    void onFadeEnd();
};

#endif // MAINMENUSTATE_H
