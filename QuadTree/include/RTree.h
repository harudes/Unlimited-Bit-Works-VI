#ifndef RTREE_H
#define RTREE_H
#include <vector>
#include <math.h>
#include <Point.h>

using namespace std;

class RTree
{
    coordenada minX,maxX,minY,maxY;
    int m;
    vector<Point> points;
    vector<RTree*> branches;
    void ChooseLeaf();
    void Split();
    void AdjustTree();
    void FindLeaf();
    void CondenseTree();
    void PickSeeds();
    void PickNext();
public:
    RTree(int M);
    ~RTree();
    vector<Point> Search();
    void Insert();
    void Delete();
protected:

};

#endif // RTREE_H
