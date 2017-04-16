#include <bits/stdc++.h>
#define fi first
#define se second
#define pb(x) push_back(x)
#define clr(x,y) memset(x,y,sizeof(x))
#define rep(i,a,n) for(int i=a,i##_END_=n;i<i##_END_;++i)
#define per(i,a,n) for(int i=(n)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
const int mod=1e9+7,INF=0x7fffffff,inf=2e8;//2 yi
const db pi=acos(-1.0),eps=1e-8;
class ConversionMachine
{
	public:
	int n;
	int id[12][12];
	struct Matrix
	{
		int A[145][145];
		Matrix()
		{
			clr(A,0);
		}
	}mat;
	int num;
	Matrix mul(Matrix&x,Matrix&y)
	{
		Matrix z;
		rep(i,0,num+1)
			rep(j,0,num+1)
				rep(k,0,num+1)
					z.A[i][k]=(z.A[i][k]+(ll)x.A[i][j]*y.A[j][k])%mod;
		return z;
	}
	Matrix fast_pow(Matrix&x,int b)
	{
		Matrix bas=x,ret;
		rep(i,0,num+1) ret.A[i][i]=1;
		for(;b;b>>=1,bas=mul(bas,bas)) if(b&1) ret=mul(ret,bas);
		return ret;
	}
	int countAll(string w1, string w2, vector<int> cst, int mc)
	{
		n=w1.size();
		ll tot=0;
		int c1=0,c2=0;
		rep(i,0,n)
		{
			if(w1[i]=='a')
			{
				if(w2[i]=='b') c1++,tot+=cst[0];
				if(w2[i]=='c') c2++,tot+=cst[0]+cst[1];
			}
			else if(w1[i]=='b')
			{
				if(w2[i]=='c') c1++,tot+=cst[1];
				if(w2[i]=='a') c2++,tot+=cst[1]+cst[2];
			}
			else
			{
				if(w2[i]=='a') c1++,tot+=cst[2];
				if(w2[i]=='b') c2++,tot+=cst[2]+cst[0];
			}
		}
		if(mc<tot) return 0;
		int cnt=c1+c2*2+(mc-tot)/(cst[0]+cst[1]+cst[2])*3;
		num=0;
		rep(i,0,n+1)rep(j,0,n-i+1) id[i][j]=num++;
		rep(i,0,n+1)rep(j,0,n-i+1)
		{
			if(i>0) mat.A[id[i][j]][id[i-1][j]]=i;
			if(n-i-j>0) mat.A[id[i][j]][id[i][j+1]]=n-i-j;
			if(j>0) mat.A[id[i][j]][id[i+1][j-1]]=j;
		}
		mat.A[id[0][0]][num]=1;
		mat.A[num][num]=1;
		mat=fast_pow(mat,cnt+1);
		return mat.A[id[c1][c2]][num];
	}
};
