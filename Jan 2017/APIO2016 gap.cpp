#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "gap.h"
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
using namespace std;
static void my_assert(int k){ if (!k) exit(1); }

static int subtask_num, N;
static long long A[100001];
static long long call_count;

typedef long long ll;
const int M=100005;
const ll INF=1e18;
ll x[M];
long long findGap(int c,int n)
{
	ll *mi=new ll,*mx=new ll;
	if(c==1)
	{
		ll l=0,r=INF;
		int tot=0;
		while(tot<n)
		{
			MinMax(l,r,mi,mx);
			l=(*mi)+1;
			r=(*mx)-1;
			x[tot++]=*mi;
			x[tot++]=*mx;
		}
		sort(x,x+tot);
		ll ans=0;
		rep(i,1,tot) ans=max(ans,x[i]-x[i-1]);
		return ans;
	}
	else
	{
		MinMax(0,INF,mi,mx);
		ll MI=*mi,MX=*mx;
		ll ans,delta;
		ans=delta=(MX-MI)/(n-1);
		ll last=MI,pre=MI;
		while(last<=MX){
			MinMax(last,last+delta,mi,mx);
			last=last+delta+1;
			if(*mi!=-1) ans=max(ans,*mi-pre),pre=*mx;
		}
		return ans;
	}
}
