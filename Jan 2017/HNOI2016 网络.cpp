#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<string>
#include<cstdlib>
#include<cassert>
#include<cctype>
#include<bitset>
using namespace std;
#define ll long long
#define pb push_back
#define ull unsigned long long
#define db double
#define vec vector
#define mp make_pair
#define y1 dafgsadifgsd
#define y2 adgijaasdg
#define y0 jafgad
#define is_empty alkdfnadsf
#define hash asdlighasdlf
#define rep(i,s,t) for(int i=(s),_t=(t);i<_t;++i)
#define per(i,s,t) for(int i=(t)-1,_s=(s);i>=_s;--i)
template<class T>inline void rd(T &x){
	x=0;char c;int f=1;
	while(c=getchar(),c<48)if(c=='-')f=-1;
	do x=x*10+(c&15);
	while(c=getchar(),c>47);
	x*=f;
}
template<class T>void prin(T x){
	if(!x)return ;
	prin(x/10);
	putchar(x%10^48);
}
template<class T>void pf(T x){
	if(x<0)putchar('-'),x=-x;
	else if(!x)putchar('0');
	prin(x);
}
template<class T>void ptn(T x){
	pf(x);putchar('\n');
}
template<class T>void ptk(T x){
	pf(x);putchar(' ');
}
template<class T>void Min(T &A,T B){
	if(A>B)A=B;
}
template<class T>void Max(T &A,T B){
	if(A<B)A=B;
}
const int N=(int)1e5+5,M=(int)2e5+5;
struct ss{
	int to,nxt;
}G[M];
struct node{
	int id,tp,x,y,val,lca;
	bool flag;
	bool operator<(const node &A)const{
		if(flag!=A.flag)return flag<A.flag;
		return id<A.id;
	}
}Q[M];
int head[N],sz[N],top[N],son[N],tot,par[N],Lpos[N],Rpos[N],dfn_time,dep[N];
void dfs(int x){
	Lpos[x]=++dfn_time;
	sz[x]=1;
	for(int i=head[x];i;i=G[i].nxt){
		int y=G[i].to;
		if(y!=par[x]){
			par[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(sz[y]>sz[son[x]])son[x]=y;
			sz[x]+=sz[y];
		}
	}
	Rpos[x]=dfn_time;
}
void gettop(int x,int y){
	top[x]=y;
	if(son[x])gettop(son[x],y);
	else return ;
	for(int i=head[x];i;i=G[i].nxt){
		int y=G[i].to;
		if(y!=son[x]&&y!=par[x])gettop(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y])
		if(dep[top[x]]>dep[top[y]])x=par[top[x]];
		else y=par[top[y]];
	if(dep[x]>dep[y])return y;
	return x;
}
int n,m;
int bit[N],f[N],ff;
void add(int x,int v){
	for(;x<=n;x+=x&-x){
		if(f[x]!=ff)f[x]=ff,bit[x]=0;
		bit[x]+=v;
	}
}
int Sum(int x){
	int res=0;
	for(;x;x-=x&-x)
		if(f[x]==ff)res+=bit[x];
	return res;
}
int ans[M];
void solve(int l,int r,int L,int R){
	if(l==r){
		for(int i=L;i<=R;++i)if(Q[i].tp==2)ans[Q[i].y]=l;
		return ;
	}
	++ff;
	int mid=(l+r)>>1,num=0,t=L-1;
	for(int i=L;i<=R;++i){
		if(Q[i].tp==0){
			if(Q[i].val>mid){
				Q[i].flag=1;num++;
				add(Lpos[Q[i].x],1);
				add(Lpos[Q[i].y],1);
				add(Lpos[Q[i].lca],-1);
				if(par[Q[i].lca])add(Lpos[par[Q[i].lca]],-1);
			}else Q[i].flag=0,t++;
		}else if(Q[i].tp==1){
			if(Q[i].val>mid){
				Q[i].flag=1;num--;
				add(Lpos[Q[i].x],-1);
				add(Lpos[Q[i].y],-1);
				add(Lpos[Q[i].lca],1);
				if(par[Q[i].lca])add(Lpos[par[Q[i].lca]],1);
			}else Q[i].flag=0,t++;
		}else {
			int cnt=Sum(Rpos[Q[i].x])-Sum(Lpos[Q[i].x]-1);
			if(cnt<num){
				Q[i].flag=1;
			}else Q[i].flag=0,t++;
		}
	}
	sort(Q+L,Q+R+1);
	if(t>=L)solve(l,mid,L,t);
	if(t<R)solve(mid+1,r,t+1,R);
}
int main(){
//	freopen(".in","r",stdin);
//	freopen("pro.out","w",stdout);
	rd(n);rd(m);
	for(int i=1,x,y;i<n;++i){
		rd(x);rd(y);
		G[++tot]=(ss){y,head[x]};head[x]=tot;
		G[++tot]=(ss){x,head[y]};head[y]=tot;
	}
	dfs(1);
	gettop(1,1);
	tot=0;
	int mx=-(int)1e9;
	for(int i=1,x,y,v,tp;i<=m;++i){
		rd(tp);
		if(tp==0){
			rd(x);rd(y);rd(v);
			Max(mx,v);
			Q[i]=(node){i,tp,x,y,v,LCA(x,y),0};
		}else if(tp==1){
			rd(x);
			Q[i]=Q[x];
			Q[i].tp=1;Q[i].id=i;
		}else if(tp==2){
			rd(x);
			Q[i].id=i;
			Q[i].tp=2;
			Q[i].x=x;
			Q[i].y=tot++;
		}
	}
	solve(0,mx,1,m);
	rep(i,0,tot){
		if(ans[i]==0)ans[i]=-1;
		ptn(ans[i]);
	}
	return 0;
}
