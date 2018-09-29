#ifndef POINT_H
#define POINT_H
#include <iostream>
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

ostream& operator<<(ostream& os, Point p);

bool operator==(Point u, Point v);

#endif // POINT_H
