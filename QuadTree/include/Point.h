#ifndef POINT_H
#define POINT_H

typedef float coordenada;

class Point{
	coordenada x;
	coordenada y;
public:
	Point(coordenada a, coordenada b);
	coordenada getX();
	coordenada getY();
	int region(coordenada xMid, coordenada yMid);
};

#endif // POINT_H
