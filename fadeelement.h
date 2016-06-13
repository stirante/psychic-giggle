#ifndef FADEELEMENT_H
#define FADEELEMENT_H

#include "renderable.h"
#include <QTime>

class FadeElement : public QObject, public Renderable
{
    Q_OBJECT

    int width = -1;
    int height = -1;
    bool started;
    bool toTransparent;
    float progress = 0.0f;
    int time;
    float step;
    QTime myTimer;
    bool test = false;
public:
    FadeElement();
    FadeElement(int, int);
    void setWidth(int);
    void setHeight(int);
    void setTime(int);
    void setToTransparent(bool);
    void start();
    void render(QPainter *);
signals:
    void onEnd();
};

#endif // FADEELEMENT_H
