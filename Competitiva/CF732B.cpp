#include <iostream>
#include <vector>
using namespace std;

void cormen(int n, int k, vector<int> &as){
	int result=0,aux;
	if(n>1){
		for(int i=1; i<n; ++i){
			aux=k-(as[i]+as[i-1]);
			if(aux>=1){
				result+=aux;
				as[i]+=aux;
			}
		}
		cout<<result<<endl;
		for(int i=0;i<n;++i)
			cout<<as[i]<<" ";
	}
	else{
		//cout<<k-as[0]<<endl<<k;
		cout<<0<<endl<<as[0];
	}
}

int main(int argc, char *argv[]) {
	int n,a;
	cin>>n;
	cin>>a;
	int min=a, max=a;
	for(int i=1;i<n;++i){
		cin>>a;
		if(a>max)
			max=a;
		if(a<min)
			min=a;
	}
	cout<<"Maximo: "<<max<<endl<<"Minimo: "<<min<<endl;
	return 0;
}

