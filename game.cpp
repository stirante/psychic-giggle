#include "game.h"
#include <QtWidgets>
#include "state.h"
#include "mainmenustate.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Starting psychic-giggle v1.0";
    setWindowTitle("Psychic Giggle");
    setMinimumSize(800, 600);
    setMouseTracking(true);
    int id = QFontDatabase::addApplicationFont(":/assets/Endless Boss Battle.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    QApplication::setFont(font);
    setState(new MainMenuState());
}

Game::~Game()
{

}

void Game::update()
{
    if (state != NULL) {
        state->internal_update();
        if (state->state != NULL)
            setState(state->state);
        if (state->close)
            close();
    }
}

void Game::render()
{
    repaint();
}



bool Game::isRunning()
{
    return running;
}

void Game::closeEvent (QCloseEvent *)
{
    running = false;
}

void Game::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, false);
    painter.setRenderHint(QPainter::TextAntialiasing, false);
    painter.fillRect(0, 0, 800, 600, QBrush(QColor(0, 0, 0)));
    if (state != NULL) {
        state->internal_render(&painter);
    }
}

void Game::mousePressEvent(QMouseEvent *e)
{
    if (state != NULL) {
        state->internal_onMousePressed(e->x() > 0 ? e->x() : 0, e->y() > 0 ? e->y() : 0, e->button());
    }
}

void Game::mouseReleaseEvent(QMouseEvent *e)
{
    if (state != NULL) {
        state->internal_onMouseReleased(e->x() > 0 ? e->x() : 0, e->y() > 0 ? e->y() : 0, e->button());
    }
}

void Game::mouseMoveEvent(QMouseEvent *e)
{
    if (state != NULL) {
        state->internal_onMouseMove(e->x() > 0 ? e->x() : 0, e->y() > 0 ? e->y() : 0);
    }
}

void Game::wheelEvent(QWheelEvent *e)
{
    if (state != NULL) {
        state->internal_onMouseScroll(e->angleDelta());
    }
}

void Game::keyPressEvent(QKeyEvent *e)
{
    if (state != NULL) {
        state->internal_onKeyPressed(e->key());
    }
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_F2) {
        QPixmap screen = grab();
        QFile file("screenshot-" + QDateTime::currentDateTime().toString(Qt::ISODate) + ".png");
        file.open(QIODevice::WriteOnly);
        screen.save(&file, "PNG");
        file.flush();
        file.close();
        qDebug() << QFileInfo(file).absoluteFilePath();
    }
    if (state != NULL) {
        state->internal_onKeyReleased(e->key());
    }
}

void Game::setState(State *s)
{
    qDebug() << "Changed state to " + s->getName();
    state = s;
    s->init();
}
