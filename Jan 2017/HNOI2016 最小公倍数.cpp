#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=100005;
struct Edge
{
	int u,v,a,b;
}edge[M],query[M];
int C[M],D[M];
bool cmp(int a,int b)
{
	return edge[a].a<edge[b].a;
}
bool cmp2(int a,int b)
{
	return edge[a].b<edge[b].b;
}
bool cmp3(int a,int b)
{
	return query[a].a<query[b].a;
}
bool cmp4(int a,int b)
{
	return query[a].b<query[b].b;
}
int reca[M],recb[M],recv[M],recu[M],par[M],siz[M],mxa[M],mxb[M];
int get_par(int x)
{
	for(;x!=par[x];x=par[x]);return x;
}
void add(int x)
{
	int u=get_par(edge[x].u),v=get_par(edge[x].v);
	if(u==v)
	{
		mxa[u]=max(mxa[u],edge[x].a);
		mxb[u]=max(mxb[u],edge[x].b);
		return;
	}
	if(siz[u]>siz[v]) swap(u,v);
	if(siz[u]==siz[v]) siz[v]++;
	par[u]=v;
	mxa[v]=max(mxa[v],max(mxa[u],edge[x].a));
	mxb[v]=max(mxb[v],max(mxb[u],edge[x].b));
}
bool recbool[M];
void add_edge(int id,int x)
{
	int u=get_par(edge[x].u),v=get_par(edge[x].v);
	if(u==v)
	{
		reca[id]=mxa[u];
		recb[id]=mxb[u];
		recu[id]=recv[id]=u;
		mxa[u]=max(mxa[u],edge[x].a);
		mxb[u]=max(mxb[u],edge[x].b);
		recbool[id]=false;
	}
	else
	{
		if(siz[u]>siz[v]) swap(u,v);//u -> v
		par[u]=v;
		reca[id]=mxa[v];
		recb[id]=mxb[v];
		if(siz[v]==siz[u]) siz[v]++,recbool[id]=true;
		else recbool[id]=false;
		recv[id]=v;
		recu[id]=u;
		mxa[v]=max(mxa[v],max(mxa[u],edge[x].a));
		mxb[v]=max(mxb[v],max(mxb[u],edge[x].b));
	}
}
bool ans[M];
void del_edge(int id)
{
	par[recu[id]]=recu[id];
	mxa[recv[id]]=reca[id];
	mxb[recv[id]]=recb[id];
	if(recbool[id]) siz[recv[id]]--;
}
int n,m;
void init()
{
	rep(i,1,n+1) par[i]=i,siz[i]=1,mxa[i]=mxb[i]=-1;
}
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
int main()
{
	scanf("%d%d",&n,&m);
	rep(i,0,m)
	{
		rd(edge[i].u);rd(edge[i].v);rd(edge[i].a);rd(edge[i].b);
	//	scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&edge[i].a,&edge[i].b);
		C[i]=i;
	}
	int S=sqrt(n*log(n)/log(2))+1;
	int q;
	scanf("%d",&q);
	rep(i,0,q)
	{
		rd(query[i].u);rd(query[i].v);rd(query[i].a);rd(query[i].b);
//		scanf("%d%d%d%d",&query[i].u,&query[i].v,&query[i].a,&query[i].b);
		D[i]=i;
	}
//	fprintf(stderr,"%d\n",S);
	sort(C,C+m,cmp);
	sort(D,D+q,cmp3);
	int R=0;
//	memset(ans,-1,sizeof(ans));
	C[m]=m;
	edge[m].a=0x7fffffff;
	rep(i,0,m/S+1)
	{
//		printf("%d\n",i);
		init();
		int l=i*S,r=min(m,(i+1)*S);
		int L=R;
		sort(C,C+l,cmp2);
		while(R<q&&query[D[R]].a<edge[C[r]].a) R++;
		sort(D+L,D+R,cmp4);
		int qt=L,t=0;
		do
		{
			//init();///
			//t=0;
			while(t<l&&edge[C[t]].b<=query[D[qt]].b) add(C[t++]);
			rep(j,l,r)
			{
				if(edge[C[j]].a<=query[D[qt]].a&&edge[C[j]].b<=query[D[qt]].b)
					add_edge(j,C[j]);
					//add(C[j]);
			}
			int u=get_par(query[D[qt]].u),v=get_par(query[D[qt]].v);
			//printf("%d :  %d %d      %d %d %d %d\n",D[qt],u,v,mxa[u],query[D[qt]].a,mxb[u],query[D[qt]].b);
			if(u==v&&mxa[u]==query[D[qt]].a&&mxb[u]==query[D[qt]].b) ans[D[qt]]=1;
			per(j,l,r)
			{
				if(edge[C[j]].a<=query[D[qt]].a&&edge[C[j]].b<=query[D[qt]].b)
					del_edge(j);
			}
			qt++;
		}while(qt<R);
	}
	rep(i,0,q) puts(ans[i]?"Yes":"No");
	return 0;
}
