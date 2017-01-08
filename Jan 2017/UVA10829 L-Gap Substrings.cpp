/*
	tags: Suffix Array,Segment Tree
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const int M=50005;
const int Tsz=1000000;
int L;
char s[M];
map<char,int>mp;
vector<int>vec[M];
struct Suffix_Array
{
	int sa[M],rk[M],v[M],h[M];
	void build(char*s,int n,int m)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=mp[s[i]]]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<n;k<<=1)
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
		/*
		rep(i,1,n+1) prt(sa[i]);
		puts("");
		rep(i,1,n+1) prt(rk[i]);
		puts("");
		rep(i,1,n+1) prt(h[i]);
		puts("");
		*/
	}
}sa;
bool cmp(int a,int b)
{
	return sa.h[a]>sa.h[b];
}
int ls[Tsz],rs[Tsz],siz[Tsz],rt[M],sz,n,C[M],par[M];
int get_par(int x)
{
	if(par[x]!=x) par[x]=get_par(par[x]);
	return par[x];
}
void insert(int&rt,int tl,int tr,int x)
{
	rt=++sz;
	ls[rt]=rs[rt]=0;
	siz[rt]=1;
	if(tl==tr) return;
	int mid=(tl+tr)>>1;
	if(mid>=x) insert(ls[rt],tl,mid,x);
	else insert(rs[rt],mid+1,tr,x);
}
int query(int rt,int tl,int tr,int l,int r)
{
	if(!rt) return 0;
	if(tl==l&&r==tr) return siz[rt];
	int mid=(tl+tr)>>1;
	if(mid>=r) return query(ls[rt],tl,mid,l,r);
	else if(mid<l) return query(rs[rt],mid+1,tr,l,r);
	else return query(ls[rt],tl,mid,l,mid)+query(rs[rt],mid+1,tr,mid+1,r);
}
int merge(int a,int b)
{//a <- b
	if(a==0||b==0) return a|b;
	ls[a]=merge(ls[a],ls[b]);
	rs[a]=merge(rs[a],rs[b]);
	siz[a]+=siz[b];
	return a;
}
int solve(int y,int l,int r)
{
	l=max(1,l);
	r=min(n,r);
	return l<=r?query(rt[y],1,n,l,r):0;
}
int solve()
{
	mp.clear();
	scanf("%d",&L);
	scanf("%s",s+1);
	sz=0;
	rep(i,0,(n=strlen(s+1))+1)
		if(mp.find(s[i])==mp.end()) mp[s[i]]=++sz;
	sa.build(s,n,sz);
	sz=0;
	rep(i,2,n+1) C[i-2]=i;
	sort(C,C+n-1,cmp);
	int ans=0;
	rep(i,1,n+1)
	{
		par[i]=i;
		insert(rt[i],1,n,i);
		vec[i].clear();
		vec[i].pb(i);
	}
	rep(i,0,n-1)
	{
		//ºÏ²¢C[i]ºÍC[i]-1
		int a=get_par(sa.sa[C[i]]),b=get_par(sa.sa[C[i]-1]);
		if(a==b) continue;
		if(vec[a].size()>vec[b].size()) swap(a,b);
		rep(j,0,vec[a].size())
		{
			int x=vec[a][j];
			ans+=solve(b,x+L+1,sa.h[C[i]]+x+L);
			ans+=solve(b,x-L-sa.h[C[i]],x-L-1);
			vec[b].pb(x);
		}
		vec[a].clear();
		par[a]=b;
		rt[b]=merge(rt[b],rt[a]);
	}
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T);
	rep(i,1,T+1) printf("Case %d: %d\n",i,solve());
	return 0;
}
