#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include "renderable.h"
#include <QPixmap>


class SimpleButton : public QObject, public Renderable
{
    Q_OBJECT

    QPixmap* idle;
    QPixmap* hover;
    QPixmap* pressed;
    QPixmap* state;
    QString text = NULL;
    int width = 190;
    int height = 50;

public:
    SimpleButton();
    SimpleButton(int width, int height);
    void render(QPainter *);
    void onMousePressed(int x, int y, Qt::MouseButton button);
    void onMouseReleased(int x, int y, Qt::MouseButton button);
    void onMouseMove(int x, int y);
    void setText(QString s);
    QString getText();
    int getWidth();
    int getHeight();

signals:
    void onClick();
};

#endif // SIMPLEBUTTON_H
