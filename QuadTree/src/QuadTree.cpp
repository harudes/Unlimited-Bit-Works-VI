#include <iostream>
#include "QuadTree.h"

ostream& operator<<(ostream& os, Point p){
	os << p.getX() << ',' << p.getY();
	return os;
}

Point::Point(coordenada a, coordenada b):x(a),y(b){

}

coordenada Point::getX(){return x;}
coordenada Point::getY(){return y;}

int Point::region(coordenada xMid, coordenada yMid){
    int rpta=0;
    if(x>xMid)
        rpta|=1;
    if(y<yMid)
        rpta|=2;
    return rpta;
}

Line::Line(Point a, Point b):u(a),v(b){}

QuadTree::QuadTree(coordenada xMin, coordenada xMax, coordenada yMin, coordenada yMax, int maxP):minX(xMin),maxX(xMax),minY(yMin),maxY(yMax),maxPoints(maxP){
    midX=(minX+maxX)/2;
    midY=(minY+maxY)/2;
    for(int i=0;i<4;++i)
        regions[i]=NULL;
}

QuadTree::QuadTree(Point leftup, Point rightdown, int maxP):minX(leftup.getX()),maxX(rightdown.getX()),minY(rightdown.getY()),maxY(leftup.getY()),maxPoints(maxP){
    for(int i=0;i<4;++i)
        regions[i]=NULL;
}

void QuadTree::split(){
    regions[0]=new QuadTree(minX,midX,midY,maxY,maxPoints);
    regions[1]=new QuadTree(midX,maxX,midY,maxY,maxPoints);
    regions[2]=new QuadTree(minX,midX,minY,midY,maxPoints);
    regions[3]=new QuadTree(midX,maxX,minY,midY,maxPoints);
    for(unsigned int i=0;i<=maxPoints;++i){
        regions[points[i].region(midX,midY)]->insertPoint(points[i]);
    }
    points.clear();
}

void QuadTree::insertPoint(coordenada x, coordenada y){
    Point punto(x,y);
    if(!regions[0]){
        points.push_back(punto);
        if(points.size()>maxPoints)
            split();
    }
    else{
        regions[punto.region(midX,midY)]->insertPoint(punto);
    }
}

void QuadTree::insertPoint(Point p){
    if(!regions[0]){
        points.push_back(p);
        if(points.size()>maxPoints)
            split();
    }
    else{
        regions[p.region(midX,midY)]->insertPoint(p);
    }
}

vector<Line> QuadTree::getLines(){
    vector<Line> lines;
    Point
        a(maxX,midY),
        b(minX,midY),
        c(midX,maxY),
        d(midX,minY);
    if(regions[0]){
        lines.push_back(Line(a,b));
        lines.push_back(Line(c,d));
        for(int i=0;i<4;++i){
            vector<Line> aux=regions[i]->getLines();
            lines.insert(lines.end(),aux.begin(),aux.end());
        }
    }
    return lines;
}

QuadTree::~QuadTree()
{
    //dtor
}
