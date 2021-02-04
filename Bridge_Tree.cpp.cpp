/**
Implementation of Bridge Tree (using DSU)

G contains original graph
GN contains final tree
vector<pair<int,int>>edge contains bridge edges

**/

#include<bits/stdc++.h>
using namespace std;
#define M 300001
int n,m,x,y,c,tin[M],tout[M],temp[M],sz[M],P[M];
vector<pair<int,int>>edge;
vector<int>G[M],GN[M];
int get(int x){
    return x==P[x]?x:P[x]=get(P[x]);
}

void unite(int x,int y){
    x=get(x);
    y=get(y);
    if(sz[x]<sz[y]) swap(x,y);
    P[y]=x;
    sz[x]+=sz[y];
}

int dfs(int i,int p){
    tin[i]=temp[i]=++c;
    for(auto j:G[i]){
        if(j==p) continue;
        if(tin[j]) temp[i]=min(temp[i],tin[j]);
        else{
            int tmp=dfs(j,i);
            temp[i]=min(temp[i],tmp);
            if(tmp>tin[i]) edge.push_back({i,j});
            else unite(i,j);
        }
    }
    tout[i]=++c;
    return temp[i];
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i) P[i]=i,sz[i]=1;
    for(int i=1;i<=m;++i){
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0);
    for(auto i:edge){
        GN[get(i.first)].push_back(get(i.second));
        GN[get(i.second)].push_back(get(i.first));
    }
    // for(auto i:edge) cout<<get(i.first)<<' '<<get(i.second)<<'\n';
}