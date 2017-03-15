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
int n,v[M+5];
vector<int>edge[M+5];
int arr[M+5],tot,siz[M+5],mx[M+5],val[M+5];
bool vis[M+5];
void rec(int x,int f)
{
	arr[tot++]=x;
	siz[x]=1,mx[x]=0;
	rep(i,0,edge[x].size())
	{
		int to=edge[x][i];
		if(to==f||vis[to]) continue;
		rec(to,x);
		siz[x]+=siz[to];
		mx[x]=max(mx[x],siz[to]);
	}
}
int find_cent(int x)
{
	tot=0;
	int cent=x;
	rec(x,0);
	rep(i,0,tot)
	{
		int tar=arr[i];
		mx[tar]=max(mx[tar],tot-siz[tar]);
		if(mx[tar]<mx[cent]) cent=tar;
	}
	return cent;
}
void dfs(int x,int f)
{
	arr[tot++]=x;
	val[x]=val[f]^v[x];
	rep(i,0,edge[x].size())
	{
		int to=edge[x][i];
		if(to==f||vis[to]) continue;
		dfs(to,x);
	}
}
ll ans=0;
int cnt[2][32];
void add_bit(int x)
{
	rep(i,0,31) cnt[(x>>i&1)^1][i]++;
}
void minus_bit(int x)
{
	rep(i,0,31) cnt[(x>>i&1)^1][i]--;
}
void query_bit(int x)
{
	rep(i,0,31) ans+=(1LL<<i)*cnt[x>>i&1][i];
}
void conquer(int x)
{
	tot=0;
	val[x]=v[x];
	add_bit(val[x]);
	rep(i,0,edge[x].size())
	{
		int to=edge[x][i];
		if(vis[to]) continue;
		int last=tot;
		dfs(to,x);
		rep(i,last,tot) query_bit(val[arr[i]]^v[x]);
		rep(i,last,tot) add_bit(val[arr[i]]);
	}
	minus_bit(val[x]);
	rep(i,0,tot) minus_bit(val[arr[i]]);
}
void divide(int x)
{
	x=find_cent(x);
	vis[x]=true;
	conquer(x);
	rep(i,0,edge[x].size())
	{
		int to=edge[x][i];
		if(!vis[to])
		{
			divide(to);
		}
	}
}
int main()
{
	rd(n);
	rep(i,1,n+1) rd(v[i]),ans+=v[i];
	rep(i,1,n)
	{
		int a,b;
		rd(a);rd(b);
		edge[a].pb(b);
		edge[b].pb(a);
	}
	divide(1);
	cout<<ans<<endl;
	return 0;
}
