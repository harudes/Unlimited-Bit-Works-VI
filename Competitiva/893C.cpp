#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	long long n,m,x,y;
	long long total=0;
	cin>>n>>m;
	vector<long long> c(n);
	for(int i=0;i<n;++i){
		cin>>c[i];
		total+=c[i];
	}
	for(int i=0;i<m;++i){
		cin>>x>>y;
		if(c[x-1]>c[y-1]){
			total-=c[x-1];
			c[x-1]=0;
		}
		else{
			total-=c[y-1];
			c[y-1]=0;
		}
	}
	cout<<total;
	return 0;
}

