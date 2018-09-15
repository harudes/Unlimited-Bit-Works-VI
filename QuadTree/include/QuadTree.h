#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
typedef float coordenada;

using namespace std;

class Point{
	coordenada x;
	coordenada y;
public:
	Point(coordenada a, coordenada b);
	coordenada getX();
	coordenada getY();
	int region(coordenada xMid, coordenada yMid);
};

struct Line{
    Line(Point a, Point b);
    Point u,v;
};

class QuadTree{
	coordenada minX,maxX,minY,maxY;
	coordenada midX,midY;
	int maxPoints;
	QuadTree* regions[4];
	vector<Point> points;
public:
	QuadTree(coordenada xMin, coordenada xMax, coordenada yMin, coordenada yMax, int maxP);
	QuadTree(Point leftup, Point rightdown, int maxP);
	void split();
	void insertPoint(Point p);
	void insertPoint(coordenada x, coordenada y);
	vector<Line> getLines();
	~QuadTree();
};


#endif // QUADTREE_H
