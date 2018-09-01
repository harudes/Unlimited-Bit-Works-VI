#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>

using namespace std;

class Point{
    int x;
    int y;
public:
    Point(int a, int b);
    int getX();
    int getY();
};

class QuadTree{
    int maxPoints,minX,maxX,minY,maxY;
    QuadTree* regions[4];
    vector<Point> points;
public:
    QuadTree(int xMin, int xMax, int yMin, int yMax, int maxP);
    void insertPoint(int x, int y);
    ~QuadTree();
};

#endif // QUADTREE_H
