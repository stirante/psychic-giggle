#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "pathnode.h"
#include "tilemap.h"

class Pathfinder
{
    TileMap* map;
    int** closed_nodes_map;
    int** open_nodes_map;
    int** dir_map;
    static const int dx[4];
    static const int dy[4];
public:
    Pathfinder(TileMap*);
    QString findPath(int, int, int, int);
    static int translateX(int index, int x, QString path);
    static int translateY(int index, int y, QString path);
};

#endif // PATHFINDER_H
