#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef long long ll;
const int N=1005;
const int M=10005;
ll A[N][M];
int n,m;
void pivot(int l,int e)
{
    ll tmp=-A[l][e];
    A[l][e]=-1;
    rep(i,0,m+1) A[l][i]/=tmp;
    rep(i,0,n+1)
        if(i!=l)
        {
            tmp=A[i][e];
            A[i][e]=0;
            if(!tmp) continue;
            rep(j,0,m+1) A[i][j]+=tmp*A[l][j];
        }
}
void simplex()
{
    while(true)
    {
        ll mx=0;
        int l=-1,e=-1;
        rep(i,0,m)
            if(A[n][i]>mx) mx=A[n][e=i];
        if(e==-1) break;
        ll mi=1LL<<62;
        rep(i,0,n)
        {
            if(A[i][e]<0)
            {
                ll tmp=-A[i][m]/A[i][e];
                if(tmp<mi) mi=tmp,l=i;
            }
        }
        pivot(l,e);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    rep(i,0,n)
    {
        int x;
        scanf("%d",&x);
        A[i][m]=x;
    }
    rep(i,0,m)
    {
        int l,r,d;
        scanf("%d%d%d",&l,&r,&d);
        l--;
        rep(j,l,r) A[j][i]=-1;
        A[n][i]=d;
    }
    simplex();
    printf("%lld\n",A[n][m]);
    return 0;
}
