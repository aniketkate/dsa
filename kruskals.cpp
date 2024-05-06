
#include <bits/stdc++.h>
using namespace std;
#define n 4


namespace s1{
    vector<int> parent(n);
    vector<int> rank(n);
}


struct edge{
    int source;
    int destination;
    int weight;
};

struct comp{
    bool operator()(const edge* lhs,const edge* rhs)const{
        return lhs->weight > rhs->weight;
    }
};

edge* createedge(int source,int destination,int weight){
    edge* cedge = new edge;
    cedge->source=source;
    cedge->destination=destination;
    cedge->weight=weight;
    return cedge;
}

class graph{
    public:
    vector<vector<int>> mst;
    vector<int> vertices = {0,1,2,3};
    //int n = vertices.size();
    priority_queue<edge*,std::vector<edge*>,comp> pq;
    
    void addedge(int source,int destination,int weight){
        edge* cedge = createedge(source,destination,weight);
        pq.push(cedge);
    }
    
    int find(int x){
        if(s1::parent[x]==-1){
            return x;
        }
        return s1::parent[x] = find(s1::parent[x]);
    }
    
    void unite(int u,int v){
        int p1 = find(u);
        int p2 = find(v);
        
        if(p1!=p2){
            if(s1::rank[p1]<s1::rank[p2]){
                s1::parent[u]=v;
            }
            else if(s1::rank[p1]>s1::rank[p2]){
                s1::parent[v]=u;
            }
            else{
                s1::parent[v]=u;
                s1::rank[u]++;
            }
        }
    }
    
    
    
    void kruskal(){
        int ans=0;
        int w=0;
        
        for(int i = 0 ; i < n;i++){
            s1::parent[i]=-1;
            s1::rank[i]=0;
        }
        
        while(ans!=(n-1)){
            edge* min = pq.top();
            pq.pop();
            
            int p1 = find(min->source);
            int p2 = find(min->destination);
            
            if(p1!=p2){
                unite(min->source,min->destination);
                ans++;
                w=w+min->weight;
                cout<<"From "<<min->source<<" to "<<min->destination<<" with "<<min->weight<<" \n";
            }
            //cout<<"h ";
        }
        cout<<"The weight of the MST is :"<<w;
    }
};

int main() {
    graph g;
    g.addedge(0, 1, 10); 
    g.addedge(1, 3, 15); 
    g.addedge(2, 3, 4); 
    g.addedge(2, 0, 6); 
    g.addedge(0, 3, 5); 
    g.kruskal();
    
    return 0;
}
