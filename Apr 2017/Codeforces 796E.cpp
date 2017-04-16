#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#define fi first
#define se second
#define clr(x,y) memset(x,y,sizeof(x))
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=5000;
typedef long long ll;
typedef pair<int,int> pii;
int n,m;
inline void rd(int&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar();
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
int A[M+5],deq[M+5];
pii B[M+5];
ll sum[M+5],dp[M+5][M+5],val[M+5];
int main()
{
	rd(n);rd(m);
	rep(i,1,n+1) rd(A[i]);
	rep(i,1,m+1) rd(B[i].fi),rd(B[i].se);
	sort(A+1,A+n+1);
	sort(B+1,B+m+1);
	clr(dp[0],127);
	dp[0][0]=0;
	rep(i,1,m+1)
	{
		rep(j,1,n+1) sum[j]=sum[j-1]+abs(B[i].fi-A[j]);
//		per(j,1,n+1)
//		{
//			dp[i][j]=dp[i-1][j];
//			rep(k,max(0,j-B[i].se),j)
//			{
//				dp[i][j]=min(dp[i][j],dp[i-1][k]+sum[j]-sum[k]);
//			}
//		}
		
		//队列中维护dp[i-1][k]-sum[k]
		//从头弹出下标小于j-B[i].se的点
		//维护一个单调递增的队列
		int qt=0,qh=0;
		deq[qh]=0;
		val[qh++]=0;
		rep(j,1,n+1)
		{
			dp[i][j]=dp[i-1][j];
			while(qt<qh&&deq[qt]<j-B[i].se) qt++;
			if(qt<qh) dp[i][j]=min(dp[i][j],val[qt]+sum[j]);
			ll tmp=dp[i-1][j]-sum[j];
			while(qt<qh&&val[qh-1]>=tmp) qh--;
			val[qh]=tmp;
			deq[qh++]=j;
		} 
	}
	if(dp[m][n]==9187201950435737471) dp[m][n]=-1;
	printf("%I64d\n",dp[m][n]);
	return 0;
}
