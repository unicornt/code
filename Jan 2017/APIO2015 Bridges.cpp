/*
	tags: 贪心,堆(求中位数)
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pts(x) cout<<x<<endl
#define prt(x) cout<<x<<' '
#define debug(x) cout<<#x<<" = "<<x<<endl
#define fi first
#define se second
using namespace std;
const int M=100000;
typedef long long ll;
typedef pair<int,int> pii;
int K,n,A[M+5],B[M+5];
char s1[3],s2[3];
ll sum[M+5];
bool cmp(pii a,pii b)
{
	return a.fi+a.se<b.fi+b.se;
}
struct Heap
{
	priority_queue<int,vector<int>,greater<int> >q;
	priority_queue<int>p;
	ll sump,sumq,cntp,cntq;
	int mid;
	void init()
	{
		while(!q.empty()) q.pop();
		while(!p.empty()) p.pop();
		cntp=cntq=0;
		sump=sumq=0;
		mid=-1;
	}
	ll query()
	{
		return (ll)mid*(cntp-cntq)-sump+sumq;
	}
	void update()
	{
		if(cntp>cntq)
		{
			cntq++;
			sumq+=mid;
			q.push(mid);
			mid=p.top();
			sump-=mid;
			cntp--;
			p.pop();
		}
		else
		{
			cntp++;
			sump+=mid;
			p.push(mid);
			mid=q.top();
			sumq-=mid;
			cntq--;
			q.pop();
		}
	}
	void push(int x)
	{
		if(mid==-1)
		{
			mid=x;
		}
		else
		{
			if(x<=mid) p.push(x),cntp++,sump+=x;
			else q.push(x),cntq++,sumq+=x;
		}
		while(abs(cntp-cntq)>=2) update();
	}
}hp;
pii p[M+5];
int main()
{
	scanf("%d%d",&K,&n);
	ll ans=0;
	rep(i,1,n+1)
	{
		int a,b;
		scanf("%s %d %s %d",s1,&a,s2,&b);
		if(a>b) swap(a,b);
		if(s1[0]==s2[0])
		{
			i_END_--;
			n--;
			i--;
			ans+=b-a;
		}
		else
		{
			ans++;
			p[i]=pii(a,b);
		}
	}
	if(!n)
	{
		pts(ans);
		return 0;
	}
	if(K>1) sort(p+1,p+n+1,cmp);
	hp.init();
	rep(i,1,n+1)
	{
		hp.push(p[i].fi);
		hp.push(p[i].se);
		sum[i]=hp.query();
	}
	if(K==1) pts(ans+sum[n]);
	else
	{
		hp.init();
		ll res=sum[n];
		per(i,1,n+1)
		{
			hp.push(p[i].fi);
			hp.push(p[i].se);
			res=min(res,sum[i-1]+hp.query());
		}
		printf("%lld\n",ans+res);
	}
	return 0;
}
