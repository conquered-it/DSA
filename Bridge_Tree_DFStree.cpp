/**

Implementation of Bridge Tree (using DFS Tree)
G contains original graph
GN contains final tree
vector<pair<int,int>>edge contains bridge edges

**/
#include<bits/stdc++.h>
using namespace std;
#define M 300001
#define pb push_back
int n,m,u,v,c,id[M],up[M],dwn[M],tin[M],dp[M],P[M];
bool vis[M],vis2[M];
vector<int>G[M],GT[M],GN[M];
vector<pair<int,int>>edge;
void dfs(int i,int p){
    P[i]=p;
    vis[i]=1;
    tin[i]=++c;
    for(int j:G[i]){
        if(j==p) continue;
        if(!vis[j]) dfs(j,i);
        else if(tin[i]<=tin[j]) ++up[j],++dwn[i];
    }
}
void dfs2(int i,int p){
    vis2[i]=1;
    dp[i]=up[i]-dwn[i];
    for(int j:G[i]){
        if(j==p) continue;
        if(!vis2[j]){
            dfs2(j,i);
            dp[i]+=dp[j];
        }
    }
}
void dfs3(int i,int p){
    id[i]=p;
    for(int j:GT[i]) dfs3(j,p);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>u>>v;
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(1,0);
    dfs2(1,0);
    for(int i=2;i<=n;++i){
        if(dp[i]) GT[P[i]].pb(i);
    }
    for(int i=1;i<=n;++i){
        if(!id[i]) dfs3(i,i);
    }
    for(int i=1;i<=n;++i){
        for(int j:G[i]) if(id[i]!=id[j]) GN[id[i]].pb(id[j]);
    }
    for(int i=1;i<=n;++i) if(dp[i]==0 && P[i]!=0) edge.pb({P[i],i});
    for(int i=1;i<=n;++i){
        cout<<i<<"-> ";
        for(int j:GN[i]) cout<<j<<' ';
        cout<<'\n';
    }
    cout<<"\nBridge Edges\n";
    for(auto it:edge) cout<<it.first<<' '<<it.second<<'\n';
}