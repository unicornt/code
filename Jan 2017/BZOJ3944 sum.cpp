/*
	tags: 杜教筛,线性筛
	notes: n<=1^31-1,(n+1)*n/2 boom!
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const int M=1664511;//(2^31-1)^(2/3)
const int N=1300;
typedef long long ll;
int n;
ll s_phi[M+5],s_mu[M+5];
ll sum_phi[N],sum_mu[N];//(2^31-1)^(1/3)
int arr[N],tot;
void calc(int x)
{
	if(x<M) return;
	int k=n/x;
	if(sum_phi[k]!=-1) return;
	arr[tot++]=k;
	ll &res1=sum_phi[k],&res2=sum_mu[k];
	res1=((ll)x+1)*x/2;
	res2=1;
	for(unsigned i=2,lst;i<=x;i=lst+1)
	{
		int val=x/i;
		lst=x/val;
		if(val>M)
		{
			calc(val);
			val=n/val;
			res1-=sum_phi[val]*(lst-i+1);
			res2-=sum_mu[val]*(lst-i+1);
		}
		else
		{
			res1-=s_phi[val]*(lst-i+1);
			res2-=s_mu[val]*(lst-i+1);
		}
	}
}
void solve()
{
	tot=0;
	scanf("%d",&n);
	calc(n);
	if(n>M) printf("%lld %lld\n",sum_phi[1],sum_mu[1]);
	else printf("%lld %lld\n",s_phi[n],s_mu[n]);
	rep(i,0,tot) sum_mu[arr[i]]=sum_phi[arr[i]]=-1;
}
int prime[M+5],tot_prime,mi_prime[M+5],pow_prime[M+5],phi[M+5],mu[M+5];
void sieve()
{
	s_phi[1]=phi[1]=1;
	s_mu[1]=mu[1]=1;
	rep(i,2,M)
	{
		if(!mi_prime[i])
			mi_prime[i]=prime[tot_prime++]=pow_prime[i]=i;
		if(pow_prime[i]==i)
		{//p^t
			phi[i]=i/mi_prime[i]*(mi_prime[i]-1);
			if(pow_prime[i]!=mi_prime[i]) mu[i]=0;
			else mu[i]=-1;
		}
		else
		{
			int k=i/pow_prime[i];
			phi[i]=phi[k]*phi[pow_prime[i]];
			mu[i]=mu[k]*mu[pow_prime[i]];
		}
		s_phi[i]=s_phi[i-1]+phi[i];
		s_mu[i]=s_mu[i-1]+mu[i];
		for(int j=0,p,prod;j<tot_prime&&(p=prime[j])<=mi_prime[i]&&(prod=i*p)<M;++j)
		{
			mi_prime[prod]=p;
			pow_prime[prod]=(p==mi_prime[i]?pow_prime[i]*p:p);
		}
//		if(i<10) prt(mu[i]);
	}
}
int main()
{
	int T;
	sieve();
	memset(sum_phi,-1,sizeof sum_phi);
	memset(sum_mu,-1,sizeof sum_mu);
	for(scanf("%d",&T);T;T--) solve();
	return 0;
}
