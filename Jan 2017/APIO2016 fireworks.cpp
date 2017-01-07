#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef long long ll;
const int M=600005;
int n,m,sz,rs[M],ls[M],tree[M],par[M],dis[M],son[M];
ll v[M];
int P(ll x)
{
	v[++sz]=x;
	return sz;
}
int Merge(int x,int y)
{
	if(x==0||y==0) return x|y;
	if(v[x]>v[y]) swap(x,y);
	//v[x]<v[y]
	rs[y]=Merge(x,rs[y]);
	swap(ls[y],rs[y]);
	return y;
}
ll Pop(int x)
{
	ll tmp=v[tree[x]];
	tree[x]=Merge(ls[tree[x]],rs[tree[x]]);
	return tmp;
}
int main()
{
//	freopen("ex_fireworks1.in","r",stdin);
	scanf("%d%d",&n,&m);
	swap(n,m);n+=m;
	ll ans=0;
	rep(i,2,n+1)
	{
		scanf("%d%d",&par[i],&dis[i]);
		ans+=dis[i];
		++son[par[i]];
	}
	per(i,2,n+1)
	{
		if(i>m) tree[i]=Merge(P(dis[i]),P(dis[i]));
		else
		{
			if(!son[i]) continue;
			for(--son[i];son[i];--son[i]) Pop(i);
			ll L=Pop(i),R=Pop(i);
			tree[i]=Merge(tree[i],P(dis[i]+L));
			tree[i]=Merge(tree[i],P(dis[i]+R));
		}
		tree[par[i]]=Merge(tree[par[i]],tree[i]);
	}
	for(;son[1];--son[1]) Pop(1);
	while(tree[1]) ans-=Pop(1);
	printf("%lld\n",ans);
	return 0;
}
