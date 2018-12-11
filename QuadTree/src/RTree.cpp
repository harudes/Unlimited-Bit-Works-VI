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

template<typename T>
void printVector(vector<T> &vec){
    cout<<"[";
    for(size_t i=0;i<vec.size();++i){
        cout<<vec[i]<<",";
    }
    cout<<"]"<<endl;
}

void RTree::Enlarge(Point E){
    coordenada minX=space.minX,
               maxX=space.maxX,
               minY=space.minY,
               maxY=space.maxY;
    if(E.getX()<minX)
        minX=E.getX();
    if(E.getX()>maxX)
        maxX=E.getX();
    if(E.getY()<minY)
        minY=E.getY();
    if(E.getY()>maxY)
        maxY=E.getY();
    space=rectangle(minX,maxX,minY,maxY);
}

void RTree::Enlarge(RTree* N){
    coordenada minX=space.minX,
               maxX=space.maxX,
               minY=space.minY,
               maxY=space.maxY;
    if(N->space.minX<minX)
        minX=N->space.minX;
    if(N->space.maxX>maxX)
        maxX=N->space.maxX;
    if(N->space.minY<minY)
        minY=N->space.minY;
    if(N->space.maxY>maxY)
        maxY=N->space.maxY;
    space=rectangle(minX,maxX,minY,maxY);
}

