#include "game.h"
#include <QtWidgets>

Game::Game(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Psychic Giggle");
}

Game::~Game()
{

}

void Game::update()
{

}

void Game::render()
{

}

bool Game::isRunning()
{
    return running;
}

void Game::closeEvent (QCloseEvent *)
{
    running = false;
}
