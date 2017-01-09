/*
	tags: 后缀数组，单调栈
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define prt(x) cout<<(x)<<' '
#define pts(x) cout<<(x)<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
const int M=500000;
typedef long long ll;
int n;
struct Suffix_Array
{
	int sa[M+5],rk[M+5],v[M+5],h[M+5];
	void build(char*s,int n,int m)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=s[i]-'a'+1]++;
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		for(int k=1;k<=n;k<<1)
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
	int L[M],R[M];
	int stk[M];
	void solve(int n)
	{
		int top=0;
		stk[++top]=1;
		h[1]=-1;
		ll ans=0;
//		rep(i,1,n+1) prt(h[i]);
//		puts("");
		ll res=0;
		rep(i,1,n+1)
		{
			int mi=0x7fffffff;
			rep(j,i+1,n+1)
			{
				mi=min(mi,h[j]);
				res+=mi;
			}
		}
		rep(i,2,n+1)
		{
			while(h[i]<=h[stk[top]])
			{
				R[stk[top]]=i;
//				printf("R %d : %d\n",i);
//				ans+=(ll)h[stk[top]]*(i-stk[top]);
				top--;
			}
			L[i]=stk[top];
//			printf("L %d : %d\n",i,stk[top]);
//			ans+=(ll)h[i]*(i-stk[top]);
			stk[++top]=i;
		}
		rep(i,2,n+1)
		{
			if(!R[i]) R[i]=n+1;
//			printf("%d %d\n",L[i],R[i]);
			if(R[i]>L[i]) ans+=(ll)h[i]*(i-L[i])*(R[i]-i);
		}
//		rep(i,2,top+1)
//		{
//			ans+=(ll)h[stk[i]]*(n+1-stk[i]);
////			debug(h[stk[i]]);
//		}
//		assert(res==ans);
//		debug(res);debug(ans);
//		printf("%lld\n",(ll)(n+1)*n*(n-1)/2);
//		assert(res==(ll)(n+1)*n*(n-1)/2-ans);
//		printf("%lld\n",res);
		printf("%lld\n",(ll)(n+1)*n*(n-1)/2-2*ans);
	}
}sa;
char s[M+5];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	sa.build(s,n,26);
	sa.solve(n);
	return 0;
}
