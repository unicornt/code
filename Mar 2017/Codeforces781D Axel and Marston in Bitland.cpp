/*
	notes: 矩阵转移比较好想，但是重点似乎在用bitset压位上==
*/
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <bitset>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb(x) push_back(x)
#define clr(x,y) memset(x,y,sizeof(x))
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define showtime fprintf(stderr,"time = %.15f\n",clock()/(double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
template<class Ty>inline void rd(Ty&res)
{
	res=0;char c;
	bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar();
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
const int M=500;
bitset<M+5>mat[2][70][M+5],ret,tmp;
int main()
{
	int n,m;
	rd(n);rd(m);
	rep(i,0,m)
	{
		int a,b,c;
		rd(a);rd(b);rd(c);
		a--;b--;
		mat[c][0][a][b]=1;
	}
	rep(i,1,62)
	{
		rep(j,0,n)rep(k,0,n)rep(h,0,2)
			if(mat[h][i-1][j][k]) mat[h][i][j]|=mat[h^1][i-1][k];
	}
	ret.reset();
	ret[0]=1;
	ll ans=0;
	bool flag=0;
	per(i,0,62)
	{
		tmp.reset();
		rep(j,0,n) if(ret[j]) tmp|=mat[flag][i][j];
		if(tmp.any())
		{
			ret=tmp;
			ans+=1ll<<i;
			flag^=1;
		}
	}
	if(ans>(ll)1e18) ans=-1;
	cout<<ans<<endl;
	return 0;
}
