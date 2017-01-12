/*
	tags: 贪心,dp
*/
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define fi first
#define se second
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int M=2000;
const ll INF=1LL<<62;
int v[M+5],dp[M+5];
ll sum[M+5];
bool f[105][105];
void chk_min(ll&x,ll y)
{
	if(x>y) x=y;
}
int main()
{
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B);
	rep(i,1,n+1)
	{
		scanf("%d",&v[i]);
		sum[i]=sum[i-1]+v[i];
	}
	ll T=0,ans=0;
	per(bit,0,41)
	{
		T|=(1LL<<bit);
		if(A!=1)
		{
			rep(i,1,n+1) rep(j,0,B+1) f[i][j]=0;
			f[0][0]=1;
			rep(i,1,n+1)
			{
				rep(j,0,i)
				{
					if((((sum[i]-sum[j])&T)|ans)==ans)
						rep(k,0,min(j+1,B)) f[i][k+1]|=f[j][k];
				}
			}
			bool ok=0;
			rep(i,A,B+1) ok|=f[n][i];
			if(!ok) ans|=1LL<<bit;
		}
		else
		{
			rep(i,0,n+1) dp[i]=0x7fffffff;
			dp[0]=0;
			rep(j,0,n) if(dp[j]<B&&dp[j]!=INF)
			{
				rep(i,j+1,n+1) if((((sum[i]-sum[j])&T)|ans)==ans)
					dp[i]=min(dp[i],dp[j]+1);
			}
			if(dp[n]>B) ans|=1LL<<bit;
		}
	}
	pts(ans);
	return 0;
}
