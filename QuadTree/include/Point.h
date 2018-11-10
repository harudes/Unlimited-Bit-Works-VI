#ifndef POINT_H
#define POINT_H
#include <iostream>

using namespace std;

typedef float coordenada;

class Point{

public:
	coordenada x;
	coordenada y;
	Point(coordenada a, coordenada b);
	Point();
	coordenada getX();
	coordenada getY();
	int region(coordenada xMid, coordenada yMid);
};

ostream& operator<<(ostream& os, Point p);

bool operator==(Point a, Point b);

bool operator!=(Point a, Point b);

struct Line{
    Line(Point a, Point b);
    Point u,v;
};

#endif // POINT_H
