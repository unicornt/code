#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
inline void rd(int&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') c=getchar(),flag=true;
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}

const int M=50000;
const int mod=1004535809;
const int mod_g=3;
const double pi=acos(-1.0);
typedef long long ll;
int n;
struct Edge
{
	int to,nxt;
	Edge(int a,int b):to(a),nxt(b){}
	Edge(){}
}edge[M*2+5];
int etot,head[M+5];
void add_edge(int u,int v)
{
	edge[etot]=Edge(v,head[u]);
	head[u]=etot++;
}
bool vis[M+5];
int arr[M+5],tot,siz[M+5],mx[M+5];
void rdfs(int x,int f)
{
	arr[tot++]=x;
	siz[x]=1;
	mx[x]=0;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to]||to==f) continue;
		rdfs(to,x);
		siz[x]+=siz[to];
		mx[x]=max(mx[x],siz[to]);
	}
}
int find_cent(int x)
{
	tot=0;
	rdfs(x,0);
	int cent=x;
	rep(i,0,tot)
	{
		int tar=arr[i];
		mx[tar]=max(mx[tar],tot-siz[tar]);
		if(mx[tar]<mx[cent]) cent=tar;
	}
	return cent;
}
int son[M+5],dep[M+5],len[M+5];
void dfs(int x,int f)
{
	len[x]=0;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to]||to==f) continue;
		dfs(to,x);
		len[x]=max(len[x],len[to]+1);
	}
}
bool cmp(int a,int b)
{
	return len[a]<len[b];
}
int dis[M+5];
int L;
void rec(int x,int f)
{
	arr[tot++]=x;
	dis[x]=dis[f]+1;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(to==f||vis[to]) continue;
		rec(to,x);
	}
}
typedef double db;
struct comp
{
	db x,y;
	comp(){}
	comp(db a,db b):x(a),y(b){}
	comp operator *(comp &b)
	{
		return comp(x*b.x-y*b.y,x*b.y+y*b.x);
	}
	comp operator +(comp &b)
	{
		return comp(x+b.x,y+b.y);
	}
	comp operator -(comp &b)
	{
		return comp(x-b.x,y-b.y);
	}
}B[M*4+5],A[M*4+5];
int C[M*4+5],prime[M+5],pcnt;
int mod_pow(int x,int y)
{
	int res=1;
	for(int b=x;y;y>>=1,b=(ll)b*b%mod) if(y&1) res=(ll)res*b%mod;
	return res;
}
int inver(int x)
{
	return mod_pow(x,mod-2);
}
int rev[M*5+5];
void DFT(comp*A,int type)
{
	rep(i,0,L) if(i<rev[i]) swap(A[i],A[rev[i]]);
	for(int i=2;i<=L;i<<=1)
	{
		int mid=i>>1;
		comp wn(cos(pi*2/i),type*sin(pi*2/i));
		for(int j=0;j<L;j+=i)
		{
			comp w(1,0);
			for(int k=0;k<mid;k++,w=w*wn)
			{
				comp a=A[j+k],b=w*A[j+k+mid];
				A[j+k]=a+b;
				A[j+k+mid]=a-b;
			}
		}
	}
}
void FFT(comp*A,comp*B)
{
	rev[0]=0;
	rep(i,1,L)
	{
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=L>>1;
	}
//	DFT(A,1);DFT(A,-1);
	DFT(A,1);DFT(B,1);
	rep(i,0,L) A[i]=A[i]*B[i];
	DFT(A,-1);
}
int ans=0;
void conquer(int x)
{
	int cnt=0;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to]) continue;
		son[cnt++]=to;
		dfs(to,x);
	}
	if(cnt==0) return;
	sort(son,son+cnt,cmp);
	C[0]=1;
	int lb=1;
	dis[x]=0;
	rep(i,0,cnt)
	{
		int la=len[son[i]]+1;
		for(L=1;L<=la+lb;L<<=1);
		tot=0;
		rec(son[i],x);
		rep(j,0,tot) A[dis[arr[j]]].x++;
		rep(j,0,L) B[j]=comp(C[j],0);
//		rep(j,0,L) dig("%d ",A[j]);puts("");
//		rep(j,0,L) dig("%d ",B[j]);puts("");
//		puts("");
		FFT(A,B);
		rep(j,0,pcnt)
		{
			if(prime[j]>=L) break;
			ans+=int(A[prime[j]].x/L+0.5);
		}
		rep(j,0,L) A[j]=comp(0,0);
		rep(j,0,tot) C[dis[arr[j]]]++;
		lb=la;
	}
	rep(j,0,L) C[j]=0,A[j]=B[j]=comp(0,0);
}
void divide(int x)
{
	x=find_cent(x);
//	dig("divide %d\n",x);
	vis[x]=true;
	conquer(x);
//	dig("ans %d\n",ans);
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
//		printf("%d -> %d\n",x,to);
		if(!vis[to]) divide(to);
	}
}
bool mark[M+5];
void sieve(int x)
{
	rep(i,2,x+1)
	{
		if(!mark[i])
		{
			prime[pcnt++]=i;
			for(int j=i+i;j<=x;j+=i) mark[j]=1;
		}
	}
}
int main()
{
	rd(n);
	sieve(n);
	etot=0;
	rep(i,1,n+1) head[i]=-1;
	int a,b;
	rep(i,1,n)
	{
		rd(a);rd(b);
		add_edge(a,b);
		add_edge(b,a);
	}
	divide(1);
//	dig("ans %d\n",ans);
	printf("%.7lf\n",(double)ans/((ll)n*(n-1)/2));
	return 0;
}
