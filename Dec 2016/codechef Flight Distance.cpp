#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
const int M=70;
typedef long long ll;
typedef double frac;
const frac eps=1e-8;
int id[M][M];
int mat[M*M][M*M];
void Ass(int x)
{
	if(!x) while(true);
}
frac A[M*M][M*M];
void pivot(int l,int e,int n,int m)
{
	frac tmp=-A[l][e];
	A[l][e]=-1;
	rep(i,0,n+1) A[l][i]=A[l][i]/tmp;
	rep(i,0,m+1)
		if(i!=l)
		{
			tmp=A[i][e];
			A[i][e]=0;
			rep(j,0,n+1) A[i][j]=A[i][j]+tmp*A[l][j];
		}
}
frac simplex(int n,int m)
{
	while(true)
	{
		int l=-1,e=-1;
		frac mx=eps;
		rep(i,0,n)
			if(A[m][i]>mx) mx=A[m][e=i];
		if(e==-1) break;
		frac mi;
		mi=1e30;
		rep(i,0,m)
			if(A[i][e]<-eps)
			{
				frac tmp=-A[i][n]/A[i][e];
				if(tmp<mi)
				{
					mi=tmp;
					l=i;
				}
			}
		Ass(l!=-1);
		pivot(l,e,n,m);
	}
	return A[m][n];
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int sz=0;
	rep(i,0,n) rep(j,i+1,n)
		id[j][i]=id[i][j]=sz++;
	//sz=n*(n-1)/2
	//[0,sz)   d_{uv}
	//[sz,sz*2)  t^+_{uv}
	//[sz*2,sz*3)  t^-_{uv}
	Ass(sz==n*(n-1)/2);
	int t=0;
	memset(mat,0,sizeof(mat));
	rep(i,0,m)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		int iduv=id[u][v];
		mat[t][iduv]=-1;
		mat[t][iduv+sz]=1;
		mat[t][iduv+(sz<<1)]=-1;
		mat[t++][sz*3]=w;
		mat[t][iduv]=1;
		mat[t][iduv+sz]=-1;
		mat[t][iduv+(sz<<1)]=1;
		mat[t++][sz*3]=-w;
		rep(j,0,n)
		{
			if(j!=v&&j!=u)
			{
				mat[t][iduv+sz]=-1;
				mat[t][iduv+(sz<<1)]=1;
				mat[t][id[v][j]]=-1;
				mat[t][id[u][j]]=1;
				mat[t++][sz*3]=-w;
				mat[t][iduv+sz]=-1;
				mat[t][iduv+(sz<<1)]=1;
				mat[t][id[u][j]]=-1;
				mat[t][id[v][j]]=1;
				mat[t++][sz*3]=-w;
			}
		}
	}
	rep(i,sz,sz*3) mat[t][i]=1;
	rep(i,0,t+1) rep(j,0,sz*3+1) A[j][i]=mat[i][j];
	frac ans=simplex(t,sz*3);
	for(int i=1;;i++)
	{
		if(ans*i-int(ans*i+eps)<eps)
		{
			printf("%d/%d\n",int(ans*i+eps),i);
			return 0;
		}
	}
	return 0;
}
