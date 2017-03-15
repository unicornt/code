#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#define clr(x,y) memset(x,y,sizeof(x))
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
int n;
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
struct node
{
	node*ch[26];
	int siz;
	node(){siz=-1;clr(ch,0);}
}*tree[M+5];
int siz[M+5];
void dfs(node* x)
{
	x->siz=1;
	rep(i,0,26)
	{
		if(x->ch[i]!=NULL)
		{
			dfs(x->ch[i]);
			x->siz+=x->ch[i]->siz;
		}
	}
}
int sz;
void dfs_add(node*x,node*y)
{
	rep(i,0,26)
	{
		if(y->ch[i]!=NULL)
		{
			if(x->ch[i]==NULL) x->ch[i]=new node(),++sz;
			dfs_add(x->ch[i],y->ch[i]);
		}
	}
}
void dfs_minus(node*x,node*y)
{
	rep(i,0,26)
	{
		if(y->ch[i]!=NULL)
		{
			if(x->ch[i]!=NULL)
			{
				if(x->ch[i]->siz==-1)
				{
					delete x->ch[i];
					x->ch[i]=NULL;
				}
				else dfs_minus(x->ch[i],y->ch[i]);
			}
		}
		/*if(x->ch[i]!=NULL)
		{
			if(x->ch[i]->siz==-1)
			{
				delete x->ch[i];
				x->ch[i]=NULL;
			}
			else dfs_minus(x->ch[i],y);
		}*/
	}
}
int res[M+5];
void rec(node* x,int dep)
{
	rep(i,0,26) if(x->ch[i]!=NULL) rec(x->ch[i],dep+1);
	int mxson=-1;
	rep(i,0,26)if(x->ch[i]!=NULL)
		if(mxson==-1||x->ch[i]->siz>x->ch[mxson]->siz) mxson=i;
	if(~mxson)
	{
		res[dep]++;
		sz=0;
		rep(i,0,26)if(x->ch[i]!=NULL&&i!=mxson)
			dfs_add(x->ch[mxson],x->ch[i]);
		res[dep]+=x->siz-x->ch[mxson]->siz-1-sz;
		rep(i,0,26)if(x->ch[i]!=NULL&&i!=mxson)
			dfs_minus(x->ch[mxson],x->ch[i]);
	}
}
int main()
{
	rd(n);
	rep(i,1,n+1) tree[i]=new node();
	rep(i,1,n)
	{
		int a,b;char c;
		rd(a);rd(b);
		scanf("%c",&c);
		tree[a]->ch[c-'a']=tree[b];
	}
	dfs(tree[1]);
	rec(tree[1],0);
	int ans=0;
	rep(i,0,n) dig("%d ",res[i]);
	dig("\n");
	rep(i,0,n) if(res[i]>res[ans]) ans=i;
	printf("%d\n%d\n",n-res[ans],ans+1);
	return 0;
}
