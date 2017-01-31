#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define pb(x) push_back(x)
#define clr(x,y) memset(x,y,sizeof(x))
#define debug(x) cerr<<#x<<" = "<<x<<endl;
#define dig(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define showtime fprintf(stderr,"time = %.15f\n",clock()/(double)CLOCKS_PER_SEC)
using namespace std;
typedef double db;
typedef long long ll;
template<class Ty>inline void rd(Ty&res)
{
	res=0;char c;
	bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar();
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
const int M=300000;
const db pi=acos(-1.0);
struct comp
{
	db x,y;
	comp(db a,db b):x(a),y(b){}
	comp(){}
	comp operator *(comp &t)
	{
		return comp(x*t.x-y*t.y,t.x*y+t.y*x);
	}
	comp operator +(comp &t)
	{
		return comp(x+t.x,y+t.y);
	}
	comp operator -(comp &t)
	{
		return comp(x-t.x,y-t.y);
	}
};
comp A[M+5],B[M+5];
int rev[M+5];
void DFT(comp *x,int n,int type)
{
	rep(i,0,n) if(i<rev[i]) swap(x[i],x[rev[i]]);
	for(int L=2;L<=n;L<<=1)
	{
		int mid=L>>1;
		comp wn(cos(pi*2/L),sin(pi*2/L*type));
		for(int k=0;k<n;k+=L)
		{
			comp w(1,0);
			for(int i=0;i<mid;i++,w=w*wn)
			{
				comp a=x[k+i],b=x[k+i+mid]*w;
				x[k+i]=a+b;
				x[k+mid+i]=a-b;
			}
		}
	}
}
void FFT(comp *A,comp *B,int n)
{
	rev[0]=0;
	rep(i,1,n)
	{
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=n>>1;
	}
	DFT(A,n,1);DFT(B,n,1);
	rep(i,0,n) A[i]=A[i]*B[i];
	DFT(A,n,-1);
	rep(i,0,n) A[i].x/=n;
}
void output(comp *x,int n)
{
	rep(i,0,n+1) printf("%d ",int(x[i].x+0.5));
}
int main()
{
	int n,m;
	rd(n);rd(m);
	int L=1,x;
	for(;L<=n+m;L<<=1);
	rep(i,0,n+1) rd(x),A[i]=comp(x,0);rep(i,n+1,L) A[i]=comp(0,0);
	rep(i,0,m+1) rd(x),B[i]=comp(x,0);rep(i,m+1,L) B[i]=comp(0,0);
	FFT(A,B,L);
	output(A,n+m);
	return 0;
}
