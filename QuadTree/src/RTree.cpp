#include "RTree.h"

RTree::RTree(int m):M(m)
{
    P=this;
}

RTree::RTree(RTree* p, int m):M(m),P(p)
{

}

RTree::~RTree()
{
    //dtor
}

void RTree::Enlarge(Point E){
    coordenada minX=space.minX,
               maxX=space.maxX,
               minY=space.minY,
               maxY=space.maxY;
    if(E.getX()<minX)
        minX=E.x;
    if(E.getX()>maxX)
        maxX=E.x;
    if(E.getY()<minY)
        minY=E.y;
    if(E.getY()>maxY)
        maxY=E.y;
    space=rectangle(minX,maxX,minY,maxY);
}

void RTree::Enlarge(rectangle R){
    coordenada minX=space.minX,
               maxX=space.maxX,
               minY=space.minY,
               maxY=space.maxY;
    if(R.minX<minX)
        minX=R.minX;
    if(R.maxX>maxX)
        maxX=R.maxX;
    if(R.minY<minY)
        minY=R.minY;
    if(R.maxY>maxY)
        maxY=R.maxY;
    space=rectangle(minX,maxX,minY,maxY);
}

void RTree::FillLeaf(RTree *N, vector<bool> &flags){
    for(int i=0;i<M+1;++i){
        if(flags[i]){
            N->InsertPoint(points[i]);
        }
    }
}

void RTree::FillBranch(RTree *N, vector<bool> &flags){
    for(int i=0;i<M+1;++i){
        if(flags[i]){
            N->InsertBranch(branches[i]);
        }
    }
}

void RTree::InsertPoint(Point E){
    points.push_back(E);
    Enlarge(E);
}

void RTree::InsertBranch(RTree* N){
    cout<<branches.size()<<endl;
    branches.push_back(N);
    Enlarge(N->space);
    N->P=this;
}

RTree* RTree::ChooseLeaf(Point E){
   // cout<<"Se empezo un ChooseLeaf"<<endl;
    RTree* N=this;
    vector<RTree*> posibleN;
    while(N->branches.size()>0){
        //cout<<"Hola"<<endl;
        //cout<<"---------------------------------------------------"<<endl;
        //cout<<N<<endl;
        RTree* F;
        float minEnlargement=N->branches[0]->space.enlargement(E.getX(),E.getY()),temp=minEnlargement;
        F=N->branches[0];
       // cout<<branches[0]<<endl;
        posibleN.push_back(F);
        float aux;
        for(size_t i=1;i<N->branches.size();++i){
           // cout<<branches[i]<<endl;
            aux =N->branches[i]->space.enlargement(E.getX(),E.getY());
            if(aux<minEnlargement){
                minEnlargement=aux;
                F=N->branches[i];
                posibleN.clear();
                posibleN.push_back(F);
            }
            else if(aux=minEnlargement){
                posibleN.push_back(F);
            }
        }
        float minArea=posibleN[0]->space.getArea();
        F=posibleN[0];
        for(size_t i=1;i<posibleN.size();++i){
            aux=posibleN[i]->space.getArea();
            if(aux<minArea){
                minArea=aux;
                F=posibleN[i];
            }
        }
        //cout<<F<<endl;
        //cout<<"---------------------------------------------------"<<endl;
        if(N!=F)
            N=F;
        else
            return N;
    }
    //cout<<"Se termino un ChooseLeaf"<<endl;
    return N;
}

void RTree::PickSeeds(RTree *&E1, RTree *&E2, vector<bool> &flags){
    float maxArea=0,aux=0;
    int I1=0,I2=1;
    for(int i=0;i<M;++i){
        for(int j=i;j<M+1;++j){
            aux=rectangle(branches[i]->space,branches[j]->space).getArea() - (branches[i]->space.getArea()+branches[j]->space.getArea());
            if(aux>maxArea){
                maxArea=aux;
                I1=i;
                I2=j;
            }
        }
    }
    flags[I1]=false;
    flags[I2]=false;
    E1=branches[I1];
    E2=branches[I2];
}

void RTree::PickSeeds(Point &E1, Point &E2, vector<bool> &flags){
    float maxArea=0,aux=0;
    int I1=0,I2=1;
    for(int i=0;i<M;++i){
        for(int j=i+1;j<M+1;++j){
            aux=rectangle(points[i],points[j]).getArea();
            if(aux>maxArea){
                maxArea=aux;
                I1=i;
                I2=j;
            }
        }
    }
    flags[I1]=false;
    flags[I2]=false;
    E1=points[I1];
    E2=points[I2];
    //cout<<I1<<" "<<I2<<endl;
}

