/*
    tags: greedy
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
priority_queue<pii>Q;
const int M=100000;
ll v[M+5];
int main()
{
	int n,K;
	scanf("%d%d",&n,&K);
	rep(i,1,n+1)
	{
		scanf("%lld",&v[i]);
		Q.push(pii(-v[i],0));
	}
	ll ans=0;
	while((n-1)%(K-1)) n++,Q.push(pii(0,0));
	while(Q.size()>1)
	{
		int cnt=0;
		pii p=pii(0,0);
		while(!Q.empty()&&cnt<K)
		{
			p.fi+=Q.top().fi;
			p.se=min(p.se,Q.top().se);
			Q.pop();
			cnt++;
		}
		p.se--;
		ans+=p.fi;
		Q.push(p);
	}
	printf("%lld\n%d\n",-ans,-Q.top().se);
	return 0;
}
