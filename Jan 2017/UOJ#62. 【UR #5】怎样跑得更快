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
const int mod=7*17*(1<<23)+1;
int fast_mod_pow(int a,int b)
{
	int res=1;
	for(int bas=a;b;b>>=1,bas=(ll)bas*bas%mod) if(b&1) res=(ll)res*bas%mod;
	return res;
}
#define minus sfefe
const int M=100000;
int n,c,d;
int b[M+5],g[M+5],ng[M+5],f[M+5],fr[M+5],fz[M+5],hx[M+5],z[M+5],x[M+5],nfr[M+5];
void minus(int &x,int y)
{
	x-=y;
	if(x<0) x+=mod;
}
void init()
{
	c%=mod-1;
	d%=mod-1;
	c=(c-d+mod-1)%(mod-1);
	rep(i,1,n+1)
	{
		g[i]=fast_mod_pow(i,d);
		f[i]=fast_mod_pow(i,c);
		ng[i]=fast_mod_pow(i,mod-1-d);
	}
	//f(n)=sum_{d|n}fr(d)
	//f(d)=f(n)-sum_{d|n,d<n}fr(d)
	rep(i,1,n+1) fr[i]=f[i];
	rep(i,1,n+1) for(int j=i+i;j<=n;j+=i) minus(fr[j],fr[i]);
	rep(i,1,n+1) nfr[i]=fast_mod_pow(fr[i],mod-2);
}
void solve()
{
	rep(i,1,n+1) rd(b[i]);
	//求fr(d)*zd
	rep(i,1,n+1) fz[i]=(ll)b[i]*ng[i]%mod;
	rep(i,1,n+1) for(int j=i+i;j<=n;j+=i) minus(fz[j],fz[i]);
	rep(i,1,n+1)
	{
		if(fr[i]) z[i]=(ll)fz[i]*nfr[i]%mod;
		else if(fz[i])
		{
			puts("-1");
			return;
		}
	}
	rep(i,1,n+1) hx[i]=z[i];
	per(i,1,n+1) for(int j=i+i;j<=n;j+=i) minus(hx[i],hx[j]);
	rep(i,1,n+1) x[i]=(ll)hx[i]*ng[i]%mod;
	rep(i,1,n+1) printf("%d ",x[i]);
	puts("");
}
int main()
{
#ifdef unicornt
	freopen("ex_equation2.in","r",stdin);
	freopen("equation.out","w",stdout);
#endif
	int q;
	rd(n),rd(c),rd(d),rd(q);
	init();
	while(q--) solve();
	return 0;
}
