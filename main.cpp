#include "game.h"
#include <QApplication>
#include <QTime>
/**
 * time in milliseconds between every tick (20 ticks per second)
 */
const int TICK_MS = 50;

int main(int argc, char *argv[])
{
    QTime lastUpdate = QTime::currentTime().addMSecs(-TICK_MS);
    QApplication a(argc, argv);
    Game w;
    w.show();
    while(w.isRunning()) {
        a.processEvents();
        QTime currentTime = QTime::currentTime();
        int timeSinceLastUpdate = lastUpdate.msecsTo(currentTime);
        while(timeSinceLastUpdate > TICK_MS){
            w.update();
            timeSinceLastUpdate -= TICK_MS;
            lastUpdate = currentTime;
        }
        w.render();
    }
    a.exit();
    return 0;
}
