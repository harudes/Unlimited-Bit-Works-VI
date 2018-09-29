#include "Point.h"

ostream& operator<<(ostream& os, Point p){
	os << p.getX() << ',' << p.getY();
	return os;
}

bool operator==(Point u, Point v){
    return (u.getX()==v.getX())&&(u.getY()==v.getY());
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
