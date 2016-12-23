#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef double db;
const int M=50;
const db eps=1e-8;
db A[M][M],x[M];
int n,m,id[M];
void ret(int x)
{
	if(x) puts("Unbounded");
	else puts("Infeasible");
	exit(0);
}
void pivot(int l,int e)
{
	swap(id[n+l],id[e]);;
	db tmp=-A[l][e];
	A[l][e]=-1;
	rep(i,0,n+1) A[l][i]/=tmp;
	rep(i,0,m+1)
		if(i!=l)
		{
			tmp=A[i][e];
			A[i][e]=0;
			rep(j,0,n+1) A[i][j]+=tmp*A[l][j];
		}
}
db simplex()
{
	rep(i,0,n+m) id[i]=i;
	while(true)
	{
		db mi=-eps;
		int l=-1,e=-1;
		rep(i,0,m)
			if(A[i][n]<mi) mi=A[l=i][n];
		if(l==-1) break;
		rep(i,0,n) if(A[l][i]>eps)
		{
			e=i;
			if(rand()&1) break;
		}
		if(e==-1) ret(0);
		pivot(l,e);
	}
	while(true)
	{
		db mx=eps;
		int l=-1,e=-1;
		rep(i,0,n)
			if(A[m][i]>mx) mx=A[m][e=i];
		if(e==-1) break;
		db mi=1e30;
		rep(i,0,m) if(A[i][e]<-eps)
		{
			db tmp=-A[i][n]/A[i][e];
			if(tmp<mi) mi=tmp,l=i;
		}
		if(l==-1) ret(1);
		pivot(l,e);
	}
	return A[m][n];
}
int main()
{
	srand(time(NULL));
	int t;
	scanf("%d%d%d",&n,&m,&t);
	rep(i,0,n) scanf("%lf",&A[m][i]);
	A[m][n]=0;
	rep(i,0,m)
	{
		rep(j,0,n)
		{
			scanf("%lf",&A[i][j]);
			A[i][j]=-A[i][j];
		}
		scanf("%lf",&A[i][n]);
	}
	printf("%lf\n",simplex());
	if(t)
	{
		rep(i,0,n) x[id[i]]=0;
		rep(i,0,m) x[id[n+i]]=A[i][n];
		rep(i,0,n) printf("%.10lf ",x[i]);
		puts("");
	}
	return 0;
}