void RTree::PickNext(RTree* N, RTree* NN ,vector<bool> &flags){
    float maxD=0,d1,d2,aux;
    RTree *temp;
    int idx=0;
    for(size_t i=0;i<M+1;++i){
        if(flags[i]){
            d1=N->space.enlargement(points[i].x,points[i].y);
            d2=NN->space.enlargement(points[i].x,points[i].y);
            aux=d2-d1;
            if(aux<0)
                aux*=-1;
            if(aux>maxD){
                maxD=aux;
                idx=i;
            }
        }
    }
    flags[idx]=false;
    d1=N->space.enlargement(points[idx].x,points[idx].y);
    d2=NN->space.enlargement(points[idx].x,points[idx].y);
    if(d1<d2){
        temp=N;
    }
    else if(d1>d2){
        temp=NN;
    }
    else{
        if(N->space.getArea()<NN->space.getArea()){
            temp=N;
        }
        else if(N->space.getArea()>NN->space.getArea()){
            temp=NN;
        }
        else{
            if(N->points.size()<NN->points.size())
                temp = N;
            else
                temp = NN;
        }
    }
    temp->InsertPoint(points[idx]);
}

void RTree::PickNextBranch(RTree* N, RTree* NN ,vector<bool> &flags){
    float maxD=0,d1,d2,aux;
    RTree *temp;
    int idx=0;
    for(size_t i=0;i<M+1;++i){
        if(flags[i]){
            d1=N->space.enlargement(branches[i]->space);
            d2=NN->space.enlargement(branches[i]->space);
            aux=d2-d1;
            if(aux<0)
                aux*=-1;
            if(aux>maxD){
                maxD=aux;
                idx=i;
            }
        }
    }
    flags[idx]=false;
    d1=N->space.enlargement(branches[idx]->space);
    d2=NN->space.enlargement(branches[idx]->space);
    if(d1<d2){
        temp=N;
    }
    else if(d1>d2){
        temp=NN;
    }
    else{
        if(N->space.getArea()<NN->space.getArea()){
            temp=N;
        }
        else if(N->space.getArea()>NN->space.getArea()){
            temp=NN;
        }
        else{
            if(N->points.size()<NN->points.size())
                temp = N;
            else
                temp = NN;
        }
    }
    temp->InsertBranch(branches[idx]);
}

void RTree::SplitRoot(){
    //cout<<"Se empezo un split de raiz"<<endl;
    RTree *N=new RTree(this,M),*NN = new RTree(this,M);
    //cout<<"Ramas de la raiz: "<<branches.size()<<endl;
    int inserted=2;
    vector<bool> flags(M+1,true);
    RTree *E1,*E2;
    //cout<<"Se empezo un pickseed"<<endl;
    PickSeeds(E1,E2,flags);
    //cout<<"Se termino un pickseed"<<endl;
    N->space=E1->space;
    cout<<E1->space.getArea()<<" "<<E2->space.getArea()<<endl;
    N->InsertBranch(E1);
    NN->space=E2->space;
    NN->InsertBranch(E2);
    while(inserted <= M+1 && N->branches.size()<=M/2 && NN->branches.size()<=M/2){
        PickNextBranch(N,NN,flags);
        ++inserted;
    }
    if(N->branches.size()==M/2){
        FillBranch(NN,flags);
    }
    else{
        FillBranch(N,flags);
    }
    branches.clear();
    branches.push_back(N);
    branches.push_back(NN);
    /*cout<<branches[0]<<":";
    for(size_t i=0;i<branches[0]->branches.size();++i)
        cout<<branches[0]->branches[i]<<" ";
    cout<<endl;
    cout<<branches[1]<<":";
    for(size_t i=0;i<branches[1]->branches.size();++i)
        cout<<branches[1]->branches[i]<<" ";
    cout<<endl;*/
    cout<<"Se realizo un split de raiz"<<endl;
}

RTree* RTree::SplitLeaf(){
    //cout<<"Se empezo un split de hoja"<<endl;
    RTree *N=new RTree(P,M),*NN = new RTree(P,M);
    //cout<<points.size()<<endl;
    int inserted=2;
    vector<bool> flags(M+1,true);
    Point E1,E2;
    PickSeeds(E1,E2,flags);
    N->InsertPoint(E1);
    N->space=rectangle(E1,E1);
    NN->InsertPoint(E2);
    NN->space=rectangle(E2,E2);
    while( (inserted <= M+1) && (N->points.size()<ceil(M/2)) && (NN->points.size()<ceil(M/2)) ){
        PickNext(N,NN,flags);
        ++inserted;
    }
    if(N->points.size()==ceil(M/2)){
        FillLeaf(NN,flags);
    }
    else{
        FillLeaf(N,flags);
    }
    points=N->points;
    space=N->space;
    //P=N->P;
    delete(N);
    branches.clear();
    NN->branches.clear();
    cout<<"Se realizo un split de hoja"<<endl;
    return NN;
}

