/*
    tags: suffix array,union find
    notes: the size of INF
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int M=300000;
const ll INF=1e18+1000;
int par[M+5];
ll ans[M+5],v[M+5],mi[M+5],mx[M+5],res[M+5];
char s[M+5];
struct Suffix_Array
{
	int sa[M+5],rk[M+5],h[M+5],v[M+5];
	void build(char*s,int n,int m)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]-'a'+1]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			rep(i,n-k+1,n+1) y[++p]=i;
			rep(i,1,n+1) if(sa[i]>k) y[++p]=sa[i]-k;
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
	/*	rep(i,1,n+1) prt(sa[i]);
		puts("");
		rep(i,1,n+1) prt(rk[i]);
		puts("");
		rep(i,1,n+1) prt(h[i]);
		puts("");*/
	}
}sa;
int get_par(int x)
{
	if(par[x]!=x) par[x]=get_par(par[x]);
	return par[x];
}
bool cmp(int a,int b)
{
	return sa.h[a]>sa.h[b];
}
int A[M+5],sz[M+5];
void chk_min(ll&x,ll y){if(x>y) x=y;}
void chk_max(ll&x,ll y){if(x<y) x=y;}
int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",s+1);
	rep(i,1,n+1) scanf("%lld",&v[i]);
	sa.build(s,n,26);
	ans[0]=-INF;
	rep(i,1,n+1)
	{
		sz[i]=1;
		ans[i]=-INF;
		mi[i]=mx[i]=v[i];
		par[i]=i;
	}
	rep(i,2,n+1) A[i-2]=i;
	int tot=n-1;
	//[0,tot)
	sort(A,A+tot,cmp);//按照h从大到小
	rep(i,0,tot)
	{//合并A[i]和A[i]-1
		int a=get_par(sa.sa[A[i]]),b=get_par(sa.sa[A[i]-1]);
		if(a==b) continue;
		chk_max(ans[sa.h[A[i]]],mi[a]*mi[b]);
		chk_max(ans[sa.h[A[i]]],mx[a]*mx[b]);
		res[sa.h[A[i]]]+=(ll)sz[a]*sz[b];
		chk_max(mx[a],mx[b]);
		chk_min(mi[a],mi[b]);
		sz[a]+=sz[b];
		par[b]=a;
	}
	sort(v+1,v+n+1);
	chk_max(ans[0],v[1]*v[2]);
	chk_max(ans[0],v[n]*v[n-1]);
	per(i,0,n-1) chk_max(ans[i],ans[i+1]);
	per(i,0,n-1) res[i]+=res[i+1];
	rep(i,0,n)
	{
		if(ans[i]==-INF) ans[i]=0LL;
		printf("%lld %lld\n",res[i],ans[i]);
	}
	return 0;
}
