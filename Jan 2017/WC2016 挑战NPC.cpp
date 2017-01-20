#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define debug(x) cout<<#x<<" = "<<x<<endl
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const int M=600;//ball: [1,n]   basket: [n+1,n+3*m]
struct Edge
{
	int to,nxt;
	Edge(int a,int b):to(a),nxt(b){}
	Edge(){}
}edge[M*400];
int etot,n,m,e,qh,qt,Timer;
int head[M+5],que[M+5],par[M+5],vis[M+5],match[M+5],pre[M+5],mark[M+5];
void add_edge(int u,int v)
{
	edge[etot]=Edge(v,head[u]);
	head[u]=etot++;
}
int get_par(int x)
{
	if(par[x]!=x) par[x]=get_par(par[x]);
	return par[x];
}
void augment(int x)
{
	int tmp;
	while(x)
	{
		tmp=match[pre[x]];
		match[x]=pre[x];
		match[pre[x]]=x;
		x=tmp;
	}
}
int LCA(int u,int v)
{
	for(u=get_par(u),v=get_par(v),Timer++;;swap(u,v))if(u)
	{
		if(vis[u]==Timer) return u;
		vis[u]=Timer;
		u=get_par(pre[match[u]]);//pre[match[u]] not pre[u]
	}
}
void shrink(int u,int v,int lca)
{
	while(get_par(u)!=lca)
	{
		pre[u]=v;
		par[u]=lca;
		par[match[u]]=lca;
		if(mark[match[u]]==1)
		{//match[u] not u
			mark[match[u]]=0;
			que[qh++]=match[u];
		}
		v=match[u];
		u=pre[v];
	}
}
int BFS(int x)
{
	qh=qt=0;
	clr(mark,-1);clr(pre,0);
	rep(i,1,n+3*m+1) par[i]=i;
	que[qh++]=x;
	mark[x]=0;
	while(qt<qh)
	{
		x=que[qt++];
		for(int i=head[x];~i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(get_par(to)==get_par(x)) continue;
			if(mark[to]==-1)
			{
				mark[to]=1;
				pre[to]=x;
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
				int lca=LCA(to,x);
				shrink(to,x,lca);
				shrink(x,to,lca);
			}
		}
	}
	return 0;
}
int blossom()
{
	clr(match,0);
	int ret=0;
	rep(i,1,n+m*3+1) if(!match[i]) ret+=BFS(i);
	return ret;
}
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
void solve()
{
	rd(n);rd(m);rd(e);
	int u,v;
	rep(i,1,m+1)
	{
		int a=n+i*3;
		int b=n+i*3-1;
		int c=n+i*3-2;
		add_edge(a,b);
		add_edge(b,a);
		add_edge(b,c);
		add_edge(c,b);
		add_edge(c,a);
		add_edge(a,c);
	}
	rep(i,0,e)
	{
		rd(u);rd(v);
		//编号为u的球可以放到编号为v的篮子中
		rep(j,n+(v-1)*3+1,n+v*3+1)
		{
			add_edge(u,j);
			add_edge(j,u);
		}
	}
	printf("%d\n",blossom()-n);
	rep(i,1,n+1) printf("%d ",(match[i]-n-1+3)/3);
	etot=0;
	rep(i,1,n+3*m+1) head[i]=-1;
}
int main()
{
//	freopen("ex_npc2.in","r",stdin);
	int T;clr(head,-1);
	for(scanf("%d",&T);T;T--) solve();
	return 0;
}
