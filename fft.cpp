#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define md 998244353
ll n,prm[1000];
ll pw(ll a,ll b){
    if(!b) return 1;
    if(b&1) return (a*pw(a,b-1))%md;
    ll temp=pw(a,b/2);
    return (temp*temp)%md;
}

ll inv(ll a){
    return pw(a,md-2);
}

ll getRoot(ll n){
    ll tmp=n-1,tot=0;
    for(ll i=2;i<=sqrt(tmp);++i){
        if(tmp%i==0){
            prm[++tot]=i;
            while(tmp%i==0) tmp/=i;
        }
    }
    if (tmp!=1) prm[++tot]=tmp;
    for(ll g=2;g<=n-1;++g){
        bool ok=1;
        for(int i=1;i<=tot;++i)
            if(pw(g,(n-1)/prm[i])==1) {ok=0; break;} 
        
        if(ok) return g;
    } 
    return 0;
}

void fft(vector<ll>&a,ll n,bool inverse,ll x){
    for(int i=0;i<n;++i){
        ll y=0;
        for(int j=0;j<__builtin_ctzll(n);++j)
            if((1ll<<j)&i) y|=(1ll<<(__builtin_ctzll(n)-j-1));
        if(y>i) swap(a[i],a[y]);
    }
    if(inverse) x=inv(x);
    for(int s=1;s<=__builtin_ctzll(n);++s){
        ll y=pw(x,n/(1ll<<s));
        for(int j=0;j<n/(1ll<<s);++j){
            ll r=1;
            for(int i=0;i<(1ll<<(s-1));++i){
                ll u=a[i+j*(1ll<<s)],v=(r*a[i+j*(1ll<<s)+(1ll<<(s-1))])%md;
                a[i+j*(1ll<<s)]=u+v;
                a[i+j*(1ll<<s)]%=md;
                a[i+j*(1ll<<s)+(1ll<<(s-1))]=u-v;
                if(a[i+j*(1ll<<s)+(1ll<<(s-1))]<0) a[i+j*(1ll<<s)+(1ll<<(s-1))]+=md;
                r*=y;
                r%=md;
            }
        }
    }
    if(inverse){
        ll invn=inv(n);
        for(int i=0;i<n;++i) a[i]=(a[i]*invn)%md;
    }
    return;
}

void polymul(vector<ll>&a,vector<ll>&b,vector<ll>&v,ll x){
    ll n=1<<(ll)(ceil(log2(a.size()+b.size())));
    vector<ll>fa=a,fb=b;
    fa.resize(n,0);
    fb.resize(n,0);
    ll y=pw(x,(md-1)/n);
    fft(fa,n,0,y);
    fft(fb,n,0,y);
    v.resize(n,0);
    for(int i=0;i<n;++i)
        v[i]=(fa[i]*fb[i])%md;
    fft(v,n,1,y);
    v.resize(a.size()+b.size()-1,0);
    return;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);  
    vector<ll>a={1,2,3,1};
    vector<ll>b={3,4,1,2,4};
    vector<ll>c;
    polymul(a,b,c,getRoot(md));
    for(int i=0;i<c.size();++i) cout<<c[i]<<' ';
    return 0;
}