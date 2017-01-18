#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const int M=500;
int n,m;
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
void print(int x)
{
	if(!x) return;
	print(x/10);
	putchar(x%10^48);
}
inline void pt(int x)
{
	if(!x) putchar('0');
	else print(x);
	putchar(' ');
}
struct Edge
{
	int to,nxt;
	Edge(int a,int b):to(a),nxt(b){}
	Edge(){}
}edge[124750*2+5];
int head[M+5],par[M+5],match[M+5],pre[M+5],mark[M+5],que[M+5],vis[M+5];
int qt,qh,etot,ans,Timer;
void add_edge(int u,int v)
{
	edge[etot]=Edge(v,head[u]);
	head[u]=etot++;
}
void init()
{
	Timer=ans=etot=0;
	clr(head,-1);clr(match,0);
}
int get_par(int x)
{
	if(x!=par[x]) par[x]=get_par(par[x]);
	return par[x];
}
void shrink(int x,int y,int lca)
{
	while(get_par(x)!=lca)
	{
		pre[x]=y;
		if(par[x]==x) par[x]=lca;
		if(par[match[x]]==match[x]) par[match[x]]=lca;
		if(mark[match[x]]==1)
		{
			mark[match[x]]=0;
			que[qh++]=match[x];
		}
		y=match[x];
		x=pre[y];
	}
}
void augment(int x)
{
	int tmp;
	while(x)
	{
//			dig("x %d\n",x);
		tmp=match[pre[x]];
		match[x]=pre[x];
		match[pre[x]]=x;
		x=tmp;
	}
}
int LCA(int u,int v)
{
	for(Timer++,u=get_par(u),v=get_par(v);;swap(u,v))if(u)
	{
		if(vis[u]==Timer) return u;
		vis[u]=Timer;
		u=get_par(pre[match[u]]);
	}
	return 0;
}
int BFS(int st)
{
	qt=qh=0;
	clr(mark,-1);clr(pre,0);
	rep(i,1,n+1) par[i]=i;
	mark[st]=0;
	que[qh++]=st;
	while(qt<qh)
	{
		int x=que[qt++];
		for(int i=head[x];~i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(get_par(to)==get_par(x)) continue;
			if(mark[to]==-1)
			{
				pre[to]=x;
				mark[to]=1;
				if(match[to]==0)
				{
					augment(to);
					return 1;
				}
				que[qh++]=match[to];
				mark[match[to]]=0;
			}
			else if(mark[to]==0)
			{
				int lca=LCA(x,to);
				shrink(x,to,lca);
				shrink(to,x,lca);
			}
		}
	}
	return 0;
}
void output()
{
	printf("%d\n",ans);
	rep(i,1,n+1) pt(match[i]);
}
void solve()
{
	rep(i,1,n+1) if(!match[i]) ans+=BFS(i);
	output();
}
int main()
{
	scanf("%d%d",&n,&m);
	init();
	rep(i,0,m)
	{
		int a,b;
		rd(a);rd(b);
		add_edge(a,b);
		add_edge(b,a);
	}
	solve();
	return 0;
}
