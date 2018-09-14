#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
typedef unsigned int pointa;
using namespace std;

void print_vector(vector<int> &A,pointa ini, pointa fin){
	cout<<endl;
	for(pointa i=ini;i<=fin;++i)
		cout<<A[i]<<",";
	cout<<endl;
}

void Merge(vector<int> &A, pointa ini, pointa fin){
	pointa mid=(fin+ini)>>1;
	vector<int> aux(mid-ini+1);
	pointa aux_tam=aux.size();
	for(pointa i2=ini,i=0;i<aux_tam;){
		aux[i++]=A[i2++];
	}
	pointa a1=0,i=ini;
	for(pointa a2=mid+1;a1<aux_tam&&a2<=fin;){
		if(aux[a1]<A[a2]){
			A[i++]=aux[a1++];
		}
		else{
			A[i++]=A[a2++];
		}
	}
	while(a1<aux_tam){
		A[i++]=aux[a1++];
	}		
}

void MergeSort(vector<int> &vec,pointa ini,pointa fin){
	if(fin-ini>0){
		pointa mid=(fin+ini)>>1;
		MergeSort(vec,ini,mid);
		MergeSort(vec,mid+1,fin);
		Merge(vec,ini,fin);
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	vector<int> vec(16);
	for(int i=0; i<16; i++)
		vec[i]=rand()%100;
	print_vector(vec,0,15);
	MergeSort(vec,0,15);
	print_vector(vec,0,15);
	return 0;
}

