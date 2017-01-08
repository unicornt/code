/*
	tags: 后缀数组
	note: 复杂度不对，但是可以AC
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define debug(x) cout<<#x<<" = "<<x<<endl
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define ptn(x) cout<<x
using namespace std;
const int M=300000;
int s[M],tot,p[M];
int n,m,sz,mark[M],res[M],T,bel[M];
struct Suffix_Array
{
	int sa[M],h[M],rk[M],v[M];
	void build(int *s,int n,int m)
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
			rep(i,1,n+1) v[x[sa[i]]]=i;
			per(i,1,n+1) sa[v[x[y[i]]]--]=y[i];
			assert(p==n);
			p=0;
			rep(i,1,n+1)
			{
				if(x[sa[i]]!=x[sa[i-1]]||x[sa[i]+k]!=x[sa[i-1]+k]) ++p;
				y[sa[i]]=p;
			}
			swap(x,y);
			if(p==n) break;
		}
		if(x!=rk) memcpy(rk,x,n+1<<2);
		int k=0;
		s[0]=-1;
		rep(i,1,n+1)
		{
			int j=sa[rk[i]-1];
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
//		rep(i,1,n+1) prt(h[i]);
//		puts("");
	}
	int solve(int p,int len)
	{
		++T;
		int L=rk[p],R=rk[p]+1;
		int mi=len,ans=0;
//		debug(L);
		while(len<=mi&&L>0)
		{
			if(mark[bel[sa[L]]]!=T&&bel[sa[L]]<=n)
			{
//				debug(L);debug(bel[sa[L]]);
				mark[bel[sa[L]]]=T;
				ans++;
				res[bel[sa[L]]]++;
			}
			mi=min(mi,h[L]);
			--L;
		}
		mi=h[R];
		while(len<=mi&&R<=tot)
		{
			if(mark[bel[sa[R]]]!=T&&bel[sa[R]]<=n)
			{
//				debug(R);
//				debug(bel[sa[R]]);
				mark[bel[sa[R]]]=T;
				ans++;
				res[bel[sa[R]]]++;
			}
			++R;
			mi=min(mi,h[R]);
		}
		return ans;
	}
}sa;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	sz=10000;
	rep(i,1,n+1)
		rep(j,0,2)
		{
			int len;
			scanf("%d",&len);
			while(len--)
			{
				scanf("%d",&s[++tot]);
				bel[tot]=i;
			}
			s[++tot]=++sz;
			bel[tot]=i;
		}
	rep(i,1,m+1)
	{
		int len;
		scanf("%d",&len);
		p[i]=tot+1;
		while(len--)
		{
			scanf("%d",&s[++tot]);
			bel[tot]=n+i;
		}
		s[++tot]=++sz;
		bel[tot]=n+i;
	}
	p[m+1]=tot+1;
	sa.build(s,tot,sz);
	rep(i,1,m+1) printf("%d\n",sa.solve(p[i],p[i+1]-p[i]-1));
	rep(i,1,n+1) printf("%d%c",res[i]," \n"[i==n]);
	return 0;
}
