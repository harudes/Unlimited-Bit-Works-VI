#include "QuadTree.h"

Point::Point(int a, int b):x(a),y(b){

}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}

QuadTree::QuadTree(int xMin, int xMax, int yMin, int yMax, int maxP):minX(xMin),maxX(xMax),minY(yMin),maxY(yMax)
{

}

void QuadTree::insertPoint(int x, int y){
    Point punto(x,y);

}

QuadTree::~QuadTree()
{
    //dtor
}
