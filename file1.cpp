#include<bits/stdc++.h>
using namespace std;
int n,m,kmp[200005],ans[200005];
string s,t,u;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    // find number of occurences for s[1..i] in t , for each i;
    cin>>s>>t;
    n=s.length();
    m=t.length();
    u=s+'.'+t;
    for(int i=1;i<u.length();++i){
        int j=kmp[i-1];
        while(j && u[i]!=u[j]) j=kmp[j-1];
        if(u[i]==u[j]) ++j;
        kmp[i]=j;
    }

    for(int i=n+1;i<u.length();++i) ++ans[kmp[i]];
    for(int i=u.length()-1;i>n;--i){
        ans[kmp[i-n-1]]+=ans[i-n];
    }
    for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
}


/**
// find number no of different substrings in string s in O(n*n)
#include<bits/stdc++.h>
using namespace std;
int n,m,kmp[200005];
string s,t,tmp;
int ans;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>s;
    n=s.length();
    for(int i=0;i<n;++i){
        tmp.push_back(s[i]);
        t=tmp;
        reverse(t.begin(), t.end());
        int mx=0;
        for(int j=1;j<t.length();++j){
            int k=kmp[j-1];
            while(k && t[j]!=t[k]) k=kmp[k-1];
            if(t[j]==t[k]) ++k;
            kmp[j]=k;
            mx=max(mx,k);
        }
        ans+=t.length()-mx;
    }
    cout<<ans;
}




**/
