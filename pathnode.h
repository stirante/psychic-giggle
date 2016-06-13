#ifndef PATHNODE_H
#define PATHNODE_H


class PathNode
{
    int x;
    int y;
    int level;
    int priority;
public:
    PathNode(int xp, int yp, int d, int p);
    int getX() const;
    int getY() const;
    int getLevel() const;
    int getPriority() const;
    void updatePriority(int xDest, int yDest);
    void nextLevel();
    int estimate(int xDest, int yDest);
    bool operator<(const PathNode& right) const;
};

#endif // PATHNODE_H
