#include <iostream>
#include <vector>
using namespace std;

long long mod=1e+9 + 7;

long long modulo(long int a, long int b){
	long long r;
	r=a%b;
	if(r<0){
		r+=b;
	}
	return r;
}

int Tetrahedron(int n){
	vector<long long> m(2);
	m[0]=3;
	m[1]=3;
	vector<long long> aux(2);
	for(int i=1;i<n;++i){
		aux[0]=3*m[0]%1000000007;
		aux[1]=modulo(aux[0]-m[1],1000000007);
		m=aux;
	}
	//for(size_t i=0;i<m.size();++i)
		//cout<<m[i][0]<<" - "<<m[i][1]<<endl;
	return modulo(m[0]-m[1],1000000007);
}

int main(int argc, char *argv[]) {
	int n;
	cin>>n;
	cout<<Tetrahedron(n);
	return 0;
}


