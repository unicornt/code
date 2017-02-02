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
const int N=1000000;
const int mod=1e9+7;
int n,m;
int prime[N+5],phi[N+5],sum_phi[N+5],mx_pr[N+5],mi_pr[N+5],pow_pr[N+5],tot;
int Sphi[N+5],vis[N+5];
void mod_add(int&x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
void sieve()
{
	tot=0;
	phi[1]=sum_phi[1]=1;
	rep(i,2,N+1)
	{
		if(mi_pr[i]==0)	pow_pr[i]=mx_pr[i]=mi_pr[i]=prime[tot++]=i;
		if(pow_pr[i]==i) phi[i]=i/mi_pr[i]*(mi_pr[i]-1);
		else phi[i]=phi[pow_pr[i]]*phi[i/pow_pr[i]];
		mod_add(sum_phi[i]=sum_phi[i-1],phi[i]);
		for(int j=0,p,prod;j<tot&&(p=prime[j])<=mi_pr[i]&&(prod=i*p)<=N;j++)
		{
			mi_pr[prod]=p;
			pow_pr[prod]=(p==mi_pr[i]?pow_pr[i]*p:p);
			mx_pr[prod]=mx_pr[i];
		}
	}
//	rep(i,1,11) dig("%d ",phi[i]);
//	puts("");
}
int pret(int n)
{
	int ret=1;
	for(int i=n;i>1;ret*=mi_pr[i],i/=pow_pr[i]);
	return ret;
}
int rec(int t)
{
	if(t<=N) return sum_phi[t];
	int&res=Sphi[m/t];
	if(~res) return res;
	res=(ll)(t+1)*t/2%mod;
	for(int i=2,last;i<=t;i=last+1)
	{
		int v=t/i;
		last=t/v;
		res=(res-(ll)(last-i+1)*rec(v))%mod;
	}
	if(res<0) res+=mod;
	return res;
}
int solve(int n,int m)
{
	if(m==0) return 0;
	if(n==1) return rec(m);
	int p=mx_pr[n];
	return ((ll)(p-1)*solve(n/p,m)+solve(n,m/p))%mod;
}
int memo[N+5];
int main()
{
	rd(n);rd(m);
	clr(Sphi,-1);
	clr(memo,-1);
	sieve();
	int ans=0;
	rep(i,1,n+1)
	{
		int t=pret(i);
		int &ret=memo[t];
		if(ret==-1) ret=solve(t,m);
		ans=(ans+(ll)ret*(i/t))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
