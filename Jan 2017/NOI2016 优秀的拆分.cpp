#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=30005;
const int S=15;
typedef long long ll;
int Log2[M];
struct Suffix_Array
{
	char s[M];
	int n,m,sa[M],rk[M],h[M],v[M],pre[S][M];
	Suffix_Array(){}
	Suffix_Array(char*str,int _n,int _m):n(_n),m(_m)
	{
		memcpy(s,str,n+2);
		build();
		pret();
	}
	void build()
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]-'a'+1]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<n;k<<=1)
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
		rep(i,1,n+1)
		{
			int j=sa[rk[i]-1];
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
	}
	void pret()
	{
		rep(i,1,n+1) pre[0][i]=h[i];
		rep(i,1,S) rep(j,1,n+1)
		{
			if(j+(1<<i-1)>n) break;
			pre[i][j]=min(pre[i-1][j],pre[i-1][j+(1<<i-1)]);
		}
	}
	int query_min(int l,int r)
	{
		int k=Log2[r-l+1];
		return min(pre[k][l],pre[k][r-(1<<k)+1]);
	}
	int query(int l,int r)
	{
		if(l==r) return n-l+1;
		if(rk[l]>rk[r]) swap(l,r);
		return query_min(rk[l]+1,rk[r]);
	}
}*sa,*rsa;
char str[M];
int prv[M],nxt[M];//差分
void solve(int n)
{
	rep(len,1,n/2+1)
	{//枚举重复子串的长度 
		for(int l=1,r=len+1;r<=n;l+=len,r+=len)
		{
			int x=rsa->query(n-l+1,n-r+1);
			int y=sa->query(l,r);
			if(!x||!y) continue;
			x=max(r-x,l);
			y=min(l+y,r);
//			printf("solve %d %d %d %d\n",l,r,x,y);
			if(y>=x)
			{
				nxt[x-len+1]++;
				nxt[y-len+1]--;
				prv[x+len]++;
				prv[y+len]--;
			}
		}
	} 
	rep(i,1,n+1) prv[i]+=prv[i-1],nxt[i]+=nxt[i-1];
//	rep(i,1,n+1) printf("prv nxt   %d %d\n",prv[i],nxt[i]);
}
void output(int n)
{
	ll ans=0;
	rep(i,1,n) ans+=(ll)prv[i]*nxt[i+1];
	printf("%lld\n",ans);
}
int main()
{
//	freopen("ex_excellent3.in","r",stdin);
	Log2[1]=0;
	rep(i,2,30001)
	{
		Log2[i]=Log2[i>>1]+1;
	}
	int cas;
	for(scanf("%d",&cas);cas;--cas)
	{
		scanf("%s",str+1);
		int n=strlen(str+1);
		rep(i,0,n+1) prv[i]=nxt[i]=0;
		sa=new Suffix_Array(str,n,26);
		reverse(str+1,str+n+1);
		rsa=new Suffix_Array(str,n,26);
		solve(n);
		output(n);
	}
	return 0;
}
