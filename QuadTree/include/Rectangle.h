#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <Point.h>

typedef float coordenada;

class rectangle
{
    float area;
    float perimeter;
    void calculateArea();
    void calculatePerimeter();
public:
    coordenada minX,minY,maxX,maxY;
    rectangle(coordenada xMin, coordenada xMax, coordenada yMin, coordenada yMax);
    rectangle(Point u, Point v);
    rectangle(rectangle u, rectangle v);
    rectangle();
    float getArea();
    float getPerimeter();
    float enlargement(coordenada x, coordenada y);
    float enlargement(rectangle r);
    ~rectangle();
};

#endif // RECTANGLE_H
