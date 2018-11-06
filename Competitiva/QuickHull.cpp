#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Point{
	float x,y;
	Point(float u, float v):x(u),y(v){}
};

ostream& operator<<(ostream& of, Point p){
	of<<'('<<p.x<<','<<p.y<<')';
	return of;
}

template <typename T>
void printVec(vector<T> vec){
	for(size_t i=0;i<vec.size();++i)
		cout<<vec[i]<<",";
	cout<<endl;
}

int getSide(Point a, Point b, Point c){
	if(((c.y-a.y)*(b.x-a.x)-(c.x-a.x)*(b.y-a.y))>0)
		return 1;
	if(((c.y-a.y)*(b.x-a.x)-(c.x-a.x)*(b.y-a.y))<0)
		return 0;
	return -1;
}

void RecursiveQuickHull(vector<Point>& points){
	
}

list<Point> QuickHull(vector<Point>& points){
	Point *min,*max;
	list<Point> result;
	min=&points[0];
	max=&points[0];
	for(size_t i=1;i<points.size();++i){
		if(points[i].x>max->x)
			max=&points[i];
		if(points[i].x<min->x)
			min=&points[i];
	}
	result.push_back(*min);
	result.push_back(*max);
	return result;
}

int main(int argc, char *argv[]) {
	vector<Point> vec={Point(0.0,3.0),Point(1.0,1.0),Point(2.0,2.0),Point(4.0,4.0),Point(0.0,0.0),Point(1.0,2.0),Point(3.0,1.0),Point(3.0,3.0)};
	QuickHull(vec);
	return 0;
}

