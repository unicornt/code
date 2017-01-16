#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#ifdef unicornt
	#define ast(x) assert(x)
	#define debug(x) cout<<#x<<" = "<<x<<endl
	#define prt(x) cout<<x<<' '
	#define pts(x) cout<<x<<endl
#else
	#define ast(x) ;
	#define debug(x) ;
	#define prt(x) ;
	#define pts(x) ;
#endif
using namespace std;
typedef long long ll;
const int INF=0x7fffffff;
const int M=1000000;
int val[M+5];
struct Segment_Tree
{
	static const int Tsz=(M<<2)+5;
	int cnt[Tsz],mx[Tsz],se[Tsz];
	int tag[Tsz];
	ll sum[Tsz];
	void up(int p)
	{
		int l=p<<1,r=p<<1|1;
		sum[p]=sum[l]+sum[r];
		if(mx[l]==mx[r])
		{
			mx[p]=mx[l];
			cnt[p]=cnt[l]+cnt[r];
			se[p]=max(se[l],se[r]);
		}
		else if(mx[l]>mx[r])
		{
			mx[p]=mx[l];
			cnt[p]=cnt[l];
			se[p]=max(mx[r],se[l]);
		}
		else
		{
			mx[p]=mx[r];
			cnt[p]=cnt[r];
			se[p]=max(se[r],mx[l]);
		}
	}
	void down(int p,int tl,int tr)
	{
		if(tag[p]==-1) return;
		int mid=(tl+tr)>>1;
		upd(tag[p],p<<1,tl,mid);
		upd(tag[p],p<<1|1,mid+1,tr);
		tag[p]=-1;
	}
	void upd(int v,int p,int tl,int tr)
	{
//		printf("tree  ");prt(tl);pts(tr);
		if(mx[p]<=v) return;
		else if(se[p]<v)
		{
			sum[p]+=(ll)(v-mx[p])*cnt[p];
			mx[p]=v;
			tag[p]=v;
			return;
		}
		int mid=(tl+tr)>>1;
		upd(v,p<<1,tl,mid);
		upd(v,p<<1|1,mid+1,tr);
		up(p);
	}
	void build(int p,int tl,int tr)
	{
		tag[p]=-1;
		if(tl==tr)
		{
			mx[p]=val[tl];
			sum[p]=val[tl];
			cnt[p]=1;
			se[p]=-1;
			return;
		}
		int mid=(tl+tr)>>1;
		build(p<<1,tl,mid);
		build(p<<1|1,mid+1,tr);
		up(p);
	}
	void update(int l,int r,int x,int p,int tl,int tr)
	{
		if(l==tl&&r==tr)
		{
			upd(x,p,tl,tr);
			return;
		}
		down(p,tl,tr);
		int mid=(tl+tr)>>1;
		if(mid>=r) update(l,r,x,p<<1,tl,mid);
		else if(mid<l) update(l,r,x,p<<1|1,mid+1,tr);
		else update(l,mid,x,p<<1,tl,mid),update(mid+1,r,x,p<<1|1,mid+1,tr);
		up(p);
	}
	int query_mx(int l,int r,int p,int tl,int tr)
	{
		if(tl==l&&tr==r)
			return mx[p];
		int mid=(tl+tr)>>1;
		down(p,tl,tr);
		if(mid>=r) return query_mx(l,r,p<<1,tl,mid);
		else if(mid<l) return query_mx(l,r,p<<1|1,mid+1,tr);
		else return max(query_mx(l,mid,p<<1,tl,mid),query_mx(mid+1,r,p<<1|1,mid+1,tr));
	}
	ll query_sum(int l,int r,int p,int tl,int tr)
	{
		if(tl==l&&tr==r) return sum[p];
		int mid=(tl+tr)>>1;
		down(p,tl,tr);
		if(mid>=r) return query_sum(l,r,p<<1,tl,mid);
		else if(mid<l) return query_sum(l,r,p<<1|1,mid+1,tr);
		else return query_sum(l,mid,p<<1,tl,mid)+query_sum(mid+1,r,p<<1|1,mid+1,tr);
	}
}sgt;
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
template<class Ty>void print(Ty x)
{
	if(!x) return;
	print(x/10);
	putchar(x%10^48);
}
template<class Ty>inline void pt(Ty x)
{
	if(!x) putchar('0');
	else print(x);
	putchar('\n');
}
void solve()
{
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) rd(val[i]);
	sgt.build(1,1,n);
	rep(t,0,m)
	{
		int opt,l,r,x;
		rd(opt);rd(l);rd(r);
		if(opt==0)
		{
			rd(x);
			sgt.update(l,r,x,1,1,n);
		}
		else if(opt==1) pt(sgt.query_mx(l,r,1,1,n));
		else pt(sgt.query_sum(l,r,1,1,n));
	}
}
int main()
{
	int T;
	for(scanf("%d",&T);T;T--) solve();
	return 0;
}
