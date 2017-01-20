#include <vector>
#include <map>
#include <set>
#include <queue>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define clr(x,y) memset(x,y,sizeof(x))
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define lowbit(x) ((x)&-(x))
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define forall(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned uint;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
const int mod=1e9+7,INF=0x7fffffff,inf=200000000;//2 yi
const ll linf=(ll)1e18;
const db pi=acos(-1.0),eps=1e-8;
int fast_pow(int x,int b,int MOD=mod){
	int res=1;
	for(;b;b>>=1,x=(ll)x*x%MOD)
		if(b&1)res=(ll)res*x%MOD;
	return res;
}
void add(int&x,int y,int MOD=mod){x+=y;if(x>=MOD)x-=MOD;}
void del(int&x,int y,int MOD=mod){x-=y;if(x<0)x+=MOD;}
template<class Ty>Ty gcd(Ty a,Ty b){return a?gcd(b%a,a):b;}
template<class Ty>void chk_min(Ty&x,Ty y){if(x>y)x=y;}
template<class Ty>void chk_max(Ty&x,Ty y){if(x<y)x=y;}
int main()
{
	
	return 0;
}
