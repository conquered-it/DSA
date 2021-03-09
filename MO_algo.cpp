#include<bits/stdc++.h>
using namespace std;
#define ll int64_t
ll n,q,t,l,r,s,id,lft,rgt,v,ans,a[200001],b[450];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>q;
    s=sqrt(n);
    for(int i=1;i<=n;++i){
        cin>>a[i];
        b[i/s+1]+=a[i];
    }
    while(q--){
        cin>>t;
        if(t==1){
            cin>>id>>v;
            b[id/s+1]+=v-a[id];
            a[id]=v;
        }
        else{
            cin>>l>>r;
            ans=0;
            lft=l/s+1,rgt=r/s+1;
            if(lft==rgt){
                for(int i=l;i<=r;++i) ans+=a[i];
            }
            else{
                for(int i=l;;++i){
                    if(i/s+1!=lft) break;
                    ans+=a[i];
                }
                for(int i=r;;--i){
                    if(i/s+1!=rgt) break;
                    ans+=a[i];
                }
                for(int i=lft+1;i<rgt;++i) ans+=b[i];
            }
            cout<<ans<<'\n';
        }
    }
}