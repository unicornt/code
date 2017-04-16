#include <bits/stdc++.h>
#define fi first
#define se second
#define pb(x) push_back(x)
#define clr(x,y) memset(x,y,sizeof(x))
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
const int mod=1e9+7,INF=0x7fffffff,inf=2e8;//2 yi
const db pi=acos(-1.0),eps=1e-8;
int mod_pow(int x,int b,int MOD=mod){
	int res=1;
	for(;b;b>>=1,x=(ll)x*x%MOD)
		if(b&1) res=(ll)res*x%MOD;
	return res;
}
typedef pair<int,int> pii;
class ColorfulWolves
{
	public:
	static const int M=50;
	vector<pii>edge[M+5];
	int sum[M+5][M+5];
	priority_queue<pii>Q;
	int dis[M+5];
	void Dijkstra(int st)
	{
		Q.push(pii(0,st));
		clr(dis,-1);
		dis[st]=0;
		while(!Q.empty())
		{
			int x=Q.top().se;
			Q.pop();
			rep(i,0,edge[x].size())
			{
				int to=edge[x][i].fi;
				if(dis[to]==-1||dis[to]>dis[x]+edge[x][i].se)
				{
					dis[to]=dis[x]+edge[x][i].se;
					Q.push(pii(-dis[to],to));
				}
			}
		}
	}
	int getmin(vector<string> colormap)
	{
		int n=colormap.size();
		clr(sum,0);
		rep(i,1,n+1)
			rep(j,1,n+1)
				sum[i][j]=sum[i][j-1]+(colormap[i-1][j-1]=='Y');
		rep(i,1,n+1)rep(j,1,n+1)
		{
			if(colormap[i-1][j-1]=='Y') edge[i].pb(pii(j,sum[i][j-1]));
		}
		Dijkstra(1);
		return dis[n];
	}
};