RTree* RTree::SplitBranch(){
    //cout<<"Se empezo un split de rama"<<endl;
    RTree *N=new RTree(P,M),*NN = new RTree(P,M);
    int inserted=2;
    vector<bool> flags(M+1,true);
    RTree *E1,*E2;
    PickSeeds(E1,E2,flags);
    cout<<E1->space.getArea()<<" "<<E2->space.getArea()<<endl;
    N->space=E1->space;
    N->InsertBranch(E1);
    NN->space=E2->space;
    NN->InsertBranch(E2);
    while( (inserted <= M+1) && (N->branches.size()<ceil(M/2)) && (NN->branches.size()<ceil(M/2)) ){
        PickNextBranch(N,NN,flags);
        ++inserted;
    }
    if(N->branches.size()==ceil(M/2)){
        FillBranch(NN,flags);
    }
    else{
        FillBranch(N,flags);
    }
    branches=N->branches;
    //P=N->P;
    delete(N);
    cout<<"Se realizo un split de rama"<<endl;
    return NN;
}

void RTree::AdjustTree(RTree* NN, RTree* Root){
    //cout<<"Se empezo un adjust tree"<<endl;
    RTree *N=this;
    bool split=1;
    do{
        N->P->Enlarge(N->space);
        if(split)
            N->P->InsertBranch(NN);
        split=0;
        if(N->P->branches.size()>M){
            if(N->P!=Root){
                RTree *PP;
                PP=N->P->SplitBranch();
                NN=PP;
                split=1;
            }
            else{
                N->P->SplitRoot();
            }
        }
        N=N->P;
    }
    while(N!=Root);
    //cout<<"Se termino un adjust tree"<<endl;
}

void RTree::AdjustTree(Point E){
    //cout<<"Se empezo un adjust tree"<<endl;
    RTree *N=this;
    do{
        cout<<N->P<<endl;
        N->Enlarge(E);
        N=N->P;
    }
    while(N->P!=N);
    N->Enlarge(E);
    //cout<<"Se termino un adjust tree"<<endl;
}

void RTree::Insert(coordenada a, coordenada b){
    Point E=Point(a,b);
    if(branches.size()==0){
        if(points.size()==0){
            points.push_back(E);
            space=rectangle(a,a,b,b);
        }
        else{
            if(points.size()<M)
                InsertPoint(E);
            else{
                ////cout<<this<<endl;
                RTree* N=new RTree(this,M);
                N->points=points;
                N->space=rectangle(points[0],points[0]);
                ////cout<<N->P<<endl;
                points.clear();
                branches.push_back(N);
                N->AdjustTree(E);
                Insert(a,b);
            }
        }
    }
    else{
        RTree *N=ChooseLeaf(E);
        N->points.push_back(E);
        RTree* NN=nullptr;
        if(N->points.size()>M){
            NN=N->SplitLeaf();
        }
        if(NN){
            N->AdjustTree(NN, this);
        }
        else{
            N->AdjustTree(E);
        }
    }
}

void RTree::Delete(){

}

vector<Line> RTree::getLines(){
    vector<Line> lines;
    //bool algo=(branches.size()>0&&points.size()>0);
    //cout<<algo;
    Point a(space.minX,space.minY),
                  b(space.maxX,space.minY),
                  c(space.maxX,space.maxY),
                  d(space.minX,space.maxY);
                lines.push_back(Line(a,b));
                lines.push_back(Line(b,c));
                lines.push_back(Line(c,d));
                lines.push_back(Line(a,d));
   // }
    if(branches.size()>0){
        /*cout<<"-------------------------------------------"<<endl;
        cout<<this<<":";
        for(size_t i=0;i<branches.size();++i)
            cout<<branches[i]<<" ";
        cout<<endl;
        cout<<"-------------------------------------------"<<endl;*/
        //if(branches.size()==0){

        for(int i=0;i<branches.size();++i){
            vector<Line> aux=branches[i]->getLines();
            lines.insert(lines.end(),aux.begin(),aux.end());
        }
    }
    //else{

    //}
    return lines;
}

void RTree::FindLeaf(){

}

void RTree::CondenseTree(){

}

vector<Point> RTree::Search(){

}

vector<Point> RTree::getPoints(){
    vector<Point> result;
    if(points.size()>0){
        result.insert(result.end(),points.begin(),points.end());
    }
    else{
        for(size_t i=0;i<branches.size();++i){
            vector<Point> aux=branches[i]->getPoints();
            result.insert(result.end(),aux.begin(),aux.end());
        }
    }
    return result;
}


