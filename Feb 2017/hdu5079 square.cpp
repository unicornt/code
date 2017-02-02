#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb(x) push_back(x)
#define clr(x,y) memset(x,y,sizeof(x))
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define showtime fprintf(stderr,"time = %.15f\n",clock()/(double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
template<class Ty>inline void rd(Ty&res)
{
	res=0;char c;
	bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar();
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
const int M=10;
const int mod=1e9+7;
int n;
int A[M][M],dp[M][5000],temp[M],col[M],tmp[M];
char s[M];
void mod_add(int&x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
void solve()
{
	rd(n);
	rep(i,1,n+1)
	{
		scanf("%s",s+1);
		rep(j,1,n+1) 
			if(s[j]=='*') A[i][j]=1;
			else A[i][j]=0;
	}
	puts("1");
	int last=1;
	rep(k,2,n+2)
	{//最大的白色子正方形的边长<k
		clr(dp,0);
		dp[0][0]=1;
		//每个位置的取值范围为[0,k)
		//状态总数为k^(n-k+1)
		int tot=1;
		rep(i,0,n-k+2) tot*=k;
		rep(i,1,n+1)
		{//枚举行
			rep(S,0,tot)
			{//枚举上一行的状态
				if(dp[i-1][S]==0) continue;
				for(int j=n-k+1,s=S;j>=1;j--,s/=k) temp[j]=s%k;
				rep(T,0,1<<n)
				{//枚举当前行的染色情况
					//dig("S %d T %d\n",S,T);
					rep(j,0,n) if(T&(1<<j))
					{
						col[j+1]=1;
						rep(w,max(0,j-k+1),j) col[w+1]=1;
					}
					else if(A[i][j+1]==1) goto end;
					else col[j+1]=0;
					int now;
					now=0;
					rep(j,1,n-k+2)
					{
						if(col[j]==0) tmp[j]=temp[j]+1;
						else tmp[j]=0;
						if(tmp[j]>=k) goto end;
						now=now*k+tmp[j];
					}
					mod_add(dp[i][now],dp[i-1][S]);
					end:;
				}
			}
		}
		int res=0;
		rep(S,0,tot)
			mod_add(res,dp[n][S]);
		printf("%d\n",(res-last+mod)%mod);
		last=res;
	}
}
int main()
{
	int T;
	for(rd(T);T;T--) solve();
	return 0;
}
