#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include <math.h>
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

bool findPoint(vector<Point> vec, Point p);

float euclidean(float a, float b);

float euclidean(Point a, Point b);

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
	bool searchPoint(Point p, QuadTree *&qt);
	void insertPoint(Point p);
	void insertPoint(coordenada x, coordenada y);
	Point leftup();
	Point rightup();
	Point leftdown();
	Point rightdown();
	bool inRegion(Point punto, float distancia);
	vector<Point> cercanos(coordenada x, coordenada y, float radio);
	vector<Line> getLines();
	~QuadTree();
};


#endif // QUADTREE_H
