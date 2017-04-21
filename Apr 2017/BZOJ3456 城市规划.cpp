#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef long long ll;
const int M=130000;
const int mod=1004535809; 
const int mod_g=3;
int mod_pow(int x,ll y)
{
	int res=1;
	for(int b=x;y;y>>=1,b=(ll)b*b%mod) if(y&1) res=(ll)res*b%mod;
	return res;
}
int inver(int x){return mod_pow(x,mod-2);}
int n,L;
int fac[M+5],inv_fac[M+5],g[M+5],f[M+5],inv_g[M+5];
int A[M*5+5],B[M*5+5],rev[M*5+5];
void add(int&x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
#define chk(x) assert(0<=(x)&&(x)<mod)
void DFT(int*arr,int type)
{
	rep(i,0,L) if(i<rev[i]) swap(arr[i],arr[rev[i]]);
	for(int i=2;i<=L;i<<=1)
	{
		int mid=i>>1;
		int wn=mod_pow(mod_g,(mod-1)/i);
		if(type==-1) wn=inver(wn);
		for(int j=0;j<L;j+=i)
		{
			for(int k=0,w=1;k<mid;k++,w=(ll)w*wn%mod)
			{
				int a=arr[j+k],b=(ll)arr[j+k+mid]*w%mod;
				add(arr[j+k],b);
				arr[j+k+mid]=(a-b+mod)%mod;
			}
		}
	}
	if(type==-1)
	{
		int inv=inver(L);
		rep(i,0,L) arr[i]=(ll)arr[i]*inv%mod;
	}
}
void NTT(int*A,int*B)
{
	DFT(A,1);DFT(B,1);
	rep(i,0,L) A[i]=(ll)A[i]*B[i]%mod;
	DFT(A,-1);
}
void solve(int sl,int sr)
{
	if(sl==sr)
	{
		f[sl]=(mod-f[sl]+(ll)g[sl]*inv_fac[sl-1])%mod;
		return;
	}
	int mid=(sl+sr)>>1;
	solve(sl,mid);
	int la=mid-sl+1,lb=sr-sl+1;
	for(L=1;L<=la+lb;L<<=1);
	rev[0]=0;
	rep(i,1,L)
	{
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=L>>1;
	}
	rep(i,sl,mid+1) A[i-sl]=f[i];rep(i,la,L) A[i]=0;
	rep(i,sl,sr+1) B[i-sl]=inv_g[i-sl];rep(i,lb,L) B[i]=0;
	NTT(A,B);
	rep(i,mid+1,sr+1) add(f[i],A[i-sl]);
	solve(mid+1,sr);
}
int main()
{
	scanf("%d",&n);
	fac[0]=1;
	inv_fac[0]=1;
	rep(i,1,n+1) fac[i]=(ll)fac[i-1]*i%mod,inv_fac[i]=inver(fac[i]);
	rep(i,1,n+1) g[i]=mod_pow(2,(ll)i*(i-1)/2),inv_g[i]=(ll)g[i]*inv_fac[i]%mod;
	solve(1,n);
	printf("%d\n",(ll)f[n]*fac[n-1]%mod);
	return 0;
}
