/*
  notes: dp,用线段树+单调栈维护
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
const int INF=M+1;
const int mod=1e9+7;
int ans,dp[M+5];
struct Line
{
	int u,l,r,s;
	int ctr()
	{
		return u+s;
	}
}line[M+5];
struct Segment_Tree
{
	vector<int>tree[M*4+5];
	void build(int p,int tl,int tr)
	{
		if(tl==tr)
		{
			tree[p].clear();
			return;
		}
		int mid=(tl+tr)>>1;
		build(p<<1,tl,mid);
		build(p<<1|1,mid+1,tr);
	}
	void update(int l,int r,int k,int p,int tl,int tr)
	{
		if(l==tl&&r==tr)
		{
			while(tree[p].size()&&line[tree[p].back()].ctr()<line[k].ctr()) tree[p].pop_back();
			tree[p].pb(k);
			return;
		}
		int mid=(tl+tr)>>1;
		if(mid>=r) update(l,r,k,p<<1,tl,mid);
		else if(mid<l) update(l,r,k,p<<1|1,mid+1,tr);
		else update(l,mid,k,p<<1,tl,mid),update(mid+1,r,k,p<<1|1,mid+1,tr);
	}
	void query(int h,int x,int p,int tl,int tr)
	{
		while(tree[p].size()&&line[tree[p].back()].ctr()<h) tree[p].pop_back();
		if(tree[p].size()&&tree[p].back()>ans) ans=tree[p].back();
		if(tl==tr) return;
		int mid=(tl+tr)>>1;
		if(x<=mid) query(h,x,p<<1,tl,mid);
		else query(h,x,p<<1|1,mid+1,tr);
	}
}sgt;
bool cmp(Line a,Line b)
{
	return a.u<b.u;
}
void add(int&x,int y)
{
	if(y==-1) x=(x+1)%mod;
	else x=(x+dp[y])%mod;
}
int main()
{
	int h,w;
	rd(h);rd(w);
	int n;
	rd(n);
	rep(i,0,n) rd(line[i].u),rd(line[i].l),rd(line[i].r),rd(line[i].s);
	sort(line,line+n,cmp);
	dp[INF]=1;
	sgt.build(1,1,w);
	rep(i,0,n)
	{
		if(line[i].l!=1)
		{
			ans=-1;
			sgt.query(line[i].u,line[i].l-1,1,1,w);
			add(dp[i],ans);
		}
		else
		{
			ans=-1;
			sgt.query(line[i].u,line[i].r+1,1,1,w);
			add(dp[i],ans);
		}
		if(line[i].r!=w)
		{
			ans=-1;
			sgt.query(line[i].u,line[i].r+1,1,1,w);
			add(dp[i],ans);
		}
		else
		{
			ans=-1;
			sgt.query(line[i].u,line[i].l-1,1,1,w);
			add(dp[i],ans);
		}
		sgt.update(line[i].l,line[i].r,i,1,1,w);
//		debug(dp[i]);
	}
	int res=0;
	rep(i,1,w+1)
	{
		ans=-1;
		sgt.query(h+1,i,1,1,w);
		add(res,ans);
//		debug(dp[ans]);
	}
	printf("%d\n",res);
	return 0;
}
