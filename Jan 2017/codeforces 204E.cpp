#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=100000;
const int S=17;
typedef long long ll;
int n,K,len;
char buf[M+5];
int str[M*2+5],bel[M*2+5],rt[M*2+5],st[M+5],ed[M+5];//[ st[i] , ed[i] )
struct suffix_array
{
	int sa[M*2+5],h[M*2+5],v[M*2+5],rk[M*2+5],ST[S][M*2+5],Log2[M*2+5];
	void build(int*s,int n,int m)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			rep(i,n-k+1,n+1) y[++p]=i;
			rep(i,1,n+1) if(sa[i]>k) y[++p]=sa[i]-k;
			assert(p==n);
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
		if(x!=rk) memcpy(rk,x,n+1<<2);
		int k=0;
//		puts("OK");//
//	rep(i,1,n+1) prt(sa[i]);
//	puts("");
//	rep(i,1,n+1) prt(rk[i]);
//	puts("");
//	rep(i,1,n+1) prt(h[i]);
//	puts("");
		rep(i,1,n+1)
		{
			int j=sa[rk[i]-1];
//			prt(i);pts(j);//
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
		pret(n);
	}
	void pret(int n)
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
	int query_mi(int a,int b)
	{
		int k=Log2[b-a+1];
		return min(ST[k][a],ST[k][b-(1<<k)+1]);
	}
	int query(int a,int b)
	{
//		assert(a!=b);
		if(a>b) swap(a,b);
		a++;
		return query_mi(a,b);
	}
}sa;
bool check(int x,int tl)
{
	int L=1,R=sa.rk[x]-1,l=sa.rk[x],r=sa.rk[x];
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(sa.query(mid,sa.rk[x])>=tl) l=mid,R=mid-1;
		else L=mid+1;
	}
	L=sa.rk[x]+1,R=len;
	while(L<=R)
	{
		int mid=(L+R)>>1;
		if(sa.query(sa.rk[x],mid)>=tl) r=mid,L=mid+1;
		else R=mid-1;
	}
//	debug(tl);//
//	prt(l);prt(sa.rk[x]);pts(r);//
	return rt[l]<=r;
}
int cnt[M+5],num=0;
void add(int x)
{
	int b=bel[sa.sa[x]];
	if(!b) return;
	if(cnt[b]==0) num++;
	cnt[b]++;
}
void del(int x)
{
	int b=bel[sa.sa[x]];
	if(!b) return;
	cnt[b]--;
	if(cnt[b]==0) num--;
}
void pret()
{
	int R=0;
	memset(cnt,0,sizeof cnt);
	rep(i,1,len+1)
	{
		while(num<K&&R<len)
		{
			++R;
			add(R);
		}
		assert(i<=R);
		assert(num<=K);
		if(num==K) rt[i]=R;
		else rt[i]=len+1;
		del(i);
	}
}
ll ans[M+5];
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&K);
	int m=26;
	len=1;
	rep(i,1,n+1)
	{
		scanf("%s",buf);
		st[i]=len;
		rep(j,0,strlen(buf))
		{
			bel[len]=i;
			str[len++]=buf[j]-'a'+1;
		}
		ed[i]=len;
		str[len++]=++m;
	}
	len-=2;
	sa.build(str,len,m);
	pret();
	rep(i,1,len+1)
	{
		if(str[i]>26) continue;
		int L=0,R=ed[bel[i]]-i,res=0;//不能包含分割字符 
		while(L<=R)
		{
			int mid=(L+R)>>1;
			if(check(i,mid)) res=mid,L=mid+1;
			else R=mid-1;
		}
//		debug(res);
		ans[bel[i]]+=res;
	}
	rep(i,1,n+1) prt(ans[i]);
	return 0;
}
/*
10 10
p
e
h
i
i
a
a
c
b
b
*/
