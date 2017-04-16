#include <bits/stdc++.h>
#define fi first
#define se second
#define pb(x) push_back(x)
#define all(x) x.begin(),x.end()
#define clr(x,y) memset(x,y,sizeof(x))
#define prt(x) cerr<<x<<' '
#define pts(x) cerr<<x<<endl
#define lowbit(x) ((x)&-(x))
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define forall(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define showtime fprintf(stderr,"time = %.15fn",clock()/(double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned uint;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
const int mod=1e9+7,INF=0x7fffffff,inf=2e8;//2 yi
const ll linf=(ll)1e18;
const db pi=acos(-1.0),eps=1e-8;
int mod_pow(int x,int b,int MOD=mod){
	int res=1;
	for(;b;b>>=1,x=(ll)x*x%MOD)
		if(b&1) res=(ll)res*x%MOD;
	return res;
}
void mod_add(int&x,int y,int MOD=mod){
	x+=y;
	if(x>=MOD) x-=MOD;
}
void mod_minus(int&x,int y,int MOD=mod){
	x-=y;
	if(x<0) x+=MOD;
}
template<class Ty>Ty gcd(Ty a,Ty b){return a?gcd(b%a,a):b;}
template<class Ty>void chk_min(Ty&x,Ty y){if(x>y)x=y;}
template<class Ty>void chk_max(Ty&x,Ty y){if(x<y)x=y;}
class KingdomAndDice {
	public:
	bool dp[55][2505],tmp[55][2505];
	double newFairness(vector<int> B, vector<int> A, int X) {
		int n=A.size();
		A.push_back(0);
		A.push_back(X+1);
		sort(A.begin(),A.end());
		int cnt=0,tot=0;
		rep(i,0,n)
		{
			if(B[i])
			{
				int p=upper_bound(A.begin(),A.end(),B[i])-A.begin()-1;
				cnt+=p;
			}
			else tot++;
		}
		A.erase(unique(A.begin(),A.end()),A.end());
		sort(B.begin(),B.end());
		clr(dp,0);
		dp[tot][cnt]=1;
		int q=0;
		rep(i,0,A.size()-1)
		{
			int c=0;
			int L=A[i]+1,R=A[i+1]-1;
			while(q<B.size()&&B[q]<=R) q++,c++;
			if(L>R) continue;
			//[L,R]
			//p=i
			rep(k,0,tot+1)
			{
				rep(j,0,n*n+1)
				{
					if(!dp[k][j]) continue;
					rep(w,0,min(R-L-c+1,k)+1)
					{
						if(j+i*w>n*n) break;
						tmp[k-w][j+i*w]=1;
					}
				}
			}
			rep(k,0,tot+1) rep(j,0,n*n+1) dp[k][j]|=tmp[k][j],tmp[k][j]=0;
		}
		rep(i,0,tot+1) rep(j,0,n*n+1) dp[0][j]|=dp[i][j];
		int mid1=n*n/2,mid2=(n*n+1)/2;
		int delta=n*n;
		bool f=0;
		rep(i,0,n*n+1)
		{
			if(dp[0][i])
			{
				if(i<=mid1)
				{
					if(mid1-i<delta) delta=mid1-i,f=0;
				}
				else
				{
					if(i-mid2<delta) delta=i-mid2,f=1;
				}
			}
		}
		if(!f) delta=mid1-delta;
		else delta=mid2+delta;
		return (double)delta/(n*n);
	}
};
