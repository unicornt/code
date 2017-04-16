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
class CosmicBlocks {
	public:
	int col[10],cnt[10],n;
	int num[12093234],line[10];
	int Hash(int S)
	{
		int cur=0;
		rep(i,0,n)
		{
			if(S&(1<<i)) cur++;
			line[col[i]]=cur;
		}
		int s=0;
		rep(i,0,n) s=s*6+line[i];
		return s;
	}
	int x[10],y[10],cntx[10],cnty[10];
	vector<int>vec[10];
	int getNumOrders(vector<int> blockTypes, int minWays, int maxWays) {
		n=blockTypes.size();
		rep(i,0,n) col[i]=i;
		do
		{
			//枚举B报颜色的顺序
			rep(i,0,1<<n)
			{
				//枚举当前颜色是否另起一行 
				rep(j,0,7) cnt[j]=0;
				int cur=0;
				rep(j,0,n)
				{
					if(i&(1<<j)) cur++;
					cnt[cur]+=blockTypes[j];
				}
				bool f=1;
				rep(j,1,cur+1) if(cnt[j]>cnt[j-1]) f=0;
				if(!f) continue;
//				rep(j,0,cur+1) printf("%d ",cnt[j]);
//				puts("");
				num[Hash(i)]++;
			}
		}while(next_permutation(col,col+n));
		int tot=1;
		rep(i,0,n+1) tot=tot*6;
		int ans=0;
		rep(i,0,tot)
		{
			if(num[i]>=minWays&&num[i]<=maxWays)
			{
				int temp=i;
				rep(j,0,7) cnt[j]=0,vec[j].clear();
				per(j,0,n)
				{
					line[j]=temp%6;
					vec[line[j]].pb(j);
					temp/=6;
				}
				rep(j,0,n) printf("%d ",cnt[j]);
				puts("");
				int res=1;
				rep(j,0,n)
				{
					if(vec[j+1].size()==0) break;
					int t=0;
					rep(k,0,vec[j].size())
						rep(w,0,vec[j+1].size()) 
				}
				ans+=res;
			}
		}
		return ans;
	}
};
