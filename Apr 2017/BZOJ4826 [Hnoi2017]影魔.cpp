#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef long long ll;
inline void rd(int&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') c=getchar(),flag=true;
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
 
const int M=200000;
int n,m,p1,p2;
int A[M+5],stk[M+5],L[M+5],R[M+5];
int qa[M+5],qb[M+5];
struct Segment_Tree
{
	ll sum[M<<2|3],tag[M<<2|3];
	void build(int p,int tl,int tr)
	{
		tag[p]=sum[p]=0;
		if(tl==tr) return;
		int mid=(tl+tr)>>1;
		build(p<<1,tl,mid);
		build(p<<1|1,mid+1,tr);
	}
	void up(int p)
	{
		sum[p]=sum[p<<1]+sum[p<<1|1];
	}
	void down(int p,int tl,int tr)
	{
		if(tag[p])
		{
			int mid=(tl+tr)>>1;
			sum[p<<1]+=(ll)(mid-tl+1)*tag[p];
			sum[p<<1|1]+=(ll)(tr-mid)*tag[p];
			tag[p<<1]+=tag[p];
			tag[p<<1|1]+=tag[p];
			tag[p]=0;
		}
	}
	void update(int l,int r,int x,int p,int tl,int tr)
	{
		if(l==tl&&r==tr)
		{
			sum[p]+=(ll)(r-l+1)*x;
			tag[p]+=x;
			return;
		}
		down(p,tl,tr);
		int mid=(tl+tr)>>1;
		if(r<=mid) update(l,r,x,p<<1,tl,mid);
		else if(l>mid) update(l,r,x,p<<1|1,mid+1,tr);
		else update(l,mid,x,p<<1,tl,mid),update(mid+1,r,x,p<<1|1,mid+1,tr);
		up(p);
	}
	ll query(int l,int r,int p,int tl,int tr)
	{
		if(l==tl&&r==tr) return sum[p];
		down(p,tl,tr);
		int mid=(tl+tr)>>1;
		if(r<=mid) return query(l,r,p<<1,tl,mid);
		else if(l>mid) return query(l,r,p<<1|1,mid+1,tr);
		else return query(l,mid,p<<1,tl,mid)+query(mid+1,r,p<<1|1,mid+1,tr);
	}
}sgt;
struct OPT
{
	int x,a,b,add;
	OPT(int c,int d,int e,int f):x(c),a(d),b(e),add(f){}
	OPT(){}
}opt[M*6+5];
bool cmp(OPT a,OPT b)
{
	if(a.x==b.x) return a.add>b.add;
	return a.x<b.x;
}
ll ans[M+5];
void solve(int cnt)
{
	sgt.build(1,1,n);
	sort(opt,opt+cnt,cmp);
	rep(i,0,cnt)
	{
		if(opt[i].add<0)
		{
			if(opt[i].add==-1) ans[opt[i].b]+=sgt.query(1,opt[i].a,1,1,n);
			else ans[opt[i].b]-=sgt.query(1,opt[i].a,1,1,n);
		}
		else
		{
			sgt.update(opt[i].a,opt[i].b,opt[i].add,1,1,n);
		}
	}
}
int main()
{
	rd(n);rd(m);rd(p1);rd(p2);
	rep(i,1,n+1) rd(A[i]);
	int top=0,tot=0;
	A[0]=1e9+1;
	rep(i,1,n+1)
	{
		while(A[stk[top]]<=A[i]) R[stk[top]]=i,top--;
		if(!L[i]) L[i]=stk[top];
		stk[++top]=i;
	}
	rep(i,1,top+1) R[stk[i]]=n+1;
	rep(i,0,m)
	{
		rd(qa[i]);rd(qb[i]);
	}
	int cnt=0;
	rep(i,0,m)
	{
		if(qa[i]>1)
		{
			opt[cnt++]=OPT(qa[i]-1,qa[i]-1,i,-1);
			opt[cnt++]=OPT(qa[i]-1,qb[i],i,-2);
			opt[cnt++]=OPT(qb[i],qa[i]-1,i,-2);
		}
		opt[cnt++]=OPT(qb[i],qb[i],i,-1);
	}
	rep(i,1,n+1)
	{
		if(L[i]>0&&i+1<=R[i]-1) opt[cnt++]=OPT(L[i],i+1,R[i]-1,p2);
		if(L[i]>0&&R[i]<=n) opt[cnt++]=OPT(L[i],R[i],R[i],p1);
	}
	solve(cnt);
	cnt=0;
	rep(i,0,m)
	{
		if(qa[i]>1)
		{
			opt[cnt++]=OPT(qa[i]-1,qa[i]-1,i,-1);
			opt[cnt++]=OPT(qa[i]-1,qb[i],i,-2);
			opt[cnt++]=OPT(qb[i],qa[i]-1,i,-2);
		}
		opt[cnt++]=OPT(qb[i],qb[i],i,-1);
	}
	rep(i,1,n+1)
	{
		if(L[i]+1<=i-1) opt[cnt++]=OPT(R[i],L[i]+1,i-1,p2);
	}
	solve(cnt);
//	rep(i,0,m) printf("%lld\n",ans[i]);
//	puts("");
	rep(i,0,m) printf("%lld\n",ans[i]+(ll)(qb[i]-qa[i])*p1);
	return 0;
}
