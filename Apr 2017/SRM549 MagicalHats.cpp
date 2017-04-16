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
vector<int>lg;
const int M=15;
int n,m,cnt,ccnt;
int x[M],y[M],islegal[1<<M],xcnt[M],ycnt[M];
int dp[1594323];
bool mark[1<<M];
class MagicalHats {
	public:
	bool is_legal(int S)
	{
		rep(i,0,n) xcnt[i]=0;
		rep(i,0,m) ycnt[i]=0;
		int tot=0;
		rep(i,0,cnt)
		{
			xcnt[x[i]]++;
			ycnt[y[i]]++;
			if(S&(1<<i))
			{
				tot++;
				xcnt[x[i]]++;
				ycnt[y[i]]++;
			}
		}
		if(tot!=ccnt) return false;
		rep(i,0,n) if(xcnt[i]&1) return false;
		rep(i,0,m) if(ycnt[i]&1) return false;
		return true;
	}
	bool Is_legal(int S)
	{
		rep(i,0,lg.size()) mark[i]=0;
		rep(i,0,cnt)
		{
			if(S%3==2) rep(j,0,lg.size()) if(lg[j]&(1<<i)) mark[j]=1;
			if(S%3==1) rep(j,0,lg.size()) if(!(lg[j]&(1<<i))) mark[j]=1;
			S/=3;
		}
		rep(i,0,lg.size()) if(!mark[i]) return true;
		return false;
	}
	int rec(int S,int num)
	{
		if(num==0) return 0;
		int &res=dp[S];
		if(res!=-1) return res;
		res=0;
		int tmp=1;
		rep(i,0,cnt)
		{
			if((S/tmp)%3==0)
			{
				int temp=inf;
				if(Is_legal(S+tmp)) temp=min(temp,rec(S+tmp,num-1)+1);
				if(Is_legal(S+tmp*2)) temp=min(temp,rec(S+tmp*2,num-1));
				if(temp!=inf) res=max(res,temp);
			}
			tmp*=3;
		}
		return res;
	}
	int findMaximumReward(vector<string> board, vector<int> coins, int numGuesses) {
		clr(dp,-1);
		lg.clear();
		n=board.size(),m=board[0].length();
		cnt=0;
		rep(i,0,n) rep(j,0,m) if(board[i][j]=='H') x[cnt]=i,y[cnt++]=j;
		ccnt=coins.size();
		rep(i,0,1<<cnt)
			if(is_legal(i)) lg.pb(i);
		if(!Is_legal(0)) return -1;
		int c=rec(0,numGuesses);
		sort(coins.begin(),coins.end());
		int ans=0;
		rep(i,0,c) ans+=coins[i];
		return ans;
	}
};
