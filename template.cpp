#include <set>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb push_back
#define pq priority_queue
#define lowbit(x) ((x)&-(x))
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl 
#define debug(x) cout<<#x<<" = "<<x<<endl;
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
#define rep(i,a,b) for(int i=a,i##_BEGIN_=b;i<i##_BEGIN_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_END_=a;i>=i##_END_;--i)
using namespace std;
const int mod=1e9+7;
const int MAX_INT=0x7fffffff,INF=1e9;
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
void print(int x)
{
	if(!x) return;
	print(x/10);
	putchar(x%10^48);
}
inline void pt(int x)
{
	if(!x) putchar('0');
	else print(x);
	putchar('\n');
}
inline void rd(int&res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
template<class Ty>inline void chk_min(Ty&x,Ty y){if(x>y)x=y;}
template<class Ty>inline void chk_max(Ty&x,Ty y){if(x<y)x=y;}
int main()
{
	
	return 0;
}
