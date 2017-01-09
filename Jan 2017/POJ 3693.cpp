#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const int M=100000;
const int S=17;
int n,Log2[M+5],ST2[S][M+5];
struct Suffix_Array
{
	int sa[M+5],rk[M+5],h[M+5],v[30],ST[S][M+5];
	void build(char*s,int n,int m)
	{
		int *x=rk,*y=h;
//		rep(i,0,n+1) sa[i]=rk[i]=h[i]=0;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]-'a'+1]++;
//		printf("%d\n",x[1]);
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1)
		{
//			Debug(n);//
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
		if(rk!=x) memcpy(rk,x,n+1<<2);
		int k=0;
		h[1]=0;
		sa[0]=0;
		rep(i,1,n+1)
		{
			int j=sa[rk[i]-1];
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
//		Debug(n);//
		pret(n);
	}
	void pret(int n)
	{
		rep(i,1,n+1) ST[0][i]=h[i];
		rep(i,1,S)
			rep(j,1,n+1)
			{
				if(j+(1<<i-1)>n) break;
				ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<i-1)]);
			}
	}
	int MIN(int a,int b)
	{
		return rk[a]<rk[b]?a:b;
	}
	void pret_sa(int n)
	{
		rep(i,1,n+1) ST2[0][i]=i;
		rep(i,1,S)
			rep(j,1,n+1)
			{
				if(j+(1<<i-1)>n) break;
				ST2[i][j]=MIN(ST2[i-1][j],ST2[i-1][j+(1<<i-1)]);
			}
	}
	int query_sa(int l,int r)
	{
		int k=Log2[r-l+1];
		return MIN(ST2[k][l],ST2[k][r-(1<<k)+1]);
	}
	int query_mi(int l,int r)
	{
		int k=Log2[r-l+1];
//		prt(l),prt(l+(1<<k)-1),prt(r-(1<<k)+1),pts(r);
		return min(ST[k][l],ST[k][r-(1<<k)+1]);
	}
	int query(int l,int r)
	{
//		prt(l);pts(r);
		l=rk[l],r=rk[r];
		if(l>r) swap(l,r);
		assert(l!=r);//
		l++;
		return query_mi(l,r);
	}
}*sa,*rsa;
char s[M+5];
int T;
void solve()
{
	sa=new Suffix_Array();
	rsa=new Suffix_Array();
	n=strlen(s+1);
	sa->build(s,n,26);
	sa->pret_sa(n);
	reverse(s+1,s+n+1);
	rsa->build(s,n,26);
	reverse(s+1,s+n+1);
	int res=0,ans=0,id=-1;
	rep(L,1,n/2+1)
	{
		for(int i=1,j=L+1;j<=n;i+=L,j+=L)
		{
			int nxt=sa->query(i,j);
			int prv=rsa->query(n-i+1,n-j+1);
//			prt(prv+nxt-1+L);pts(L);//
			if(j-prv>i+nxt-1) continue;
//			printf("%d %d %d %d\n",prv,nxt,i,j);
			int LL=i-prv+1,RR=j+nxt-1;
			int len=RR-LL+1;
			int delta=len-len/L*L;
			len-=delta;
			//[LL,RR]
			//[LL,LL+delta]
			//[RR-delta,RR]
//			printf("query_sa(%d,%d)\n",LL,LL+delta);
			int now=sa->query_sa(LL,LL+delta);
//			debug(now);//
//			debug(L);//
//			prt(i);pts(j);//
//			prt(nxt);pts(prv);//
//			assert(len%L==0);
			int rept=len/L;
//			int len=prv+nxt-1+L;
			if(rept>ans)
			{
				ans=rept;
				res=len;
				id=now;
			}
			else if(rept==ans)
			{
				if(sa->rk[now]<sa->rk[id])
				{
	//				puts("OK");
					res=len;
					ans=rept;
					id=now;
				}
			}
		}
	}
	if(id==-1) id=sa->sa[1],res=1;
//	printf("ans ");
//	printf("%d %d\n",id,res);
	printf("Case %d: ",++T);
	rep(i,id,id+res) putchar(s[i]);
	puts("");
	delete sa;
	delete rsa;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	Log2[1]=0;
	rep(i,2,M) Log2[i]=Log2[i>>1]+1;
	while(scanf("%s",s+1)!=EOF,s[1]!='#') solve();
	return 0;
}
