#ifndef GAME_H
#define GAME_H

#include <QWidget>

class Game : public QWidget
{
    Q_OBJECT
    bool running = true;
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
};

#endif // GAME_H
