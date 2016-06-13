#include "pathfinder.h"
#include <queue>

//Using havily modified version of A* algorithm implementation from http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/

const int Pathfinder::dx[4]={1, 0, -1, 0};
const int Pathfinder::dy[4]={0, 1, 0, -1};

Pathfinder::Pathfinder(TileMap *m)
{
    map = m;
    closed_nodes_map = new int*[map->getWidth()];
    for(int i = 0; i < map->getWidth(); ++i) {
        closed_nodes_map[i] = new int[map->getHeight()];
    }
    open_nodes_map = new int*[map->getWidth()];
    for(int i = 0; i < map->getWidth(); ++i) {
        open_nodes_map[i] = new int[map->getHeight()];
    }
    dir_map = new int*[map->getWidth()];
    for(int i = 0; i < map->getWidth(); ++i) {
        dir_map[i] = new int[map->getHeight()];
    }
}

QString Pathfinder::findPath(int xStart, int yStart, int xFinish, int yFinish)
{
    std::priority_queue<PathNode> pq[2];
    int pqi;
    PathNode* n0;
    PathNode* m0;
    int i, j, x, y, xdx, ydy;
    char c;
    pqi=0;

    for(y=0;y<map->getHeight();y++)
    {
        for(x=0;x<map->getWidth();x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    n0=new PathNode(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[xStart][yStart]=n0->getPriority();

    while(!pq[pqi].empty())
    {
        n0=new PathNode( pq[pqi].top().getX(), pq[pqi].top().getY(),
                         pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getX(); y=n0->getY();

        pq[pqi].pop();
        open_nodes_map[x][y]=0;
        closed_nodes_map[x][y]=1;

        if(x==xFinish && y==yFinish)
        {
            QString path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+4/2)%4;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            delete n0;
            while(!pq[pqi].empty()) pq[pqi].pop();
            return path;
        }

        for(i=0;i<4;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>map->getWidth()-1 || ydy<0 || ydy>map->getHeight()-1 || !map->isWalkable(xdx, ydy)
                 || closed_nodes_map[xdx][ydy]==1))
            {
                m0=new PathNode( xdx, ydy, n0->getLevel(),
                                 n0->getPriority());
                m0->nextLevel();
                m0->updatePriority(xFinish, yFinish);

                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    dir_map[xdx][ydy]=(i+4/2)%4;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    dir_map[xdx][ydy]=(i+4/2)%4;

                    while(!(pq[pqi].top().getX()==xdx &&
                            pq[pqi].top().getY()==ydy))
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop();

                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0);
                }
                else delete m0;
            }
        }
        delete n0;
    }
    return QString("");
}

int Pathfinder::translateX(int index, int x, QString path)
{
    if (path.length() <= index) return x;
    char c = path.toStdString().at(index);
    int j=std::atoi(&c);
    x=x+dx[j];
    return x;
}

int Pathfinder::translateY(int index, int y, QString path)
{
    if (path.length() <= index) return y;
    char c = path.toStdString().at(index);
    int j=std::atoi(&c);
    y=y+dy[j];
    return y;
}
