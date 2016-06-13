#include "fadeelement.h"
#include <QDebug>

FadeElement::FadeElement()
{

}
FadeElement::FadeElement(int w, int h)
{
    width = w;
    height = h;
}

void FadeElement::setWidth(int w)
{
    width = w;
}

void FadeElement::setHeight(int h)
{
    height = h;
}

void FadeElement::setTime(int t)
{
    time = t;
    step = 255.0f/(float)t;
}

void FadeElement::setToTransparent(bool t)
{
    toTransparent = t;
    if (t) progress = 255;
    else progress = 0;
}

void FadeElement::start()
{
    started = true;
    //myTimer.start();
}

void FadeElement::render(QPainter *p)
{
    if (started) {
//        if (!test) {
//            myTimer.start();
//            test = !test;
//        }
//        else {
//            int nMilliseconds = myTimer.elapsed();
//            myTimer.restart();
//            qDebug() << "It took " << nMilliseconds;
//        }
        if (toTransparent) progress -= step;
        else progress += step;
        if (progress > 255) progress = 255;
        if (progress < 0) progress = 0;
        time--;
        if (time < 0) {
            started = false;
            emit onEnd();
        }
    }
    int w = width;
    int h = height;
    if (w < 0) w = p->window().width();
    if (h < 0) h = p->window().height();
    p->fillRect(getX(), getY(), w, h, QBrush(QColor(0, 0, 0, (int)progress)));
}
