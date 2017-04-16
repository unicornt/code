#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const int M=100000;
const int S=300;
int dp[M+5][S+5];
int n;
int A[M+5];
int rec(int p,int k)
{
	if(p>n) return 0;
	if(k<=S)
	{
		if(dp[p][k]!=-1) return dp[p][k];
		dp[p][k]=rec(p+A[p]+k,k)+1;
	}
	else return rec(p+A[p]+k,k)+1;
}
int main()
{
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",&A[i]);
	int q;
	scanf("%d",&q);
	clr(dp,-1);
	rep(i,0,q)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",rec(a,b));
	}
	return 0;
}
