#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=500005;
typedef long long ll;
char s[M];
int mp[300];
int K;
struct Suffix_Array
{
	int sa[M],rk[M],h[M],v[M],stk[2][M];
	ll ans;
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
//			printf("%d %d\n",i,j);
			for(;s[i+k]==s[j+k];++k);
			h[rk[i]]=k;
			if(k) --k;
		}
	}
	void calc(int f,int n)
	{
		int top=0;
		ll tot=0;
		//stk[0]ÖÐÎ¬»¤µÄÊÇÒ»¸ö°´ÕÕheight[i]µÝÔöµÄÐòÁÐ 
		//stk[1]ÖÐÎ¬»¤µÄÊÇcnt[i]±íÊ¾µ±Ç°Õâ¸öµãÕÆ¹ÜµÄºó×º¸öÊý 
		rep(i,2,n+1)
		{
			if(h[i]<K) top=tot=0;//ÒÔºó¿Ï¶¨ÓëÖ®Ç°µÄºó×ºÎÞ¹Ø 
			else
			{
				int cnt=0;
				if(v[i-1]==f) tot+=h[i]-K+1,cnt=1;//Èç¹ûÉÏÒ»¸öºó×ºÔÚµÚÒ»¸ö×Ö·û´®ÖÐ£¬ÄÇÃ´¿ÉÒÔËãÉÏÒ»¸ö 
				while(top>0&&h[i]<=h[stk[0][top]])
				{
					cnt+=stk[1][top];
					tot-=stk[1][top]*(h[stk[0][top]]-h[i]);
					--top;
				}
				stk[0][++top]=i;
				stk[1][top]=cnt;
				if(v[i]!=f) ans+=tot;
			}
		}
	}
	void solve(int mid,int n)
	{
//		sa[i]<mid ÊôÓÚµÚÒ»¸ö×Ö·û´®
//		sa[i]>mid ÊôÓÚµÚ¶þ¸ö×Ö·û´®
		ans=0;
		v[1]=-1;
		rep(i,2,n+1)
		{
			if(sa[i]<mid) v[i]=1;
			else v[i]=0;
		}
		assert(sa[1]==mid);
		calc(0,n);
		calc(1,n);
		printf("%lld\n",ans);
	}
}sa;
void pret()
{
	int t=0;
	mp['a'-1]=++t;
	rep(i,'A','Z'+1) mp[i]=++t; 
	rep(i,'a','z'+1) mp[i]=++t;
}
int main()
{
	pret();
	while(scanf("%d",&K)!=EOF,K)
	{
		scanf("%s",s+1);
		int n=strlen(s+1);
		int mid=n+1;
		s[n+1]='a'-1;
		scanf("%s",s+n+2);
		n=strlen(s+1);
		sa.build(s,n,53);
		sa.solve(mid,n);
	}
	return 0;
}
