#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
int k;
template<class Ty>
struct Vector
{
	Ty *arr;
	void resize(int n,Ty c)
	{
		arr=new Ty[n];
		rep(i,0,n) arr[i]=c;
	}
	inline Ty &operator[](int x)
	{
		return arr[x];
	}
};
int num[100005];
Vector<char>null;
struct Matrix
{
	int r,c;
	Vector<Vector<char> >mat;//mat[r][c]
	inline void resiz(int _r,int _c,int v)
	{
		r=_r,c=_c;
		mat.resize(r,null);
		rep(i,0,r)
			mat[i].resize(c,v);
	}
}A,B,C,D,X,tmp;
void Multi(Matrix&ret,Matrix&a,Matrix&b)
{
	rep(i,0,a.r)rep(j,0,b.c)
	{
		int x=0;
		rep(w,0,a.c)
			x+=a.mat[i][w]*b.mat[w][j];
		ret.mat[i][j]=x%k;
	}
}
int n,d;
void solve()
{
	X.resiz(n,1,0);
	tmp.resiz(d,1,0);
	C.resiz(n,1,0);
	rep(ttt,0,8)
	{
		int tt=0;
		rep(i,0,n)
		{
			if(n<10000) X.mat[i][0]=(rand()&31)<31?1:0;
			else X.mat[i][0]=1;
			tt+=X.mat[i][0];
		}
		tt%=k;
		Multi(tmp,B,X);
		Multi(C,A,tmp);
		rep(i,0,n)
		{
			if((C.mat[i][0]+num[i]*X.mat[i][0])%k!=tt)
			{
				rep(j,0,n)
				{
					if(i==j) continue;
					int res=0,upp=0;
					rep(w,0,d)
						res=res+A.mat[i][w]*A.mat[j][w];
					if(res%k==0)
					{
						int a=min(i,j);
						int b=max(i,j);
						printf("%d %d\n",a+1,b+1);
						exit(0);
					}
				}
				assert(false);
			}
		}
		if(n>=10000) break;
	}
	puts("-1 -1");
}
Vector<Vector<char> >E;
template<class Ty>
inline void rd(Ty&x)
{
	x=0;char c;
	while(c=getchar(),c<'0');
	do x=x*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
}
int main()
{
	scanf("%d%d%d",&n,&d,&k);
	E.resize(n,null);
	rep(i,0,n) E[i].resize(d,0);
	rep(i,0,n)
	{
		int ret=0;
		rep(j,0,d)
		{
			int x;
			rd(x);
			x%=k;
			E[i][j]=x;
			ret+=x*x;
		}
		if(k==3) ret*=ret;
		num[i]=ret%k;
		num[i]=!num[i];
	}
	//A*B*X=C*X
	if(k==2)
	{
		A.resiz(n,d,0);
		B.resiz(d,n,0);
		rep(i,0,n) rep(j,0,d) A.mat[i][j]=B.mat[j][i]=E[i][j];
		D.resiz(d,1,1);
		solve();
	}
	else
	{
		A.resiz(n,d*d,0);
		B.resiz(d*d,n,0);
		rep(i,0,n) rep(j,0,d) rep(w,0,d) A.mat[i][j*d+w]=B.mat[j*d+w][i]=E[i][j]*E[i][w];
		d=d*d;
		D.resiz(d,1,1);
		solve();
	}
	return 0;
}
