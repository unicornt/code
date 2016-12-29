#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=200005;
char str[M];
int sa[M],rk[M],h[M],v[M],n;
void build(char*s,int m)
{
	int *x=rk,*y=h;
	rep(i,0,m) v[i]=0;
	rep(i,1,n+1) v[x[i]=s[i]-'a'+1]++;
	rep(i,1,m) v[i]+=v[i-1];
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
			if(x[sa[i-1]]!=x[sa[i]]||x[sa[i-1]+k]!=x[sa[i]+k]) p++;
			y[sa[i]]=p;
		}
		swap(x,y);
		if(p==n) break;
	}
	if(x!=rk) memcpy(rk,x,n+1<<2);
	int k=0;
	rep(i,1,n+1)
	{
		int p=sa[rk[i]-1];
		for(;s[i+k]==s[p+k];k++);
		h[rk[i]]=k;
		if(k) k--;
	}
}
void print()
{
	rep(i,1,n+1) printf("%d%c",sa[i]," \n"[i==n]);
	rep(i,2,n+1) printf("%d%c",h[i]," \n"[i==n]);
}
int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	build(str,27);
	print();
	return 0;
}
