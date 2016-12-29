#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define pq priority_queue
#define lowbit(x) ((x)&-(x))
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl 
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
#define rep(i,a,b) for(int i=a,i##_BEGIN_=b;i<i##_BEGIN_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_END_=a;i>=i##_END_;--i)
using namespace std;
const int mod=1e9+7;
const int MAX_INT=0x7fffffff,INF=1e9;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
void print(int x)
{
    if(!x) return;
    print(x/10);
    putchar(x%10^48);
}
inline void pt(int x)
{
    if(!x) putchar('0');
    else print(x);
    putchar('\n');
}
inline void rd(int&res)
{
    res=0;char c;
    while(c=getchar(),c<48);
    do res=res*10+(c^48);
    while(c=getchar(),c>47);
}
template<class Ty>inline void chk_min(Ty&x,Ty y){if(x>y)x=y;}
template<class Ty>inline void chk_max(Ty&x,Ty y){if(x<y)x=y;}
const int M=2005;
const int S=40005;
int mp[M],mi[M],mx[M],bk[S+S];
double dp[2][M];
double sqr(int x)
{
    return (double)x*x;
}
int A[M],B[M],C[M],D[M];
int main()
{
    int n;
    scanf("%d",&n);
    rep(i,0,n+1) mi[i]=-1,mx[i]=1e9;
    rep(i,1,n+1)
        scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
    int sx,sy,tx,ty;
    scanf("%d%d",&sx,&sy);
    scanf("%d%d",&tx,&ty);
    int cnt=1;
    memset(bk,-1,sizeof(bk));
    mp[0]=sx;
    bk[sx+S]=0;
    rep(i,1,n+1) if(bk[A[i]+S]==-1&&A[i]>sx&&A[i]<tx)
    {
        bk[A[i]+S]=cnt;
        mp[cnt++]=A[i];
    }
    bk[tx+S]=cnt;
    mp[cnt]=tx;
    rep(i,1,n+1)
    {
        if(A[i]<sx&&C[i]>sx)
        {
            mx[0]=D[i];
            mi[0]=B[i];
        }
        if(A[i]<tx&&C[i]>tx)
        {
            mx[cnt]=D[i];
            mi[cnt]=B[i];
        }
    }
    rep(i,1,n+1)
    {
        if(A[i]<sx||C[i]>tx) continue;
        if(bk[A[i]+S]!=-1)
        {
            chk_max(mi[bk[A[i]+S]],B[i]);
            chk_min(mx[bk[A[i]+S]],D[i]);
        }
        if(bk[C[i]+S]!=-1)
        {
            chk_max(mi[bk[C[i]+S]],B[i]);
            chk_min(mx[bk[C[i]+S]],D[i]);
        }
    }
    double v;
    scanf("%lf",&v);
    if(sy>=mi[0]&&sy<=mx[0])
    {
        chk_max(mi[0],sy);
        chk_min(mx[0],sy);
    }
    if(ty>=mi[cnt]&&ty<=mx[cnt])
    {
        chk_max(mi[cnt],ty);
        chk_min(mx[cnt],ty);
    }
    rep(i,0,cnt+1) dp[0][i]=dp[1][i]=1e10;
    if(sy>=mi[0]&&sy<=mx[0]) dp[0][0]=dp[1][0]=0;
    else
    {
        dp[0][0]=fabs(sy-mx[0]);
        dp[1][0]=fabs(sy-mi[0]);//0 -> upper  ,  1 -> lower
    }
    rep(i,0,cnt+1)
    {
        int id1=-1,id2=-1;
        rep(j,i+1,cnt+1)
        {
            if(id1==-1)
            {
                id1=id2=j;
                chk_min(dp[0][j],dp[0][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mx[j]-mx[i])));
                chk_min(dp[1][j],dp[0][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mi[j]-mx[i])));
            }
            else
            {
                if((mx[j]-mx[i])*(mp[id1]-mp[i])<=(mp[j]-mp[i])*(mx[id1]-mx[i]))
                {
                    id1=j;
                    if((mx[j]-mx[i])*(mp[id2]-mp[i])>=(mp[j]-mp[i])*(mi[id2]-mx[i]))
                        chk_min(dp[0][j],dp[0][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mx[j]-mx[i])));
                }
                if((mi[j]-mx[i])*(mp[id2]-mp[i])>=(mp[j]-mp[i])*(mi[id2]-mx[i]))
                {
                    id2=j;
                    if((mi[j]-mx[i])*(mp[id1]-mp[i])<=(mp[j]-mp[i])*(mx[id1]-mx[i]))
                        chk_min(dp[1][j],dp[0][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mi[j]-mx[i])));
                }
            }
        }
        id1=-1,id2=-1;
        rep(j,i+1,cnt+1)
        {
            if(id1==-1)
            {
                id1=id2=j;
                chk_min(dp[0][j],dp[1][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mx[j]-mi[i])));
                chk_min(dp[1][j],dp[1][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mi[j]-mi[i])));
            }
            else
            {
                if((mx[j]-mi[i])*(mp[id1]-mp[i])<=(mp[j]-mp[i])*(mx[id1]-mi[i]))
                {
                    id1=j;
                    if((mx[j]-mi[i])*(mp[id2]-mp[i])>=(mp[j]-mp[i])*(mi[id2]-mi[i]))
                        chk_min(dp[0][j],dp[1][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mx[j]-mi[i])));
                }
                if((mi[j]-mi[i])*(mp[id2]-mp[i])>=(mp[j]-mp[i])*(mi[id2]-mi[i]))
                {
                    id2=j;
                    if((mi[j]-mi[i])*(mp[id1]-mp[i])<=(mp[j]-mp[i])*(mx[id1]-mi[i]))
                        chk_min(dp[1][j],dp[1][i]+sqrt(sqr(mp[j]-mp[i])+sqr(mi[j]-mi[i])));
                }
            }
        }
    }
    if(ty>=mi[cnt]&&ty<=mx[cnt]);
    else
    {
        dp[0][cnt]+=fabs(ty-mx[cnt]);
        dp[1][cnt]+=fabs(ty-mi[cnt]);//0 -> upper  ,  1 -> lower
    }
    printf("%.8f\n",min(dp[0][cnt],dp[1][cnt])/v);
    return 0;
}
