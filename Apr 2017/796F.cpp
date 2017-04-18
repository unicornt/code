#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define pb(x) push_back(x)
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline void rd(int&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') c=getchar(),flag=true;
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
const int M=300000;
int n,m;
int A[M+5],mark[M+5],B[M+5],mx[M+5],L[M+5],R[M+5];
struct Segment_Tree
{
	int mx[M*4+5],tag[M*4+5];
	void build(int p,int tl,int tr,int x)
	{
		mx[p]=x;
		tag[p]=-1;
		if(tl==tr) return;
		int mid=(tl+tr)>>1;
		build(p<<1,tl,mid,x);
		build(p<<1|1,mid+1,tr,x);
	}
	void up(int p)
	{
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
	}
	void down(int p)
	{
		if(tag[p]!=-1)
		{
			int ls=p<<1,rs=ls|1;
			if(mx[ls]>tag[p])
			{
				tag[ls]=mx[ls]=tag[p];
			}
			if(mx[rs]>tag[p])
			{
				tag[rs]=mx[rs]=tag[p];
			}
			tag[p]=-1;
		}
	}
	void update(int l,int r,int x,int p,int tl,int tr)
	{
//		printf("mx[%d] = %d\n",p,mx[p]);
		if(mx[p]<=x) return;
		if(l==tl&&r==tr)
		{
			mx[p]=tag[p]=x;
			return;
		}
		down(p);
		int mid=(tl+tr)>>1;
		if(r<=mid) update(l,r,x,p<<1,tl,mid);
		else if(l>mid) update(l,r,x,p<<1|1,mid+1,tr);
		else update(l,mid,x,p<<1,tl,mid),update(mid+1,r,x,p<<1|1,mid+1,tr);
		up(p);
	}
	int query(int l,int r,int p,int tl,int tr)
	{
//		printf("mx[%d] = %d\n",p,mx[p]);
		if(l==tl&&r==tr) return mx[p];
		down(p);
		int mid=(tl+tr)>>1;
		if(r<=mid) return query(l,r,p<<1,tl,mid);
		else if(l>mid) return query(l,r,p<<1|1,mid+1,tr);
		else return max(query(l,mid,p<<1,tl,mid),query(mid+1,r,p<<1|1,mid+1,tr));
	}
	void modify(int x,int w,int p,int tl,int tr)
	{
		if(tl==tr)
		{
			mx[p]=w;
			return;
		}
		down(p);
		int mid=(tl+tr)>>1;
		if(x<=mid) modify(x,w,p<<1,tl,mid);
		else modify(x,w,p<<1|1,mid+1,tr);
		up(p);
	}
}sgt1,sgt2;
vector<pii>vec[M+5];
map<int,int>Left;
int main()
{
	rd(n);rd(m);
	rep(i,1,n+1) B[i]=-1,mx[i]=1e9+1;
	int tot=0;
	sgt1.build(1,1,n,1e9);
	sgt2.build(1,1,n,0);
	rep(i,1,m+1)
	{
		int opt,a,b,c;
		rd(opt),rd(a),rd(b);
		if(opt==1)
		{
			rd(c);
			mark[i]=c;
//			rep(j,a,b+1) if(c==A[j]) mark[i]=-1;
			int qry=sgt2.query(a,b,1,1,n);
			if(qry>c)
			{
				puts("NO");
				return 0;
			}
			if(qry==c) mark[i]=-1;
			else Left[c]=n+1,vec[a].pb(pii(b,c));
			if(mark[i]==c) tot|=c;
			L[i]=a,R[i]=b;
//			rep(j,a,b+1) if(A[j]==-1) mx[j]=min(mx[j],c);else if(A[j]>c){puts("NO");return 0;}
			sgt1.update(a,b,c,1,1,n);
		}
		else
		{
			if(mx[a]==1e9+1) mx[a]=sgt1.query(a,a,1,1,n);
			sgt2.modify(a,b,1,1,n);
			mark[i]=-1;
		}
	}
	rep(i,1,n+1) if(mx[i]==1e9+1) mx[i]=sgt1.query(i,i,1,1,n);else sgt1.modify(i,mx[i],1,1,n);
	rep(i,1,m+1)
	{
		if(mark[i]==-1) continue;
		int qrt=sgt1.query(L[i],R[i],1,1,n);
		if(qrt<mark[i])
		{
//			dig("qrt %d %d %d\n",i,qrt,mark[i]);
			puts("NO");
			return 0;
		}
//		rep(j,L[i],R[i]+1)
//		{
//			if(mx[j]==mark[i]) break;
//			if(j==R[i])
//			{
//				puts("NO");
//				return 0;
//			}
//		}
	}
//	rep(i,1,n+1) dig("%d ",mx[i]);
//	dig("\n");
	rep(i,1,n+1)
	{
		rep(j,0,vec[i].size())
		{
//			printf("%d %d\n",vec[i][j].fi,vec[i][j].se);
			Left[vec[i][j].se]=min(Left[vec[i][j].se],vec[i][j].fi);
		}
		if(Left.find(mx[i])!=Left.end()&&Left[mx[i]]>=i&&Left[mx[i]]!=n+1)
		{
			Left[mx[i]]=n+1;
			B[i]=mx[i];
		}
	}
	for(map<int,int>::iterator it=Left.begin();it!=Left.end();++it) if((*it).se!=n+1)
	{
//		dig("illegal %d %d\n",(*it).fi,(*it).se);
		puts("NO");
		return 0;
	}
	rep(i,1,n+1)
	{
		if(B[i]!=-1) continue;
		int tmp=0;
		per(j,0,31)
		{
			if(tmp+(1<<j)<=mx[i]&&!(tot&(1<<j))) tmp+=1<<j;
		}
		B[i]=tmp;
		tot|=tmp;
	}
	dig("tot %d\n",tot);
	puts("YES");
	rep(i,1,n+1) printf("%d ",B[i]);
	puts("");
	return 0;
}
