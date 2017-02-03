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
#define showtime fprintf(stderr,"time = %.15f\n",clock()/(double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
typedef unsigned uint;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
const int mod=1000000009,INF=0x7fffffff,inf=2e8;//2 yi
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
class FoxAndMountain {
	public:
	static const int M=50;
	int f[M+5];
	void getfail(vector<int>&x,int n)
	{
		f[1]=0;
		rep(i,2,n+1)
		{
			int j=f[i-1];
			while(j&&x[j+1]!=x[i]) j=f[j];
			f[i]=(x[j+1]==x[i]?j+1:j);
		}
//		rep(i,1,n+1) dig("%d ",f[i]);
//		puts("");
	}
	vector<int>his;
	int m;
	int dp[M+5][M+5][M+5][2];
	void trans(int p,int h,int mat,int t,int w)
	{
		if(h+w<0) return;
		int j;
		for(j=mat;j&&his[j+1]!=w;j=f[j]);
		if(his[j+1]==w) j++;
		if(j==m) mod_add(dp[p][h+w][f[j]][1|t],dp[p-1][h][mat][t]);
		else mod_add(dp[p][h+w][j][t],dp[p-1][h][mat][t]);
	}
	void solve(int p,int h,int mat,int t)
	{
		trans(p,h,mat,t,-1);
		trans(p,h,mat,t,1);
	}
	int count(int n, string history) {
		m=history.size(); 
		his.resize(m+1);
		rep(i,1,m+1) his[i]=history[i-1]=='D'?-1:1;
		getfail(his,m);
		clr(dp,0);
		dp[0][0][0][0]=1;
		rep(i,1,n+1)
		{
			rep(j,0,i)
			{//i-1µÄ¸ß¶È 
				rep(k,0,m)
				{//Æ¥ÅäÁËkÎ» 
					//ÓÐ¹ýhistory
					if(dp[i-1][j][k][1]) solve(i,j,k,1);
					//Ã»ÓÐ¹ý 
					if(dp[i-1][j][k][0]) solve(i,j,k,0);
				}
			}
		}
		int ans=0;
		rep(i,0,m) mod_add(ans,dp[n][0][i][1]);
		return ans;
	}
};

// CUT begin
ifstream data("FoxAndMountain.sample");

string next_line() {
	string s;
	getline(data, s);
	return s;
}

template <typename T> void from_stream(T &t) {
	stringstream ss(next_line());
	ss >> t;
}

void from_stream(string &s) {
	s = next_line();
}

template <typename T>
string to_string(T t) {
	stringstream s;
	s << t;
	return s.str();
}

string to_string(string t) {
	return "\"" + t + "\"";
}

bool do_test(int n, string history, int __expected) {
	time_t startClock = clock();
	FoxAndMountain *instance = new FoxAndMountain();
	int __result = instance->count(n, history);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (__result == __expected) {
		cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
		return true;
	}
	else {
		cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
		cout << "		   Expected: " << to_string(__expected) << endl;
		cout << "		   Received: " << to_string(__result) << endl;
		return false;
	}
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
	int cases = 0, passed = 0;
	while (true) {
		if (next_line().find("--") != 0)
			break;
		int n;
		from_stream(n);
		string history;
		from_stream(history);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(n, history, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1486041211;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
	set<int> cases;
	bool mainProcess = true;
	for (int i = 1; i < argc; ++i) {
		if ( string(argv[i]) == "-") {
			mainProcess = false;
		} else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "FoxAndMountain (1000 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