RTree* RTree::ChooseLeaf(Point E){
    RTree* N=this;
    vector<RTree*> posibleN;
    while(N->branches.size()>0){
        RTree* F;
        float minEnlargement=N->branches[0]->space.enlargement(E),temp=minEnlargement;
        F=N->branches[0];
        posibleN.push_back(F);
        float aux;
        for(size_t i=1;i<N->branches.size();++i){
            aux =N->branches[i]->space.enlargement(E);
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
        if(N!=F)
            N=F;
        else{
            return N;
        }
    }
    return N;
}

void RTree::FindLeaf(){

}

void RTree::CondenseTree(){

}

void RTree::InsertPoint(Point E){
    points.push_back(E);
    Enlarge(E);
}

void RTree::InsertBranch(RTree* N){
    branches.push_back(N);
    Enlarge(N);
}

void RTree::PickSeeds(RTree *&E1, RTree *&E2, vector<bool> &flags){
    float maxArea=0,aux=0;
    int I1=0,I2=0;
    for(int i=0;i<M+1;++i){
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
    int I1=0,I2=0;
    for(int i=0;i<M+1;++i){
        for(int j=i;j<M+1;++j){
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
}

void RTree::PickNext(RTree* N, RTree* NN ,vector<bool> &flags){
    float maxD=0,d1,d2,aux;
    RTree *temp;
    int idx=-1;
    for(size_t i=0;i<M+1;++i){
        if(flags[i]){
            d1=N->space.enlargement(points[i]);
            d2=NN->space.enlargement(points[i]);
            aux=d2-d1;
            if(aux<0)
                aux*=-1;
            if(aux>maxD){
                maxD=aux;
                idx=i;
            }
        }
    }
    if(idx>=0){
        flags[idx]=false;
        d1=N->space.enlargement(points[idx]);
        d2=NN->space.enlargement(points[idx]);
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
}

void RTree::PickNextBranch(RTree* N, RTree* NN ,vector<bool> &flags){
    float maxD=0,d1,d2,aux;
    RTree *temp;
    int idx=-1;
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
    if(idx>=0){
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
        branches[idx]->P=temp;
    }
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
            branches[i]->P=N;
        }
    }
}

void RTree::SplitRoot(){
    RTree *N=new RTree(this,M),*NN = new RTree(this,M);
    int inserted=2;
    vector<bool> flags(M+1,true);
    RTree *E1,*E2;
    PickSeeds(E1,E2,flags);
    N->InsertBranch(E1);
    E1->P=N;
    N->space=E1->space;
    NN->InsertBranch(E2);
    NN->space=E2->space;
    E2->P=NN;
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
}

void RTree::SplitBranch(RTree *&NN){
    RTree *N=new RTree(P,M);
    P->branches.push_back(NN);
    int inserted=2;
    vector<bool> flags(M+1,true);
    RTree *E1,*E2;
    PickSeeds(E1,E2,flags);
    N->InsertBranch(E1);
    N->space=E1->space;
    E1->P=N;
    NN->InsertBranch(E2);
    NN->space=E2->space;
    E2->P=NN;
    while(inserted <= M+1 && N->branches.size()<M/2+1 && NN->branches.size()<M/2+1){
        PickNextBranch(N,NN,flags);
        ++inserted;
    }
    if(N->branches.size()==M/2+1){
        FillBranch(NN,flags);
    }
    else{
        FillBranch(N,flags);
    }
    branches=N->branches;
    for(size_t i=0;i<branches.size();++i){
        branches[i]->P=this;
    }
    space=N->space;
    delete(N);
}

void RTree::SplitLeaf(RTree *&NN){
    RTree *N=new RTree(P,M);
    NN = new RTree(P,M);
    P->branches.push_back(NN);
    int inserted=2;
    vector<bool> flags(M+1,true);
    Point E1,E2;
    PickSeeds(E1,E2,flags);
    N->InsertPoint(E1);
    N->space=rectangle(E1,E1);
    NN->InsertPoint(E2);
    NN->space=rectangle(E2,E2);
    while(inserted <= M+1 && N->points.size()<M/2+1 && NN->points.size()<M/2+1){
        PickNext(N,NN,flags);
        ++inserted;
    }
    if(N->points.size()==M/2+1){
        FillLeaf(NN,flags);
    }
    else{
        FillLeaf(N,flags);
    }
    points=N->points;
    space=N->space;
    delete(N);
    branches.clear();
    NN->branches.clear();
}

void RTree::AdjustTree(RTree* NN, RTree* Root){
    RTree *N=this;
    while(N->P==N){
        P->Enlarge(N);
        N=N->P;
    }
    P->Enlarge(NN);
    if(P->branches.size()>M){
        if(P!=Root){
            RTree* PP= new RTree(P->P,M);
            P->SplitBranch(PP);
            P->AdjustTree(PP,Root);
        }
        else{
            if(P!=this)
                P->SplitRoot();
        }
    }
}

void RTree::AdjustTree(Point E){
    RTree *N=this;
    do{
        N=N->P;
        N->Enlarge(E);
    }
    while(N->P!=N);
    N->Enlarge(E);
}

void RTree::Insert(coordenada a, coordenada b){
    Point E=Point(a,b);
    if(branches.size()==0){
        if(points.size()==0){
            points.push_back(E);
            space=rectangle(E,E);
        }
        else{
            if(points.size()<M)
                InsertPoint(E);
            else{
                RTree* N=new RTree(this,M);
                N->points=points;
                N->space=rectangle(N->points[0],points[0]);
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
        N->Enlarge(E);
        RTree* NN=nullptr;
        if(N->points.size()>M){
            N->SplitLeaf(NN);
        }
        N->AdjustTree(E);
        if(NN){
            N->AdjustTree(NN, this);
        }
    }
}

void RTree::Delete(){

}

bool RTree::onCircle(Point punto, float distancia){
    return euclidean(punto, Point(space.minX,space.maxY)) <= distancia && euclidean(punto, Point(space.minX,space.minY)) <= distancia && euclidean(punto, Point(space.maxX,space.maxY)) <= distancia && euclidean(punto, Point(space.maxX,space.minY)) <= distancia;
}

bool RTree::inRegion(Point punto, float distancia) {
    bool c1 = punto.getX() >= space.minX && punto.getX() <= space.maxX && punto.getY() >= space.minY && punto.getY() <= space.maxY;
    if (!c1) {
        c1 = (punto.getX()<space.minX && punto.getX()+distancia>space.minX) || (punto.getX() > space.maxX && punto.getX() - distancia < space.maxX) || (punto.getY() < space.minY && punto.getY() + distancia > space.minY) || (punto.getY() > space.maxY && punto.getY() - distancia < space.maxY);
        bool c2 = euclidean(punto, Point(space.minX,space.maxY)) <= distancia || euclidean(punto, Point(space.minX,space.minY)) <= distancia || euclidean(punto, Point(space.maxX,space.maxY)) <= distancia || euclidean(punto, Point(space.minX,space.minY)) <= distancia;
        c1 = c1 || c2;
    }
    return c1;
}

vector<Point> RTree::Search(Point centro, float radio){
    vector<Point> puntos;
    if(onCircle(centro,radio)){
        return getPoints();
    }
    else if (inRegion(centro, radio)) {
        if (branches.size()==0) {
            for (size_t i = 0; i < points.size(); ++i) {
                if (euclidean(points[i], centro) <= radio)
                    puntos.push_back(points[i]);
            }
        }
        else {
            vector<Point> aux;
            for (int i = 0; i < branches.size(); ++i) {
                aux = branches[i]->Search(centro, radio);
                puntos.insert(puntos.end(),aux.begin(),aux.end());
            }
        }
    }
    return puntos;
}

vector<Line> RTree::getLines(){
    vector<Line> lines;
    Point a(space.minX,space.minY),
          b(space.maxX,space.minY),
          c(space.maxX,space.maxY),
          d(space.minX,space.maxY);
          lines.push_back(Line(a,b));
          lines.push_back(Line(b,c));
          lines.push_back(Line(c,d));
          lines.push_back(Line(a,d));
    if(branches.size()>0){
        for(int i=0;i<branches.size();++i){
            vector<Line> aux=branches[i]->getLines();
            lines.insert(lines.end(),aux.begin(),aux.end());
        }
    }
    //else{

    //
    return lines;
}

void RTree::PrintTree(){
    if(points.size()>0){
            cout<<"[";
        for(size_t i=0;i<points.size();++i){
            cout<<" "<<points[i]<<" ";
        }
        cout<<"]"<<endl;
    }
    else{
        for(size_t i=0;i<branches.size();++i){
            branches[i]->PrintTree();
        }
    }
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


