/*
  tags: Dinic,dp
  notes: 这题有很多细节，非常恶心
*/
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define For(i,a,b) for(int i##id=a,i=B[i##id];i##id<b;i##id++,i=B[i##id])
#define Rof(i,a,b) for(int i##id=(b)-1,i=B[i##id];i##id>=a;i##id--,i=B[i##id])
#define debug(x) cout<<#x<<" = "<<x<<endl
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define pb(x) push_back(x)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const int M=50000;
const int INF=0x7fffffff;
int n;
pll p[M+5];
ll C[M+5];
int B[M+5],up_to[M+5],left_up[M+5],right_up[M+5];
bool cmp1(int a,int b)
{
	if(p[a].fi==p[b].fi) return p[a].se<p[b].se;
	return p[a].fi<p[b].fi;
}
bool cmp2(int a,int b)
{
	if(C[a]==C[b]) return p[a].se<p[b].se;
	return C[a]<C[b];
}
void pret()
{
	sort(B,B+n+1,cmp1);
	per(i,0,n) if(p[B[i]].fi==p[B[i+1]].fi)
		up_to[B[i]]=B[i+1];

	rep(i,0,n+1)
		C[i]=p[i].fi+p[i].se;
	sort(B,B+n+1,cmp2);
	per(i,0,n) if(C[B[i]]==C[B[i+1]])
		left_up[B[i]]=B[i+1];

	rep(i,0,n+1)
		C[i]=p[i].fi-p[i].se;
	sort(B,B+n+1,cmp2);
	per(i,0,n) if(C[B[i]]==C[B[i+1]])
		right_up[B[i]]=B[i+1];
}
int dp[M+5],tmp[M+5];
bool cmp3(int a,int b)
{
	if(p[a].se==p[b].se) return p[a].fi<p[b].fi;
	return p[a].se<p[b].se;
}
void chk_max(int&x,int y){if(x<y) x=y;}
int stk[M+5],top;
void radd_edge(int u,int v)
{
	assert(stk[top]==u);
	stk[++top]=v;
}
void add_line(int l,int r,int j,int i)
{
	stk[++top]=B[i];
	if(j<i)
	{
		Rof(k,j+1,i) radd_edge(B[kid+1],k);
		radd_edge(B[j+1],B[l]);
		For(k,l,j) radd_edge(k,B[kid+1]);
	}
	else
	{
//		puts("OK");
		For(k,i,j-1) radd_edge(k,B[kid+1]);
		radd_edge(B[j-1],B[r-1]);
		Rof(k,j,r-1) radd_edge(B[kid+1],k);
	}
//	printf("%d %d %d %d %d\n",stk[top],B[j],j,l,r);
	assert(stk[top]==B[j]);
}
bool mark[M+5];
int ans=0,pre[M+5],Id[M+5],Lid[M+5],Rid[M+5],ID[M+5];
void check(int a,int b)
{
	if(dp[b]+1>dp[a]) dp[a]=dp[b]+1,pre[a]=b;
}
void get_ans(int x)
{
	if(Id[x]!=-1) add_line(Lid[x],Rid[x],Id[x],ID[x]),x=B[Id[x]];
	else if(x) stk[++top]=x;
	if(pre[x]) get_ans(pre[x]);
}
void DP()
{
	memset(dp,-1,sizeof dp);
	dp[0]=0;
	sort(B,B+n+1,cmp3);
	memset(Id,-1,sizeof Id);
//	rep(i,0,n+1) prt(up_to[i]),prt(left_up[i]),pts(right_up[i]);//
	For(l,0,n+1)
	{
		int rid=lid;
		while(rid<=n&&p[B[rid]].se==p[l].se) rid++;
		For(i,lid,rid)
			tmp[i]=dp[i];
		int mx=-1,id=-1;
		For(i,lid,rid)
		{
			ID[i]=iid;
			Lid[i]=lid,Rid[i]=rid;
			if(mx!=-1&&mx+iid-lid>dp[i]) dp[i]=mx+iid-lid,Id[i]=id;
			if(tmp[i]>mx) mx=tmp[i],id=iid;
		}
		mx=id=-1;
		Rof(i,lid,rid)
		{
			if(mx!=-1&&mx+rid-iid-1>dp[i]) dp[i]=mx+rid-iid-1,Id[i]=id;
			if(tmp[i]>mx) mx=tmp[i],id=iid;
		}
		For(i,lid,rid)
		{
			if(dp[i]==-1) continue;
			if(up_to[i]) check(up_to[i],i);
			if(left_up[i]) check(left_up[i],i);
			if(right_up[i]) check(right_up[i],i);
		}
		lid=rid-1;
	}
	rep(i,0,n+1) chk_max(ans,dp[i]);
	printf("%d\n",ans);
//	rep(i,0,n+1) printf("pre[%d] = %d\n",i,pre[i]);
	rep(i,0,n+1) if(dp[i]==ans)
	{
		top=0;
		get_ans(i);
//#ifndef unicornt
		per(i,1,top+1) printf("%d ",stk[i]);
		puts("");
//#endif
		break;
	}
}
int in[M+5],out[M+5];
struct NetWork
{
	struct Edge
	{
		int to,cap,nxt;
		Edge(int a,int b,int c):to(a),cap(b),nxt(c){}
		Edge(){}
	}edge[M*6+50];
	int src,dest,head[M*2+50],etot,work[M*2+50];
	int DFS(int x,int flow)
	{
		if(x==dest) return flow;
		int tmp,res=0;
		for(int&i=work[x];~i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(dis[to]==dis[x]+1&&edge[i].cap>0&&(tmp=DFS(to,min(edge[i].cap,flow)))<=flow)
			{
//				debug(tmp);
				res+=tmp;
				edge[i].cap-=tmp;
				edge[i^1].cap+=tmp;
				flow-=tmp;
			}
		}
		return res;
	}
	int que[M*2+50],dis[M*2+50];
	bool BFS()
	{
//		debug(dest);
//		debug(etot);
		rep(i,0,dest+1) dis[i]=-1;
		int L=0,R=0;
		que[R++]=src;
		dis[src]=0;
//		debug(dest);
		while(L<R)
		{
			int x=que[L++];
			for(int i=head[x];~i;i=edge[i].nxt)
			{
				int to=edge[i].to;
//				if(x==24997) debug(i),debug(to);
				if(edge[i].cap>0&&dis[to]==-1)
				{
					dis[to]=dis[x]+1;
					que[R++]=to;
				}
			}
		}
		return dis[dest]!=-1;
	}
	int Dinic()
	{
		int ans=0;
//		puts("OK");
		while(BFS())
		{
//			puts("OK");
			rep(i,0,dest+1) work[i]=head[i];
			int res=DFS(src,INF);
			if(res) ans+=res;
			assert(res);
		}
//		debug(ans);
		return ans;
	}
	void add_edge(int u,int v,int w)
	{
//		printf("edge %d %d %d\n",u,v,w);
		edge[etot]=Edge(v,w,head[u]);
		head[u]=etot++;
		edge[etot]=Edge(u,0,head[v]);
		head[v]=etot++;
	}
	void init(int n)
	{
		src=n+n+2;
		dest=n+n+3;
//		memset(head,-1,sizeof(head));
		rep(i,0,dest+1) head[i]=-1;
		etot=0;
		rep(i,0,n+1) add_edge(n+1+i,i,INF);
	}
}nw;
void add_edge(int u,int v)
{
//	printf("add edge     %d %d\n",u,v);
	in[v]++;
	out[u]++;
	nw.add_edge(u,v+n+1,INF);
}
bool flag[M];
void solve()
{
	nw.init(n);
	memset(mark,0,sizeof mark);
	memset(flag,0,sizeof flag);
	Rof(i,0,n+1)
	{
		if(dp[i]==ans) mark[i]=1;
		if(up_to[i]&&tmp[up_to[i]]==dp[i]+1&&(flag[up_to[i]]||dp[up_to[i]]==dp[i]+1&&mark[up_to[i]]))
			mark[i]=1,add_edge(i,up_to[i]);
		if(left_up[i]&&tmp[left_up[i]]==dp[i]+1&&(flag[left_up[i]]||dp[left_up[i]]==dp[i]+1&&mark[left_up[i]]))
			mark[i]=1,add_edge(i,left_up[i]);
		if(right_up[i]&&tmp[right_up[i]]==dp[i]+1&&(flag[right_up[i]]||dp[right_up[i]]==dp[i]+1&&mark[right_up[i]]))
			mark[i]=1,add_edge(i,right_up[i]);
		if(mark[i])
		{
//			assert(iid>=Lid[i]&&iid<Rid[i]);
//			assert(Id[i]>=Lid[i]&&Id[i]<Rid[i]);
			For(j,Lid[i],Rid[i])
			{
				if(jid<iid)
				{
					if(dp[i]==tmp[j]+iid-Lid[i]) flag[j]=1;
				}
				else if(jid>iid&&dp[i]==tmp[j]+Rid[i]-iid-1) flag[j]=1;
			}
		}
	}
//	rep(i,0,n+1) prt(mark[i]),pts(flag[i]);
	int res=0;
	rep(i,0,n+1)
	{
		res+=max(0,out[i]-in[i]);
		if(in[i]<out[i]) nw.add_edge(i+n+1,nw.dest,out[i]-in[i]);
		if(in[i]>out[i]) nw.add_edge(nw.src,i,in[i]-out[i]);
	}
	printf("%d\n",res-nw.Dinic());
}
int main()
{
//	freopen("farm7.in","r",stdin);
	scanf("%d",&n);
	p[0]=pll(0,0);
	rep(i,1,n+1) scanf("%lld%lld",&p[i].fi,&p[i].se),B[i]=i;
	pret();
	DP();
	solve();
	return 0;
}
/*
5
1 1
-1 1
-2 2
2 2
3 3

*/
