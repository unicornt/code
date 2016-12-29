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
#define pq priority_queue
#define pb(x) push_back(x)
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
const int M=100005;
char opt[M];
vector<int>edge[M],son[M];
vector<pii>query[M];
int len,m,id[M],n,pre[M],ch[M][26],allc,fail[M];
void build_Trie()
{
    int cur=allc=0;
    n=0;
    rep(i,0,len)
    {
        if(opt[i]=='P') id[++n]=cur;
        else if(opt[i]=='B') cur=pre[cur];
        else
        {
            int c=opt[i]-'a';
            if(ch[cur][c]==0)
            {
                ch[cur][c]=++allc;
                pre[allc]=cur;
                son[cur].pb(allc);
            }
            cur=ch[cur][c];
        }
    }
}
int que[M];
void build_AC()
{
    int L=0,R=0;
    rep(i,0,26) if(ch[0][i])
        que[R++]=ch[0][i];
    while(L<R)
    {
        int cur=que[L++];
        rep(i,0,26)
        {
            if(!ch[cur][i]) ch[cur][i]=ch[fail[cur]][i];
            else
            {
                int to=ch[cur][i];
                fail[to]=ch[fail[cur]][i];
                que[R++]=to;
            }
        }
    }
}
int L[M],R[M],dfs_clock=0;
void dfs(int x)
{
    L[x]=++dfs_clock;
    rep(i,0,edge[x].size())
        dfs(edge[x][i]);
    R[x]=dfs_clock;
}
int ans[M];
int bit[M];
void add(int x,int w)
{
    while(x<=dfs_clock)
    {
        bit[x]+=w;
        x+=lowbit(x);
    }
}
int sum(int x)
{
    int res=0;
    while(x>0)
    {
        res+=bit[x];
        x-=lowbit(x);
    }
    return res;
}
void dfs_solve(int x)
{
    add(L[x],1);
//  printf("add %d\n",L[x]);
    rep(i,0,query[x].size())
    {
        int b=query[x][i].fi;
//      printf("query(%d)     %d %d\n",L[x],L[b],R[b]);
        ans[query[x][i].se]=sum(R[b])-sum(L[b]-1);
    }
    rep(i,0,son[x].size())
        dfs_solve(son[x][i]);
    add(L[x],-1);
//  printf("del %d\n",L[x]);
}
void solve()
{
    build_Trie();
    build_AC();
    scanf("%d",&m);
    rep(i,0,m)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        query[id[b]].pb(pii(id[a],i));
    }
//  debug(allc);
    rep(i,1,allc+1) edge[fail[i]].pb(i);
    dfs(0);
    dfs_solve(0);
    rep(i,0,m)
        printf("%d\n",ans[i]);
}
int main()
{
    scanf("%s",opt);
    len=strlen(opt);
    solve();
    return 0;
}
