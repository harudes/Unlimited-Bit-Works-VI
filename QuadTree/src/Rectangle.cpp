#include "Rectangle.h"

rectangle::rectangle(coordenada xMin, coordenada xMax, coordenada yMin, coordenada yMax):minX(xMin),maxX(xMax),minY(yMin),maxY(yMax)
{
    calculateArea();
    calculatePerimeter();
}

rectangle::rectangle(){}

rectangle::rectangle(Point u, Point v){
    if(u.x<v.x){
        minX=u.x;
        maxX=v.x;
    }
    else{
        minX=v.x;
        maxX=u.x;
    }
    if(u.y<v.y){
        minY=u.y;
        maxY=v.y;
    }
    else{
        minY=v.y;
        maxY=u.y;
    }
    calculateArea();
    calculatePerimeter();
}

rectangle::rectangle(rectangle u, rectangle v){
    if(u.minX<v.minX){
        minX=u.minX;
    }
    else{
        minX=v.minX;
    }
    if(u.maxX>v.maxX){
        maxX=u.maxX;
    }
    else{
        maxX=v.maxX;
    }
    if(u.minY<v.minY){
        minY=u.minY;
    }
    else{
        minY=v.minY;
    }
    if(u.maxY>v.maxY){
        maxY=u.maxY;
    }
    else{
        maxY=v.maxY;
    }
    calculateArea();
    calculatePerimeter();
}

void rectangle::calculateArea(){
    area=(maxX-minX)*(maxY-minY);
}

void rectangle::calculatePerimeter(){
    perimeter=2*(maxX-minX+maxY-minY);
}

float rectangle::getArea(){return area;}

float rectangle::getPerimeter(){return perimeter;}

float rectangle::enlargement(coordenada x, coordenada y){
    if(x<minX || x>maxX || y<minY || y>maxY){
        coordenada xMin=minX,xMax=maxX,yMin=minY,yMax=maxY;
        if(x<minX)
            xMin=x;
        if(x>maxX)
            xMax=x;
        if(y<minY)
            yMin=y;
        if(y>maxY)
            yMax=y;
        rectangle FI(xMin,xMax,yMin,yMax);
        return FI.getArea()-getArea();
    }
    return 0;
}

float rectangle::enlargement(rectangle r){
    if(r.minX<minX || r.maxX>maxX || r.minY<minY || r.maxY>maxY){
        coordenada xMin=minX,xMax=maxX,yMin=minY,yMax=maxY;
        if(r.minX<minX)
            xMin=r.minX;
        if(r.maxX>maxX)
            xMax=r.maxX;
        if(r.minY<minY)
            yMin=r.minY;
        if(r.maxY>maxY)
            yMax=r.maxY;
        rectangle FI(xMin,xMax,yMin,yMax);
        return FI.getArea()-getArea();
    }
    return 0;
}

rectangle::~rectangle()
{
    //dtor
}
