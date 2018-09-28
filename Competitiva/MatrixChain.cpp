#include <iostream> 
#include <limits.h> 
#include <vector>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

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

void BackTracking(vector<vector<pair<pair<int,int>,pair<int,int>>>> &backTracking,int n){
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
}

int MatrixChainOrder(vector<int> p) { 
	int n=p.size();
	vector<vector<int>> m(n);
	queue<pair<int,int>> orden;
	stack<pair<int,int>> aux;
	for (int i = 0; i < n; ++i) {
		m[i].assign(n,0);
	}
	vector<vector<pair<pair<int,int>,pair<int,int>>>> backTracking(n);
	for (int i = 0; i < n; ++i) {
		backTracking[i].assign(n,make_pair(make_pair(0,0),make_pair(0,0)));
	}
	int j, temp,auxI,auxJ,auxK;
	for (int L=2; L<n; ++L) { 
		for (int i=1; i<n-L+1; ++i) { 
			j = i+L-1; 
			m[i][j] = INT_MAX; 
			for (int k=i; k<=j-1; ++k) { 
				temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]; 
				if (temp < m[i][j]){ 
					m[i][j] = temp;
					auxI=i;
					auxJ=j;
					auxK=k;
				}
			}
			backTracking[i][j]=make_pair(make_pair(auxI,auxK),make_pair(auxK+1,auxJ));
		}
	}
	BackTracking(backTracking,n);
	cout<<endl;
	return m[1][n-1];
}

int main() 
{ 
	vector<int> arr= {1000,9,8,7,6,5,4,3,2,1}; 
	cout<<"Minimum number of multiplications is: "<<MatrixChainOrder(arr)<<" "; 
	return 0; 
} 

