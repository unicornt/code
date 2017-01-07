#include <cstdio>
#include <cassert>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define showtime fprintf(stderr,"time = %.15f\n",clock() / (double)CLOCKS_PER_SEC)
using namespace std;
#define debug(x) cout<<#x<<" = "<<x<<endl
const int M=1005;
const int mod=1e9+7;
typedef long long ll;
int n,dp[M],c[M][M],C[M][M],H[M],fac[M];
int fast_pow(int x,int b)
{
	int res=1,bas=x;
	for(;b;b>>=1,bas=(ll)bas*bas%mod) if(b&1) res=(ll)res*bas%mod;
	return res;
}
int inver(int x){return fast_pow(x,mod-2);}
int inv[M];
void prepare()
{
	fac[0]=1;
	rep(i,1,1001) fac[i]=(ll)fac[i-1]*i%mod;
	rep(i,0,1001) fac[i]=inver(fac[i]);
	memset(c,-1,sizeof(c));
	rep(i,1,n+1) inv[i]=inver(i);
	rep(i,0,1001)
		rep(j,0,1001)
		{
			if(j==0||i==j) C[j][i]=1;
			else C[j][i]=(C[j-1][i-1]+C[j][i-1])%mod;
		}
}
void add(int &x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
int A[M],B[M],sum[M][M],E[M][M];
int Calc(int m,int ni)
{
	if(c[m][ni]!=-1) return c[m][ni];
	int&res=c[m][ni],nn=H[ni+1]-H[ni];
	if(res!=-1) return res;
	if(m>nn) return res=0;
	res=1;
	rep(i,nn-m+1,nn+1) res=(ll)res*i%mod;
	res=(ll)res*inver(fac[m])%mod;
	return res;
}
int main()
{
	scanf("%d",&n);
	prepare();
	int tot=0;
	rep(i,1,n+1)
	{
		scanf("%d%d",&A[i],&B[i]);
		H[tot++]=A[i];
		H[tot++]=B[i]+1;
	}
	H[tot++]=0;
	H[tot++]=1;
	sort(H,H+tot);
	tot=unique(H,H+tot)-H;
	rep(i,1,n+1)
	{
		A[i]=lower_bound(H,H+tot,A[i])-H;
		B[i]=lower_bound(H,H+tot,B[i]+1)-H;
//		printf("interval %d %d\n",A[i],B[i]);
	}
	//[A_i,B_i)
	//dp[i][j]±íÊ¾µ±Ç°´¦Àíµ½µÚiËùÊ±£¬´¬µÄÊýÁ¿¡Ê[C_i,C_{i+1}) µÄ·½°¸ÊýÁ¿
	dp[0]=1;
	rep(i,0,tot) sum[0][i]=1;
	int ans=0;
	rep(j,0,tot-1)
	{
		c[0][j]=1;
		int t=H[j+1]-H[j];
		rep(i,1,n+2) c[i][j]=(ll)c[i-1][j]*inv[i]%mod*(t-i+1)%mod;
	}
	showtime;
	rep(w,0,tot-1)
	{
		int cnt=0;
		rep(i,1,n+1) if(w>=A[i]&&w<B[i]) cnt++;
		rep(i,0,cnt+1)
		{
			//µ±cntµÈÓÚiÊ± 
			int&r=E[i][w];
			rep(j,0,i+1) r=(r+C[j][i]*(ll)c[j+1][w])%mod;
		}
	}
	showtime;
	rep(i,1,n+1)
	{
		rep(w,A[i],B[i])
		{
			int cnt=0,&res=dp[w];//¿ÉÄÜºÍµ±Ç°Ñ§Ð£´¬ÊýÔÚÍ¬Ò»Çø¼äµÄ 
			per(j,0,i)
			{//´Ój×ªÒÆµ½i²¢ÇÒi,jÁ½ËùÑ§Ð£µÄ´¬ÊýÁ¿²»Í¬Çø¼ä 
				//¿¼ÂÇÖÐ¼äÓÐÑ§Ð£´¬µÄÊýÁ¿ÏàÍ¬Çø¼äµÄÇé¿ö
//				dp[i][w]=(ll)sum[j][w-1]*(H[w+1]-H[w])%mod;
				res=(res+(ll)E[cnt][w]*sum[j][w-1])%mod;
//				rep(k,0,cnt+1)
//				{//´¬ÊýÁ¿ÏàÍ¬Çø¼äµÄÑ§Ð£¸öÊý(²»°üº¬i)
//					dp[i][w]=(dp[i][w]+(ll)sum[j][w-1]*C[k][cnt]%mod*Calc(k+1,w))%mod;
////					printf("C[%d][%d] = %d    Calc(%d,%d)  =  %d\n",k,cnt,C[k][cnt],k+1,H[w+1]-H[w],Calc(k+1,w));
//				}
				if(A[j]<=w&&B[j]>w) ++cnt;
			}
		}
//		puts("");
//		rep(w,A[i],B[i]) printf("%d ",dp[i][w]);
//		puts("\n");
		rep(w,1,tot) add(sum[i][w]=sum[i][w-1],dp[w]),dp[w]=0;
		add(ans,sum[i][tot-1]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
4
1 3
4 5
6 10
12 13

4
1 5
1 5
1 5
1 5
*/
