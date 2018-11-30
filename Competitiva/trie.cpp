#include <iostream>
#include <stack>
#include <utility>
using namespace std; 

const int ALPHABET_SIZE = 26; 

struct TrieNode{ 
	TrieNode *children[ALPHABET_SIZE]; 
	
	bool isEndOfWord; 
	
	bool hasChildren(){
		for(int i=0;i<ALPHABET_SIZE;++i){
			if(children[i])
				return true;
		}
		return false;
	}
}; 


TrieNode *getNode(){ 
	struct TrieNode *pNode =  new TrieNode; 
	
	pNode->isEndOfWord = false; 
	
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = nullptr; 
	
	return pNode; 
} 

void insert(TrieNode *root, string key){ 
	TrieNode *pCrawl = root; 
	
	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 
		
		pCrawl = pCrawl->children[index]; 
	} 
	
	pCrawl->isEndOfWord = true; 
} 

bool search(TrieNode *root, string key, stack<pair<TrieNode*,int>> &route){ 
	TrieNode *pCrawl = root; 
	route.push(make_pair(pCrawl,0));
	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = key[i] - 'a'; 
		if (!pCrawl->children[index]) 
			return false; 
		pCrawl = pCrawl->children[index]; 
		route.push(make_pair(pCrawl,index));
	} 
	
	return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 

void del(TrieNode *root, string key){
	stack<pair<TrieNode*,int>> route;
	if(search(root,key,route)){
		int idx;
		do{
			if(route.top().first->hasChildren()){
				route.top().first->isEndOfWord=false;
				return;
			}
			delete(route.top().first);
			idx=route.top().second;
			route.pop();
			route.top().first->children[idx]=nullptr;
		}
		while(!route.top().first->isEndOfWord);
	}
}


int main(){ 
	string keys[] = {"the", "a", "there", 
		"answer", "any", "by", 
		"bye", "their" }; 
	int n = 8; 
	
	TrieNode *root = getNode(); 
	root->isEndOfWord=true;
	
	for (int i = 0; i < n; i++) 
		insert(root, keys[i]); 
	stack<pair<TrieNode*,int>> r;
	
	search(root, "the",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	search(root, "these",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	search(root, "any",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	del(root,"a");
	search(root, "any",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	search(root, "a",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	del(root,"any");
	search(root, "any",r)? cout << "Yes\n" : 
		cout << "No\n"; 
	return 0; 
}
