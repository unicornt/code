#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define pq priority_queue
#define lowbit(x) ((x)&-(x))
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl 
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
#define rep(i,a,b) for(int i=a,i##_BEGIN_=b;i<i##_BEGIN_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_END_=a;i>=i##_END_;--i)
using namespace std;
const int mod=1e9+7;
const int MAX_INT=0x7fffffff,INF=1e9;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
void print(int x)
{
	if(!x) return;
	print(x/10);
	putchar(x%10^48);
}
inline void pt(int x)
{
	if(!x) putchar('0');
	else print(x);
	putchar('\n');
}
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
template<class Ty>inline void chk_min(Ty&x,Ty y){if(x>y)x=y;}
template<class Ty>inline void chk_max(Ty&x,Ty y){if(x<y)x=y;}
const int M=2005;
const int S=15;
char str[M];
int mp[300];
struct Suffix_Array
{
	int sa[M],h[M],v[M],rk[M],Log2[M],pre[M][S];
	void build(char *s,int m,int n)
	{
		int *x=rk,*y=h;
		rep(i,0,m+1) v[i]=0;
		rep(i,1,n+1) v[x[i]=mp[s[i]]]++;
		// rep(i,1,n+1) printf("%d ",x[i]);
		// puts("");
		rep(i,1,m+1) v[i]+=v[i-1];
		rep(i,1,n+1) sa[v[x[i]]--]=i;
		x[0]=-1;
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
				if(x[sa[i]]!=x[sa[i-1]]||x[sa[i]+k]!=x[sa[i-1]+k])
					p++;
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
			for(;s[i+k]==s[p+k];++k);
			h[rk[i]]=k;
			if(k) k--;
		}
		// rep(i,1,n+1) printf("%d ",sa[i]);
		// puts("");
		// rep(i,1,n+1) printf("%d ",rk[i]);
		// puts("");
	}
	void pret(int n)
	{
		Log2[1]=0;
		rep(i,2,n+1) Log2[i]=Log2[i>>1]+1;
		rep(i,1,n+1) pre[i][0]=h[i];
		rep(k,1,S)
			rep(j,1,n-(1<<k)+1)
				pre[j][k]=min(pre[j][k-1],pre[j+(1<<(k-1))][k-1]);
	}
	int querymi(int L,int R)
	{
		if(L>R) swap(L,R);
		int mi=1e8;
		rep(i,L+1,R+1) mi=min(mi,h[i]);
		if(mi==1e8) mi=0;
		return mi;
		// if(L>R) swap(L,R);
		// int k=Log2[R-L+1];
		// return min(pre[L][k],pre[R-(1<<k)+1][k]);
	}
	void solve(int n)
	{
		int ans=1;
		int id=1,f=0;
		// rep(i,1,n+1) printf("%c",str[i]);
		// puts("");
		rep(i,1,n/2+1)
		{
			int tmp=querymi(rk[i],rk[n-i+1]);
			// printf("%c %c :  %d\n",str[i],str[n-i+1],tmp);
			// printf("querymi (%d , %d)\n",rk[i],rk[n-i+1]);
			if(tmp*2-1>ans*2-(!f))
			{
				f=0;
				ans=tmp;
				id=i;
			}
			// printf("%d %d\n",i,n-i+2);
			if(n-i+2<=n)
			{
				tmp=querymi(rk[i],rk[n-i+2]);
				if(tmp*2>ans*2-(!f))
				{
					f=1;
					ans=tmp;
					id=i;
				}
			}
		}
		if(id!=-1)
		{
			// debug(ans);//
			// printf("%c\n",str[id]);//
			if(f)
			{
				// printf("f %d",ans);
				rep(i,id-ans,id+ans) printf("%c",str[i]);
			}else rep(i,id-ans+1,id+ans) printf("%c",str[i]);
			puts("");
		}
	}
}sa;
int main()
{
	memset(mp,-1,sizeof(mp));
	mp['a'-1]=0;
	rep(i,'a','z'+1) mp[i]=i-'a'+1;
	rep(i,'A','Z'+1) mp[i]=i-'A'+mp['z']+1;
	scanf("%s",str+1);
	int n=strlen(str+1);
	str[n+1]='a'-1;
	rep(i,1,n+1) str[n+n+1-i+1]=str[i];
	sa.build(str,mp['Z'],n*2+1);
	sa.pret(n*2+1);
	sa.solve(n*2+1);
	return 0;
}
