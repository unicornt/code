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
#define lowbit(x) ((x)&(-(x)))
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
const int M=15;
const int N=1<<M;
const int mod=1e9+7;
int in[N+5],out[N+5],h[N+5],g[N+5],f[N+5],bitcnt[N+5],mod_pow[M*M+5],w[N+5];
int n,m;
void mod_minus(int&x,int y)
{
	x-=y;
	if(x<0) x+=mod;
}
void mod_add(int&x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
int main()
{
#ifdef unicornt
	freopen("ex_scon1.in","r",stdin);
#endif
	rd(n);rd(m);
	int a,b;
	rep(i,0,m)
	{
		rd(a);rd(b);
		a--;b--;
		out[1<<a]|=1<<b;
		in[1<<b]|=1<<a;
	}
	mod_pow[0]=1;
	rep(i,1,m+1) mod_pow[i]=mod_pow[i-1]*2%mod;
//	f(S)表示的生成子图强联通的方案数。
//	g(S)表示的生成子图中，若的所有联通块都强联通，则对有贡献，奇数个联通块贡献+1，否则-1。相当与求所有点集为S的子图的系数和。
//	h(S)表示S的诱导子图里的边的个数
	rep(i,0,1<<n) bitcnt[i]=bitcnt[i>>1]+(i&1);
	rep(S,1,1<<n)
	{
		int v=lowbit(S);
		int _S=S^v;
		h[S]=h[_S]+bitcnt[_S&in[v]]+bitcnt[_S&out[v]];
		for(int T=_S;T;T=(T-1)&_S) 
			mod_minus(g[S],(ll)g[T]*f[S^T]%mod);
		f[S]=mod_pow[h[S]];
		//w(T)表示(u,v)的数量，其中u∈S-T,v∈T
		//w(T)=w(T')-bitcnt
		for(int T=S;T;T=(T-1)&S)
		{
			if(T==S) w[T]=0;
			else
			{
				int v=lowbit(S^T);
				int _T=T|v;
				w[T]=w[_T]-bitcnt[in[v]&(S^_T)]+bitcnt[out[v]&T];
			}
			mod_minus(f[S],(ll)mod_pow[h[S^T]+w[T]]*g[T]%mod);
		}
		mod_add(g[S],f[S]);
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}
