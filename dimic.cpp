/**
Implementation of Dimic with Scaling algorithm
**/
#include<bits/stdc++.h>
using namespace std;
#define ll int64_t
const int M = 4000;
ll flow;
int n,m,x,y,src,sink,lim,d[M],pt[M],arr[101],inf = 1e9;
set<pair<int,int>>good;
struct edge {
    int a,b,f,c;
};
struct vertex{
    int val,index;
};
vector<vertex>V{{0,0},{0,1}};
vector <edge> e;
vector <int> g[M];
queue <int> q;
void add_edge(int a, int b, int c) {                                                                           
    edge ed;
    ed.a = a; ed.b = b; ed.f = 0; ed.c = c;
    g[a].push_back(e.size());
    e.push_back(ed);
    ed.a = b; ed.b = a; ed.f = c; ed.c = c;
    g[b].push_back(e.size());
    e.push_back(ed);
}

bool bfs() {
    for (int i = src; i <= sink; i++) d[i]=inf;
    d[src]=0;
    q.push(src);
    while (!q.empty() && d[sink]==inf) {
        int cur = q.front(); q.pop();
        for (size_t i = 0; i < g[cur].size(); i++) {
            int id = g[cur][i];
            int to = e[id].b;
            if (d[to] == inf && e[id].c - e[id].f >= lim) {
                d[to] = d[cur] + 1;
                q.push(to);
            }
        }
    }
    while (!q.empty())  q.pop();
    return d[sink]!=inf;
}

bool dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == sink) return 1;
    for (; pt[v] < g[v].size(); pt[v]++) {
        int id = g[v][pt[v]];
        int to = e[id].b;
        if (d[to] == d[v] + 1 && e[id].c - e[id].f >= flow) {
            int pushed = dfs(to, flow); 
            if (pushed) {
                e[id].f += flow;
                e[id ^ 1].f -= flow;
                return 1;
            }               
        }
    }
    return 0;
}

void dinic() {
    for (lim = (1 << 30); lim >= 1;) {
        if (!bfs()) {
            lim >>= 1;
            continue;
        }
        for (int i = src; i <= sink; i++) pt[i] = 0;
        int pushed;
        while (pushed = dfs(src, lim)) { 
            flow = flow + lim;
        }
    }
}

void make_vertex(int x,int i){
    ll d=2;
    while(d*d<=x){
        while(x%d==0){
            V.push_back({(int)d,i});
            x/=d;
        }
        ++d;
    }
    if(x!=1) V.push_back({x,i});
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>arr[i];
        make_vertex(arr[i],i);
    }
    for(int i=1;i<=m;++i){
        cin>>x>>y;
        if(y&1) swap(x,y);
        good.insert({x,y});
    }
    int tmp=V.size();
    V.push_back({0,tmp});
    for(int i=2;i<V.size()-1;++i){
        for(int j=2;j<V.size()-1;++j){
            if(V[i].val==V[j].val && good.count({V[i].index,V[j].index}))
                add_edge(i,j,1);
        }
    }
    for(int i=2;i<V.size()-1;++i){
        if(V[i].index&1) add_edge(1,i,1);
        else add_edge(i,V.size()-1,1);
    }
    src=1,sink=V.size()-1;
    dinic();
    cout<<flow<<endl;
}



/*

more accurate

#include<bits/stdc++.h>
using namespace std;
#define ll int64_t
const ll M = 4000;
#define ld long double
const int N = 200500;
 
using namespace std;
 
struct edge
{
    int a, b, cap, flow;
};
 
int n,src,sink,x,y,w,m,X,d[N],pt[N];
vector<edge> e;
vector<int> g[N];
vector<vector<int>>EDGES;
 
void add_edge(int a, int b, int cap)
{
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back(e.size());
    e.push_back(e1);
    g[b].push_back(e.size());
    e.push_back(e2);
}
 
bool bfs()
{
    for (int i=0;i<=n;++i) d[i]=-1;
    d[src]=0;
    queue<int>qu;
    qu.push(src);
    while (qu.size())
    {
        int v=qu.front();
        qu.pop();
        for (int i=0;i<g[v].size();++i)
        {
            int id=g[v][i];
            int to=e[id].b;
            if (d[to]==-1 && e[id].flow<e[id].cap)
            {
                d[to]=d[v]+1;
                qu.push(to);
            }
        }
    }
    return d[sink]!=-1;
}
 
int dfs(int v, int flow)
{
    if (v==sink || flow==0) return flow;
    for (;pt[v]<g[v].size();++pt[v])
    {
        int id = g[v][pt[v]],to = e[id].b;
        if (d[to]!=d[v]+1) continue;
        int pushed=dfs(to,min(flow, e[id].cap-e[id].flow));
        if (pushed){
            e[id].flow+=pushed;
            e[id^1].flow-=pushed;
            return pushed;
        }
    }
    return 0;
}
 
int dinic()
{
    int flow = 0;
    while (1)
    {
        if(!bfs()) break;
        for (int i=0;i<=n;++i) pt[i]=0;
        while (1)
        {
            int pushed = dfs(src, 10000);
            if (!pushed)
                break;
            flow += pushed;
        }
    }
    return flow;
}
*/
