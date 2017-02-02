/*
  tags: 树分治
  notes: conquer调用有两种，一种是直接计算(不考虑在同一棵子树的情况)，另一种是同一种子树去重。
         conquer调用时注意初始化dep和dis的值并不都是0
*/
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
const int M=100000;
struct Edge
{
	int to,v,nxt;
	Edge(int a,int b,int c):to(a),v(b),nxt(c){}
	Edge(){}
}edge[M*2+5];
int head[M+5],etot;
void add_edge(int u,int v,int w)
{
	edge[etot]=Edge(v,w,head[u]);
	head[u]=etot++;
}
void chk_max(int&x,int y)
{
	if(x<y) x=y;
}
int n,l,w,tot;
ll ans=0;
int siz[M+5],arr[M+5];
bool vis[M+5];
void rec(int x,int f)
{
	arr[tot++]=x;
	siz[x]=1;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to]||to==f) continue;
		rec(to,x);
		siz[x]+=siz[to];
	}
}
int find_cent(int u)
{
	int cent=u;
	tot=0;
	rec(u,0);
	rep(i,0,tot)
	{
		int tar=arr[i];
		chk_max(siz[tar],tot-siz[tar]);
		if(siz[tar]<siz[cent]) cent=tar;
	}
	return cent;
}
int dep[M+5];
ll dis[M+5];
void dfs(int x,int f)
{
	arr[tot++]=x;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(vis[to]||to==f) continue;
		dis[to]=dis[x]+edge[i].v;
		dep[to]=dep[x]+1;
		dfs(to,x);
	}
}
bool cmp(int a,int b)
{
	return dis[a]<dis[b];
}
struct Binary_Index_Tree
{
	int bit[M+5];
	void update(int x,int w)
	{
		++x;
		for(int i=x;i<=n+1;i+=i&-i) bit[i]+=w;
	}
	int query(int x)
	{
		++x;
		int res=0;
		for(int i=x;i;i-=i&-i) res+=bit[i];
		return res;
	}
}bit;
void conquer(int u,int type)
{
	tot=0;
	dfs(u,0);
	sort(arr,arr+tot,cmp);
	int R=tot-1;
	rep(i,0,tot) bit.update(dep[arr[i]],1);
	rep(L,0,tot)
	{
		int x=arr[L];
		while(R>=L&&dis[arr[R]]+dis[x]>w)
		{
			bit.update(dep[arr[R]],-1);
			R--;
		}
		if(L<=R)
		{
			bit.update(dep[arr[L]],-1);
			if(dis[arr[R]]+dis[x]<=w&&l-dep[x]>=0)
				ans+=type*bit.query(l-dep[x]);
		}else return;
	}
}
void divide(int u)
{
	u=find_cent(u);
	vis[u]=true;
	dep[u]=dis[u]=0;
	conquer(u,1);
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(!vis[to])
		{
			dis[to]=edge[i].v;
			dep[to]=1;
			conquer(to,-1);
		}
	}
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(!vis[to]) divide(to);
	}
}
int main()
{
	clr(head,-1);
	rd(n);rd(l);rd(w);
	rep(i,2,n+1)
	{
		int a,b;
		rd(a);rd(b);
		add_edge(a,i,b);
		add_edge(i,a,b);
	}
	divide(1);
	printf("%I64d\n",ans);
	return 0;
}
