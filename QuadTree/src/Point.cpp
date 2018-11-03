#include "Point.h"

Point::Point(coordenada a, coordenada b):x(a),y(b){

}//dtor

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
