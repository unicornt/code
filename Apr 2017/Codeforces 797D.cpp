#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int M=100000;
bool not_root[M+5];
int ans=0;
int ls[M+5],rs[M+5],val[M+5];
map<int,bool>mp;
void rec(int x,int l,int r)
{
	if(x==-1) return;
	if(val[x]>=l&&val[x]<=r) mp[val[x]]=1;
	rec(ls[x],l,min(r,val[x]-1));
	rec(rs[x],max(l,val[x]+1),r);
}
int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n+1)
	{
		scanf("%d%d%d",&val[i],&ls[i],&rs[i]);
		not_root[ls[i]]=not_root[rs[i]]=1;
	}
	int rt=1;
	rep(i,1,n+1) if(!not_root[i]) rt=i;
	rec(rt,0,1e9);
	rep(i,1,n+1) if(mp.find(val[i])==mp.end())
	{
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}
