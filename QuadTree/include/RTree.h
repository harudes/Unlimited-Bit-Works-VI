#ifndef RTREE_H
#define RTREE_H
#include <vector>
#include <math.h>
#include <Point.h>
#include <Rectangle.h>
#include <queue>
#include <iostream>

using namespace std;

class RTree
{
    rectangle space;
    int M;
    RTree* P;
    vector<Point> points;
    vector<RTree*> branches;
    RTree* ChooseLeaf(Point E);
    RTree* SplitLeaf();
    RTree* SplitBranch();
    void SplitRoot();
    void InsertPoint(Point E);
    void InsertBranch(RTree* N);
    void Enlarge(Point E);
    void Enlarge(rectangle R);
    void AdjustTree(RTree* NN, RTree* Root);
    void AdjustTree(Point E);
    void FindLeaf();
    void CondenseTree();
    void FillLeaf(RTree *N, vector<bool> &flags);
    void FillBranch(RTree *N, vector<bool> &flags);
    void PickSeeds(Point &E1, Point &E2, vector<bool> &flags);
    void PickSeeds(RTree *&E1, RTree *&E2, vector<bool> &flags);
    void PickNext(RTree* N, RTree* NN,vector<bool> &flags);
    void PickNextBranch(RTree* N, RTree* NN,vector<bool> &flags);
public:
    RTree(int m);
    RTree(RTree* p, int m);
    ~RTree();
    vector<Point> Search();
    void Insert(coordenada a, coordenada b);
    void Delete();
    vector<Point> getPoints();
	vector<Line> getLines();
};

#endif // RTREE_H
