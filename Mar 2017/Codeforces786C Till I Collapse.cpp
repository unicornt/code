#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int M=100000;
int n,A[M+5],tot;
int bit[M+5];
void update(int x,int w)
{
	for(int i=x;i<=n;i+=i&-i) bit[i]+=w;
}
int query(int x)
{
	int res=0;
	for(int i=x;i>0;i-=i&-i) res+=bit[i];
	return res;
}
vector<int>qry[M+5];
int pos[M+5],nxt[M+5],ans[M+5];
int main()
{
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%d",&A[i]);
	rep(i,1,n+1) pos[i]=n+1;
	per(i,1,n+1)
	{
		nxt[i]=pos[A[i]];
		pos[A[i]]=i;
	}
	rep(i,1,n+1) qry[1].pb(i),update(pos[i],1);
	rep(i,1,n+1)
	{
		rep(j,0,qry[i].size())
		{
			int k=qry[i][j];
			int L=i,R=n,res=n+1;
			while(L<=R)
			{
				int mid=(L+R)>>1;
				if(query(mid)<=k) L=mid+1,res=mid;
				else R=mid-1;
			}
			ans[k]++;
			qry[res+1].pb(k);
		}
		update(i,-1);
		update(nxt[i],1);
	}
	rep(i,1,n+1) printf("%d ",ans[i]);
	return 0;
}
