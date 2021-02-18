/**

Bellman ford implementation

Max bellman ford example -> https://codeforces.com/problemset/problem/301/B ,
                 solution -> https://codeforces.com/contest/301/submission/107751144

**/

#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
bool isneg=0;
vector<int>bellman_ford(int v,int src,vector<pair<pair<int,int>,int>>&edges){
    vector<int>dist(v+1,2e9);
    dist[src]=0;
    for(int i=0;i<v-1;++i){
        for(auto it:edges){
            int u=it.F.F,v=it.F.S,w=it.S;
            if(dist[u]!=2e9 && dist[v]>dist[u]+w)
                dist[v]=dist[u]+w;
        }
    }

    // negative cycle detection
    for(auto it:edges){
         int u=it.F.F,v=it.F.S,w=it.S;
            if(dist[u]!=2e9 && dist[v]>dist[u]+w){
                isneg=1;
                break;
            }
    }
    return dist;
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,m,u,v,w;
    vector<pair<pair<int,int>,int>>edges;
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>u>>v>>w;
        edges.push_back({{u,v},w});
    }
    vector<int>dist=bellman_ford(n,1,edges);
    for(int i=1;i<=n;++i) cout<<dist[i]<<' ';
    cout<<"\n\n";
    cout<<isneg;
    // dist contains final distances
    // isneg indicates if nrgative cycle present or not
}
