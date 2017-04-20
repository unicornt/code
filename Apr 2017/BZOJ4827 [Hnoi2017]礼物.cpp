#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef long long ll;
const int mod=998244353;//7*17*2^23+1
const int mod_g=3;
const int M=500000;
int n,m,L;
int A[M+5],B[M+5];
int mod_pow(int x,int y)
{
	int res=1;
	for(int b=x;y;y>>=1,b=(ll)b*b%mod) if(y&1) res=(ll)res*b%mod;
	return res;
}
int inv(int x){return mod_pow(x,mod-2);}
int rev[M+5];
void DFT(int*A,int type)
{
	rep(i,0,L) if(i<rev[i]) swap(A[i],A[rev[i]]);
	for(int i=2;i<=L;i<<=1)
	{
		int mid=i>>1;
		int wn=mod_pow(mod_g,(mod-1)/i);
		if(type==-1) wn=inv(wn);
		for(int j=0;j<L;j+=i)
		{
			for(int k=0,w=1;k<mid;k++,w=(ll)w*wn%mod)
			{
				int a=A[j+k],b=(ll)w*A[j+k+mid]%mod;
				A[j+k]=(a+b)%mod;
				A[j+k+mid]=(a-b+mod)%mod; 
			}
		}
	}
	if(type==-1)
	{
		int inver=inv(L);
		rep(i,0,L) A[i]=(ll)A[i]*inver%mod;
	}
}
void NTT(int*A,int*B)
{
	DFT(A,1);DFT(B,1);
	rep(i,0,L) A[i]=(ll)A[i]*B[i]%mod;
	DFT(A,-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	int dlt=0;
	rep(i,0,n) scanf("%d",&A[i]),dlt+=A[i];
	rep(i,0,n) scanf("%d",&B[i]),dlt-=B[i];
	int ans=0x7fffffff;
	rep(c,-m,m+1)
	{
		ans=min(ans,n*c*c+2*c*dlt);
	}
	rep(i,0,n) ans+=A[i]*A[i]+B[i]*B[i];
	reverse(A,A+n);
//	rep(i,0,n)
//	{
//		swap(A[n-1-i],A[i]);
//		if(n-i-1<=i) break;
//	}
	per(i,0,n) B[n-1+i]=B[i],B[i]=0;
	for(L=1;L<=n*4;L<<=1);
	rev[0]=0;
	rep(i,1,L)
	{
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=L>>1;
	}
//	rep(i,0,n) printf("%d ",A[i]);
//	puts("");
//	DFT(B,1);
//	DFT(B,-1);
//	rep(i,0,n) printf("%d ",A[i]);
//	puts("");
	NTT(A,B);
	rep(i,n,L) A[i%n]+=A[i];
	int mx=0;
	rep(i,0,n) mx=max(mx,A[i]);
//	printf("%d %d\n",ans,mx);
	printf("%d\n",ans-2*mx);
	return 0;
}
