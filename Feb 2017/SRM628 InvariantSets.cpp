#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stack>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <utility>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define pq priority_queue
#define clr(a,b) memset(a,b,sizeof(a))
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define forall(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
using namespace std;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef double db;
const int mod=1000000007;
const int INF=0x7fffffff;
const int inf=20000000;//2000w
const ll linf=1LL<<60;
const db pi=acos(-1.0);
const db eps=1e-8;
int fast_pow(int x,int b,int MOD=mod){
	int res=1;
	for(;b;b>>=1,x=(ll)x*x%MOD)
		if(b&1) res=(ll)res*x%MOD;
	return res;
}
void add(int&x,int y,int MOD=mod){
	x+=y;
	if(x>=MOD) x-=MOD;
}
void del(int&x,int y,int MOD=mod){
	x-=y;
	if(x<0) x+=MOD;
}
ll gcd(ll a,ll b){
	return a?gcd(b%a,a):b;
}
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
class InvariantSets {
	public:
	static const int M=50;
	int vis[M+5];
	bool cyc[M+5];
	vector<int>edge[M+5];
	ll solve(int x)
	{
		ll ret=1;
		rep(i,0,edge[x].size())
		{
			int to=edge[x][i];
			if(!cyc[to]) ret*=(1+solve(to));
		}
		return ret;
	}
	long long countSets(vector<int> f) {
		int n=f.size();
		rep(i,0,n) edge[f[i]].pb(i);
		clr(vis,-1);
		ll ans=1;
		rep(i,0,n)
		{
			int u;
			for(u=i;vis[u]==-1;u=f[u])
				vis[u]=i;
			if(vis[u]==i)
			{//ÕÒµ½Ò»¸ö»· 
				ll res=1;
				for(int w=u;;)
				{
					cyc[w]=true;
					if((w=f[w])==u) break;
				}
				for(int w=u;;)
				{
					res*=solve(w);
					if((w=f[w])==u) break;
				}
				ans*=(1+res);
			}
		}
		return ans;
	}
};

// CUT begin
ifstream data("InvariantSets.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
	int len;
	from_stream(len);
	ts.clear();
	for (int i = 0; i < len; ++i) {
		T t;
		from_stream(t);
		ts.push_back(t);
	}
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

bool do_test(vector<int> f, long long __expected) {
	time_t startClock = clock();
	InvariantSets *instance = new InvariantSets();
	long long __result = instance->countSets(f);
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
		vector<int> f;
		from_stream(f);
		next_line();
		long long __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if ( do_test(f, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1486030924;
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
		cout << "InvariantSets (1000 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
