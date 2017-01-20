/*
  tags: 网络流
  notes: 模板题
*/
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
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
const int M=200;
const int INF=0x7fffffff;
int n;
struct NetWork
{
	struct Edge
	{
		int to,cap,nxt;
		Edge(int a,int b,int c):to(a),cap(b),nxt(c){}
		Edge(){}
	}edge[M*2+5];
	int etot,src,dest,head[M+5];
	void init()
	{
		src=1;
		dest=n;
		etot=0;
		clr(head,-1);
	}
	void add_edge(int u,int v,int cap)
	{
		edge[etot]=Edge(v,cap,head[u]);
		head[u]=etot++;
	}
	int que[M+5],qh,qt,dis[M+5],work[M+5];
	bool BFS()
	{
		rep(i,1,dest+1) dis[i]=-1;
		dis[src]=0;
		qh=qt=0;
		que[qh++]=src;
		while(qt<qh)
		{
			int x=que[qt++];
			for(int i=head[x];~i;i=edge[i].nxt)
			{
				int to=edge[i].to;
				if(edge[i].cap>0&&dis[to]==-1)
				{
					dis[to]=dis[x]+1;
					que[qh++]=to;
				}
			}
		}
		return dis[dest]!=-1;
	}
	int dfs(int x,int flow)
	{
		if(x==dest||flow==0) return flow;
		int res=0;
		for(int&i=work[x];~i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(edge[i].cap>0&&dis[to]==dis[x]+1)
			{
				int tmp=dfs(to,min(flow,edge[i].cap));
				edge[i].cap-=tmp;
				edge[i^1].cap+=tmp;
				flow-=tmp;
				res+=tmp;
				if(flow==0) break;
			}
		}
		return res;
	}
	int dinic()
	{
		int res=0;
		while(BFS())
		{
			rep(i,1,dest+1) work[i]=head[i];
			res+=dfs(src,INF);
		}
		return res;
	}
}nw;
int main()
{
	int m;
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		nw.init();
		rep(i,0,m)
		{
			int u,v,c;
			rd(u);rd(v);rd(c);
			nw.add_edge(u,v,c);
			nw.add_edge(v,u,0);
		}
		printf("%d\n",nw.dinic());
	}
	return 0;
}
