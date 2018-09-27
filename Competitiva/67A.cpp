#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rpta=1;

void mayusculas(string &palabra){
	for(int i = 0; i < palabra.size(); i++){
		palabra[i] = toupper(palabra[i]);
	}
}

struct Edge  { int u, v; float w;
Edge(int u = -1, int v = -1, float w = -1.0) : u(u), v(v), w(w) { }
};

class GRAPH {
private:
	// Implementation-dependent code
	vector<vector <bool> > adj;
	vector<vector <float> > weight;
	vector<int> camino;
	vector<string> disp;
	vector<float> pesos;
	int Vcnt, Ecnt;
	bool digraph;
public:
	GRAPH(int V, bool digraph = false) : adj(V),weight(V), Vcnt(V), Ecnt(0), digraph(digraph) {
		for (int i = 0; i < V; i++){
			adj[i].assign(V, false);
			weight[i].assign(V, false);
			camino.assign(V,0);
			disp.push_back("unvisited");
			pesos.push_back(100000.0);
		}
	}
	void clean(){
		for(int i=0; i<Vcnt;i++){
			disp[i]="unvisited";
			pesos[i]=100000;
		}
	};
	~GRAPH(){};
	int V()const{
		return Vcnt;
	};
	int E()const{
		return Ecnt;
	};
	bool directed()const{
		return digraph;
	};
	void insert(Edge e){
		adj[e.u][e.v]=1;
		weight[e.u][e.v]=e.w;
		weight[e.v][e.u]=e.w;
		if(digraph)
			adj[e.v][e.u]=1;
			Ecnt++;
	};
	void remove(Edge e){
		adj[e.v][e.w]=0;
		if(digraph)
			adj[e.w][e.v]=0;
			Ecnt--;
	};
	bool edge(int u, int v){
		return adj[u][v];
	};
	vector<int> neightbors(int u){
		vector<int> vecinos;
		for(int i=0;i<Vcnt;i++){
			if(adj[u][i])
				vecinos.push_back(i);
		}
		return vecinos;
	}
	void dfs(int u, int l){
		if(l>rpta)
			rpta=l;
		//cout<<u<<" -> ";
		disp[u] = "in_progress";
		vector<int> vecinos=neightbors(u);
		for(int i=0;i<vecinos.size();i++){
			if(disp[vecinos[i]]=="unvisited"){
				dfs(vecinos[i],l+1);
			}
		}
		disp[u]="done";
	};
	void bfs(int s){
		vector<vector<int> > L(Vcnt);
		L[0].push_back(s);
		for(int i=0;i<Vcnt;i++){
			for(int j=0; j<L[i].size();i++){
				vector<int> vecinos=neightbors(L[i][j]);
				for(int k=0;k<vecinos.size();k++){
					disp[vecinos[k]]="visited";
					L[i+1].push_back(vecinos[k]);
					//cout<<vecinos[k]<<" -> ";
				}
			}
		}
	};
	class adjIterator {
	private:
		const GRAPH &G;
		int i, v;
	public:
		adjIterator(const GRAPH &G, int v) :  G(G), v(v), i(-1) { }
		int beg() { i = -1; return nxt(); }
		int nxt() {
			for (i++; i < G.V(); i++)
				if (G.adj[v][i] == true) return i;
			return -1;
		}
		bool end() { return i >= G.V(); }
	};
};


template <class Graph>
vector <Edge> edges(Graph &G) {
	int E = 0;
	vector <Edge> a(G.E());
	for (int v = 0; v < G.V(); v++) {
		typename Graph::adjIterator A(G, v);
		for (int w = A.beg(); !A.end(); w = A.nxt())
			if (G.directed() || v < w)
				a[E++] = Edge(v, w);
	}
	return a;
}

template <class Graph>
void show(const Graph &G) {
	for (int s = 0; s < G.V(); s++) {
		cout.width(2); cout << s << ":";
		typename Graph::adjIterator A(G, s);
		for (int t = A.beg(); !A.end(); t = A.nxt()) { 
			cout.width(2); cout << t << " "; 
		}
		cout << endl;
	}
}

bool buscar(vector<string> vec, string val, size_t &pos){
	pos=0;
	for(;pos<vec.size()&&vec[pos]!="";++pos){
		if(vec[pos]==val){
			return 1;
		}
	}
	return 0;
}

void insertar(vector<string> &vec, string val){
	size_t pos=0;
	if(!(buscar(vec,val,pos)))
		vec[pos]=val;
}

int main(int argc, char *argv[]) {
	int e;
	cin>>e;
	GRAPH grafo(e+1,0);
	string aux;
	string aux2;
	vector<string> nombres(e+1,"");
	size_t pos;
	size_t pos2;
	for(int i=0;i<e;++i){
		cin>>aux>>aux2>>aux2;
		mayusculas(aux);
		mayusculas(aux2);
		insertar(nombres,aux2);
		insertar(nombres,aux);
		buscar(nombres,aux2,pos);
		buscar(nombres,aux,pos2);
		Edge ed(pos,pos2,1.0);
		grafo.insert(ed);
	}
	grafo.dfs(0,1);
	cout<<rpta;
	return 0;
}

