#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define prt(x) cout<<x<<' '
#define pts(x) cout<<x<<endl
#define debug(x) cout<<#x<<" = "<<x<<endl
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long ull;
const int M=100005;
const int S=333;
ll mod;
char str[M];	
ll C[M],num[M];
void pret()
{
	ull now=0;
	int len=strlen(str);
	C[len]=0;
	ull bas=1;
	per(i,0,len)
	{
		now=(now+bas*(str[i]-'0'))%mod;
		bas=bas*10%mod;
		num[i]=now;
		C[i]=now;
	}
	sort(C,C+len+1);
	int t=unique(C,C+len+1)-C;
	rep(i,0,len+1) num[i]=lower_bound(C,C+t,num[i])-C;
}
struct node
{
	int l,r,ls;
	node(){}
	node(int a,int b):l(a),r(b)
	{
		ls=l/S;
	}
}qry[M];
bool cmp(int a,int b)
{
	if(qry[a].ls!=qry[b].ls) return qry[a].ls<qry[b].ls;
	return qry[a].ls&1?qry[a].r<qry[b].r:qry[a].r>qry[b].r;
}
int B[M];
ll ans[M],res;
int cnt[M];
void add(int x)
{
	res+=cnt[num[x]];
	cnt[num[x]]++;
}
void del(int x)
{
	cnt[num[x]]--;
	res-=cnt[num[x]];
}
inline void rd(int &res)
{
	res=0;char c;
	while(c=getchar(),c<48);
	do res=res*10+(c^48);
	while(c=getchar(),c>47);
}
ll sum[M];
void spj()
{
	int len=strlen(str);
	rep(i,1,len+1)
	{
		sum[i]=sum[i-1];
		cnt[i]=cnt[i-1];
		if((str[i-1]-'0')%mod==0) sum[i]+=i,cnt[i]++;
	}
	int q;
	rd(q);
	rep(i,1,q+1)
	{
		int a,b;
		rd(a);rd(b);
		printf("%lld\n",sum[b]-sum[a-1]-(ll)(cnt[b]-cnt[a-1])*(a-1));
	}
}
int main()
{
	scanf("%lld",&mod);
	scanf("%s",str);
	if(mod==2||mod==5) spj();
	else
	{
		pret();
		int q;
		scanf("%d",&q);
		rep(i,1,q+1)
		{
			int a,b;
			rd(a);rd(b);
			--a;
			qry[i]=node(a,b);
			B[i]=i;
		}
		sort(B+1,B+q+1,cmp);
		int l=0,r=0;
		cnt[num[0]]=1;
		res=0;
		rep(iid,1,q+1)
		{
			int i=B[iid];
			//[l,r]
			while(l<qry[i].l) del(l++);
			while(l>qry[i].l) add(--l);
			while(r<qry[i].r) add(++r);
			while(r>qry[i].r) del(r--);
			ans[i]=res;
		}
		rep(i,1,q+1) printf("%lld\n",ans[i]);
	}
	return 0;
}
