#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
template<class Ty>inline void rd(Ty&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') c=getchar(),flag=true;
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
typedef long long ll;
const int M=100000;
ll n;
int q;
char opt[M+5];
ll lowbit(ll x){return x&(-x);}
int main()
{
	rd(n);rd(q);
	ll cur;
	rep(i,0,q)
	{
		rd(cur);
		scanf("%s",opt);
		rep(i,0,strlen(opt))
		{
			if(opt[i]=='L') cur-=lowbit(cur)>>1;
			else if(opt[i]=='R')
			{
				if(cur+(lowbit(cur)>>1)<=n) cur+=lowbit(cur)>>1;
			}
			else
			{
				if(cur==((n+1)>>1)) continue;
				ll fa1=cur-lowbit(cur);
				ll fa2=cur+lowbit(cur);
				if(abs(fa1-cur)==(lowbit(fa1)>>1)) cur=fa1;
				else if(abs(fa2-cur)==(lowbit(fa2)>>1)) cur=fa2;
				else assert(false);
			}
		}
		printf("%I64d\n",cur);
	}
	return 0;
}
