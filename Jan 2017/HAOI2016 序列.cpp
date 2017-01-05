#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int M=100005;
const int S=18;
const int BLK=333;
int A[M],stk[M],n,q;
namespace RMQ
{
	int pre[M][S],Log2[M];
	bool cmppre(int a,int b)
	{
		if(A[a]==A[b]) return a<b;
		return A[a]<A[b];
	}
	void prepare()
	{
		Log2[1]=0;
		rep(i,2,n+1) Log2[i]=Log2[i>>1]+1;
		rep(i,0,n) pre[i][0]=i;
		rep(i,1,S) rep(j,0,n)
		{
			if(j+(1<<i-1)>=n) break;
			pre[j][i]=min(pre[j][i-1],pre[j+(1<<i-1)][i-1],cmppre);
		}
	}
	int query(int l,int r)
	{
		--r;
		assert(l<=r);
		int k=Log2[r-l+1];
//		printf("%d %d %d %d\n",l,l+(1<<k)-1,r-(1<<k)+1,r);
		assert(r-(1<<k)+1<=l+(1<<k));
		return min(pre[l][k],pre[r-(1<<k)+1][k],cmppre);
	}
}
int C[M];
void get_arr(ll *l)
{
	int top=0;
	rep(i,0,n)
	{
		while(top>0&&A[i]<A[stk[top]]) --top;
		l[i]=top>0?(ll)(i-stk[top])*A[i]+l[stk[top]]:0;
		stk[++top]=i;
	}
}
ll lsum[M],rsum[M];
ll go_right(int l,int r)
{
//	printf("go right %d %d\n",l,r);
	int pos=RMQ::query(l,r+1);
	return (ll)(pos-l+1)*A[pos]-lsum[pos]+lsum[r];
}
ll go_left(int l,int r)
{
//	printf("go left %d %d\n",l,r);
	int pos=RMQ::query(l-1,r);
	return (ll)(r-pos)*A[pos]-rsum[pos]+rsum[l-1];
}
ll ans[M];
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
struct node
{
	int l,r,lx;
	node(){}
	node(int a,int b):l(a),r(b)
	{
		lx=l/BLK;
	}
}qry[M];
bool cmp(int a,int b)
{
	if(qry[a].lx!=qry[b].lx) return qry[a].lx<qry[b].lx;
	return qry[a].lx&1?qry[a].r<qry[b].r:qry[a].r>qry[b].r;
}
int main()
{
	scanf("%d%d",&n,&q);
	rep(i,0,n) scanf("%d",&A[i]);
	rep(i,0,q)
	{
		int a,b;
		scanf("%d%d",&a,&b);
//		rd(a);rd(b);
		--a;
		qry[i]=node(a,b);
		C[i]=i;
	}
	get_arr(lsum);
	reverse(A,A+n);
	get_arr(rsum);
	reverse(A,A+n);
	reverse(rsum,rsum+n);
	sort(C,C+q,cmp);
//	A[n]=0x7fffffff;
	int l=0,r=0;
	RMQ::prepare();
	ll res=0;
//	rep(i,0,n) printf("%lld %lld\n",lsum[i],rsum[i]);
    rep(iid,0,q)
	{
		int i=C[iid];
		while(r<qry[i].r) res+=go_right(l,r++);
		while(l>qry[i].l) res+=go_left(l--,r);
		while(r>qry[i].r) res-=go_right(l,--r);
		while(l<qry[i].l) res-=go_left(++l,r);
//		printf("%d %d %d %d\n",l,r,qry[i].l,qry[i].r);
		ans[i]=res;
	}
	rep(i,0,q) printf("%lld\n",ans[i]);
	return 0;
}
