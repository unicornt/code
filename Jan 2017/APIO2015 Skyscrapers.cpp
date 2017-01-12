#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define fi first
#define se second
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
int n,m;
void chk_min(int&x,int y)
{
	if(x>y) x=y;
}
const int N=2000;
const int M=30000;
const int INF=0x7fffffff;
namespace P100
{
	struct node
	{
		int p,step,d,dis;
		node(int a,int b,int c,int e):p(a),step(b),d(c),dis(e){}
		node(){}
	};
	const int S=170;
	int dis[M][200];
	bool mark[M+5];
	queue<node>Q;
	vector<int>edge[M+5];
	void add_edge(int v,int d)
	{
		mark[v]=1;
		rep(i,0,edge[v].size())
		{
			int t=edge[v][i];
			if(t<S)
			{
				if(dis[v][t]==-1) dis[v][t]=d;
				else continue;
			}
			Q.push(node(v,t,-1,d));
			Q.push(node(v,t,1,d));
		}
	}
	void solve()
	{
		memset(dis,-1,sizeof(dis));
		int s,t;
		rep(i,0,m)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			if(i==0) s=a;
			if(i==1) t=a;
			edge[a].pb(b);
		}
		add_edge(s,0);
		while(!Q.empty())
		{
			node now=Q.front();
			Q.pop();
			int p=now.p,step=now.step,d=now.d,dist=now.dis;
			if(p==t)
			{
				printf("%d\n",dist);
				exit(0);
			}
			int to=p+step*d;
			if(to>=0&&to<n)
			{
				if(step<S)
				{
					if(dis[to][step]==-1) dis[to][step]=dist+1;
					else continue;
				}
				Q.push(node(to,step,d,dist+1));
				if(!mark[to]) add_edge(to,dist+1);
			}
		}
		puts("-1");
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	P100::solve();
//	P57::solve();
	return 0;
}
/*
5 3
0 2
1 1
4 1
*/
