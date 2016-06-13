#include "pathnode.h"
#include <math.h>

PathNode::PathNode(int xp, int yp, int d, int p)
{
    x = xp;
    y = yp;
    level = d;
    priority = p;
}

int PathNode::getX() const
{
    return x;
}

int PathNode::getY() const
{
    return y;
}

int PathNode::getLevel() const
{
    return level;
}

int PathNode::getPriority() const
{
    return priority;
}

void PathNode::updatePriority(int xDest, int yDest)
{
    priority=level+estimate(xDest, yDest)*10;
}

void PathNode::nextLevel()
{
    level+=10;
}

int PathNode::estimate(int xDest, int yDest)
{
    int xd, yd, d;
    xd=xDest-x;
    yd=yDest-y;
    d=static_cast<int>(sqrt(xd*xd+yd*yd));
    return d;
}

bool PathNode::operator<(const PathNode &right) const
{
    return this->getPriority() > right.getPriority();
}
//bool operator<(const PathNode a, const PathNode b)
//{
//    return a.getPriority() > b.getPriority();
//}
