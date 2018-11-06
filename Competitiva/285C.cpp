#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	long long int n;
	cin>>n;
	int a;
	long long int l=0,g=0,result=0,m=0;
	bool isn=false;
	for(int i=0;i<n;++i){
		cin>>a;
		if(a<n){
			l+=a;
			++m;
		}
		else{
			l-=(a);
		}
	}
	result=n*(n+1)-l-(m*(m+1)/2);
	cout<<l<<endl<<g<<endl;
	cout<<m<<endl;
	cout<<result;
	return 0;
}

