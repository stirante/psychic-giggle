#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "state.h"

class Game : public QWidget
{
    Q_OBJECT
    bool running = true;
    State* state;
public:
    Game(QWidget *parent = 0);
    ~Game();
    /**
     * Base update method executed on every tick
     */
    void update();
    /**
     * Base rendering method
     */
    void render();
    /**
     * Returns true, if the game should be running
     * @return true, if the game should be running
     */
    bool isRunning();
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);

    //Events
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void setState(State*);
};

#endif // GAME_H
