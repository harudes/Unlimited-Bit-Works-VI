#include <iostream>
using namespace std;

int combination(string act, string comb, int n){
	int aux, aux2,temp,result=0;
	for(unsigned int i=0;i<n;++i){
		aux=act[i]-'0';
		aux2=comb[i]-'0';
		temp=abs(aux-aux2);
		if(temp>5)
			temp=10-temp;
		result+=temp;
	}
	return result;
}

int main(int argc, char *argv[]) {
	int n;
	string a,b;
	cin>>n;
	cin>>a;
	cin>>b;
	cout<<combination(a,b,n);
	return 0;
}

