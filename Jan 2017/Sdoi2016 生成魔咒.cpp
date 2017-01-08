/*
	tags: Suffix Array
	notes: 后缀数组的构建出错，没有在最后将x复制到rk中 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <map>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define debug(x) cout<<#x<<" = "<<x<<endl
#define prt(x) cout<<x<<' '
#define ptn(x) cout<<x
#define pts(x) cout<<x<<endl
using namespace std;
const int M=100000;
const int S=17;
typedef long long ll;
map<int,int>mark;
int s[M+5];
int n,m;
struct Suffix_Array
{
	int sa[M+5],rk[M+5],h[M+5],v[M+5],ST[S][M+5],Log2[M+5],bit[2][M+5];
	void build(int*s)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<n;k<<=1)
		{
			int p=0;
			rep(i,n-k+1,n+1) y[++p]=i;
			rep(i,1,n+1) if(sa[i]>k) y[++p]=sa[i]-k;
//			assert(p==n);
			rep(i,1,n+1) v[x[sa[i]]]=i;
			per(i,1,n+1) sa[v[x[y[i]]]--]=y[i];
			p=0;
			rep(i,1,n+1)
			{
				if(x[sa[i]]!=x[sa[i-1]]||x[sa[i]+k]!=x[sa[i-1]+k]) ++p;
				y[sa[i]]=p;
			}
			swap(x,y);
			if(p==n) break;
		}
		if(rk!=x) memcpy(rk,x,n+1<<2);
		int k=0;
		rep(i,1,n+1)
		{
			int j=sa[rk[i]-1];
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
//		rep(i,1,n+1) prt(sa[i]);
//		puts("");
//		rep(i,1,n+1) prt(rk[i]);
//		puts("");
//		rep(i,1,n+1) prt(h[i]);
//		puts("");
		pret();
	}
	void pret()
	{
		Log2[1]=0;
		rep(i,2,n+1) Log2[i]=Log2[i>>1]+1;
		rep(i,1,n+1) ST[0][i]=h[i];
		rep(i,1,S) rep(j,1,n+1)
		{
			if(j+(1<<i-1)>n) break;
			ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<i-1)]);
		}
	}
	int query_st(int a,int b)
	{
		if(a>b) swap(a,b);
		a++;
		int k=Log2[b-a+1];
		return min(ST[k][a],ST[k][b-(1<<k)+1]);
	}
	void update_mx(int x)
	{
		for(int i=x;i<=n;i+=i&-i) bit[0][i]=max(bit[0][i],x);
	}
	void update_mi(int x)
	{
		for(int i=x;i;i-=i&-i) bit[1][i]=min(bit[1][i],x);
	}
	int query_mx(int x)
	{
		int res=0;
		for(int i=x;i;i-=i&-i) res=max(res,bit[0][i]);
		return res;
	}
	int query_mi(int x)
	{
		int res=n+1;
		for(int i=x;i<=n;i+=i&-i) res=min(res,bit[1][i]);
		return res;
	}
	void init_bit()
	{
		rep(i,1,n+1) bit[0][i]=0,bit[1][i]=n+1;
	}
	void solve(int*s)
	{
		ll ans=0;
		init_bit();
		per(i,1,n+1)
		{
			int rnk=rk[i];
			int L=query_mx(rnk);
			int R=query_mi(rnk);
			int lcp=0;
//			prt(L);prt(rnk);pts(R);//
			if(L!=n+1) lcp=max(lcp,query_st(L,rnk));
			if(R) lcp=max(lcp,query_st(R,rnk));
//			debug(lcp);//
			ans+=(n-i+1)-lcp;
			printf("%lld\n",ans);
//			puts("");//
			update_mi(rnk);
			update_mx(rnk);
		}
	}
}sa;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	rep(i,1,n+1)
	{
		scanf("%d",&s[i]);
		if(mark.find(s[i])==mark.end()) mark[s[i]]=++m;
		s[i]=mark[s[i]];
	}
	reverse(s+1,s+n+1);
	sa.build(s);
	sa.solve(s);
	return 0;
}
/*
3
1 2 1
*/
