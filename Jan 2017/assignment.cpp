#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
typedef long long ll;
typedef long double ldb;
int n,m;
const int M=250;
ldb dp[M+5][M+5];
ldb calc(int k)
{
	dp[0][0]=1;
	rep(i,1,m+1)
	{
		rep(j,1,i+1)
		{
			if(i>=k+1) dp[i][j]=dp[i-1][j-1]+dp[i-1][j]-dp[i-k-1][j-1];
			else dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
		}
	}
	ldb res=0;
	ldb C=1;
	rep(i,1,m+1)
	{
		if(i>n) break;
		C=C*(n-i+1)/i;
		res+=dp[m][i]*C;
	}
	return res;
}
void solve()
{
	scanf("%d%d",&m,&n);
	ldb tot=calc(m);
	ldb last=0;
	ldb ans=0;
	rep(i,1,m)
	{
		ldb now=calc(i);
		ans+=(now-last)*i/tot;
		last=now;
	}
	ans+=(tot-last)*m/tot;
	printf("%.10Lf\n",ans);
}
int main()
{
//	freopen("assignment.in","r",stdin);
//	freopen("assignment.out","w",stdout);
	int T;
	for(scanf("%d",&T);T;T--) solve();
	return 0;
}
