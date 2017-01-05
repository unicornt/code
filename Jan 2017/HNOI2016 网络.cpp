#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
int n,m;
inline void rd(int&x)
{
	x=0;char c;
	while(c=getchar(),c<48);
	do x=x*10+(c^48);
	while(c=getchar(),c>47);
}
const int M=100005;
const int S=17;
struct Edge
{
	int to,nxt;
	Edge(int a,int b):to(a),nxt(b){}
	Edge(){}
}edge[M<<1];
int head[M],etot,C[M<<1],ans[M<<1],B[M<<1],opt[M<<1],a[M<<1],b[M<<1],v[M<<1];
void add_edge(int u,int v)
{
	edge[etot]=Edge(v,head[u]);
	head[u]=etot++;
}
int A[M<<1];
int L[M],R[M],dfs_clock,pre[S][M],dep[M],lca[M<<1];
void rec(int x,int f)
{
	pre[0][x]=f;
	dep[x]=dep[f]+1;
	L[x]=++dfs_clock;
	for(int i=head[x];~i;i=edge[i].nxt)
	{
		int to=edge[i].to;
		if(to==f) continue;
		rec(to,x);
	}
	R[x]=dfs_clock;
}
void pret()
{
	rep(i,1,S) rep(j,1,n+1) pre[i][j]=pre[i-1][pre[i-1][j]];
}
int up(int u,int step)
{
	rep(i,0,S) if(step&(1<<i)) u=pre[i][u];
	return u;
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	u=up(u,dep[u]-dep[v]);
	if(u!=v)
	{
		per(i,0,S) if(pre[i][u]!=pre[i][v]) u=pre[i][u],v=pre[i][v];
		u=pre[0][u];
	}
	return u;
}
#define lowbit(x) ((x)&(-(x)))
struct Binary_Index_Tree
{
	int bit[M<<1];
	void add(int x,int w)
	{
		while(x<=dfs_clock)
		{
			bit[x]+=w;
			x+=lowbit(x);
		}
	}
	void init()
	{
		memset(bit,0,sizeof(bit));
	}
	int sum(int x)
	{
		int res=0;
		while(x>0)
		{
			res+=bit[x];
			x-=lowbit(x);
		}
		return res;
	}
}bit;
void add(int i,int f)
{
	bit.add(L[a[i]],f);
	bit.add(L[b[i]],f);
	bit.add(L[lca[i]],-f);
	if(pre[0][lca[i]]) bit.add(L[pre[0][lca[i]]],-f);
}
void solve(int tL,int tR,int l,int r)
{
//	printf("L and R     %d %d\n",tL,tR);
	if(tL+1==tR)
	{
		rep(i,l,r) if(opt[C[i]]==2) ans[C[i]]=B[tL];
		return;
	}
	int mid=(tL+tR)>>1;
//	puts("1");
	//[tL,mid) [mid,tR);
	rep(i,l,r) A[i]=C[i];
	int tot=0,tl=l,tr=r-1;
//	puts("2");
	rep(iid,l,r)
	{
		int i=A[iid];
		if(opt[i]==2)
		{
			int res=bit.sum(R[a[i]])-bit.sum(L[a[i]]-1);
//			printf("res and tot   %d %d\n",res,tot);
			assert(res<=tot);
			if(res>=tot) C[tl++]=i;
			else C[tr--]=i;
		}
		else if(opt[i]==0)
		{
			assert(v[i]>=tL&&v[i]<tR);
			if(v[i]>=mid)
			{
				add(i,1);
				++tot;
				C[tr--]=i;
			}
			else C[tl++]=i;
		}
		else
		{
			assert(opt[i]==1);
			assert(v[a[i]]>=tL&&v[a[i]]<tR);
			if(v[a[i]]>=mid)
			{
				add(a[i],-1);
				--tot;
				C[tr--]=i;
			}
			else C[tl++]=i;
		}
	}
	rep(iid,l,r)
	{
		int i=A[iid];
		if(opt[i]==0&&v[i]>=mid) add(i,-1);
		if(opt[i]==1&&v[a[i]]>=mid) add(a[i],1);
	}
	rep(i,tr+1,r)
	{
		int j=r-(i-tr);
		if(i>=j) break;
		swap(C[i],C[j]);
	}
//	puts("3");
	assert(tl==tr+1);
	solve(tL,mid,l,tl);
	solve(mid,tR,tl,r);
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	rep(i,1,n)
	{
		int u,v;
		rd(u);rd(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	int tot=0;
	B[tot++]=-1;
	rep(i,1,m+1)
	{
		rd(opt[i]);
		rd(a[i]);
		if(opt[i]==0)
		{
			rd(b[i]),rd(v[i]);
			B[tot++]=v[i];
		}
	}
	rec(1,0);
	pret();
	sort(B,B+tot);
	tot=unique(B,B+tot)-B;
	rep(i,1,m+1) if(!opt[i])
	{
		v[i]=lower_bound(B,B+tot,v[i])-B;
		lca[i]=LCA(a[i],b[i]);
	}
	rep(i,1,m+1) C[i]=i,ans[i]=-1;
	solve(0,tot,1,m+1);
	rep(i,1,m+1)if(opt[i]==2) printf("%d\n",ans[i]);
	return 0;
}
