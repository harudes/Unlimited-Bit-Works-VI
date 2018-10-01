#include <iostream> 
#include <limits.h> 
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

int operaciones=0;

template<typename T,typename S>
ostream& operator<<(ostream &os, pair<T,S> p){
	os<<"("<<p.first<<" "<<p.second<<")";
	return os;
}

template<typename T>
void printMatrix(vector<vector<T>> vec){
	for(size_t i=0;i<vec.size();++i){
		for(size_t j=0;j<vec[i].size();++j){
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}

/*void BackTracking(vector<vector<pair<pair<int,int>,pair<int,int>>>> &backTracking,int n){
	queue<pair<int,int>> orden;
	stack<pair<int,int>> aux;
	orden.push(backTracking[1][n-1].first);
	orden.push(backTracking[1][n-1].second);
	while(!orden.empty()){
		if(orden.front()!=make_pair(0,0)){
			orden.push(backTracking[orden.front().first][orden.front().second].first);
			orden.push(backTracking[orden.front().first][orden.front().second].second);
			aux.push(orden.front());
		}
		orden.pop();
	}
	while(!aux.empty()){
		pair<int,int> temp=aux.top();
		aux.pop();
		cout<<aux.top()<<temp<<endl;
		aux.pop();
	}
}*/

void BackTracking(vector<vector<int>> s,int i,int j,char &c){
	if(i==j)
		cout<<c++;
	else{
		cout<<"(";
		BackTracking(s,i,s[i][j],c);
		BackTracking(s,s[i][j]+1,j,c);
		cout<<")";
	}
}

int MatrixChainOrder(vector<int> p) { 
	int n=p.size();
	vector<vector<int>> m(n);
	char c='A';
	for (int i = 0; i < n; ++i) {
		m[i].assign(n,0);
	}
	vector<vector<int>> s(n);
	for (int i = 0; i < n; ++i) {
		s[i].assign(n,0);
	}
	int j, temp;
	for (int L=2; L<n; ++L) { 
		for (int i=1; i<n-L+1; ++i) { 
			j = i+L-1; 
			m[i][j] = INT_MAX; 
			for (int k=i; k<=j-1; ++k) { 
				temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]; 
				if (temp < m[i][j]){
					m[i][j] = temp;
					s[i][j]=k;
				}
			}
		}
	}
	BackTracking(s,1,n-1,c);
	cout<<endl;
	return m[1][n-1];
}

int main() 
{ 
	vector<int> arr= {9,5,7,8,10}; 
	cout<<"Numero minimo de operaciones: "<<MatrixChainOrder(arr)<<" "; 
	return 0; 
} 

