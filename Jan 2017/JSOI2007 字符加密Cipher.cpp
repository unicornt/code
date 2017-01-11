#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=200000;
char s[M+5];
struct suffix_array
{
	int sa[M+5],rk[M+5],h[M+5],v[M+5];
	void build(char*s,int n,int m)
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
	}
}sa;
char B[M+5];
int main()
{
	scanf("%s",s+1);
	int len,n;
	len=n=strlen(s+1);
	rep(i,1,len+1) B[i-1]=s[i];
	sort(B,B+len);
	int tot=unique(B,B+len)-B;
	rep(i,1,len+1) s[i]=lower_bound(B,B+tot,s[i])-B+1;
	rep(i,1,n+1) s[n+i]=s[i];
	n<<=1;
	sa.build(s,n,tot);
	rep(i,1,n+1)
	{
		if(sa.sa[i]>len) continue;
		printf("%c",B[s[sa.sa[i]+len-1]-1]);
	}
	return 0;
}
