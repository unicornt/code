#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define x first
#define y second
using namespace std;
typedef pair<double,double> node;
const int M=10005;
double X,Y;
node p[M];
double Rnd(){return rand()%10000/10000.0;}
void legal(node&a)
{
	if(a.x<0) a.x=0;
	if(a.x>X) a.x=X;
	if(a.y<0) a.y=0;
	if(a.y>Y) a.y=Y;
}
double sqr(double x){return x*x;}
double dis(node a,node b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
int n;
double calc(node a)
{
	double res=1e300;
	rep(i,0,n) res=min(res,dis(a,p[i]));
	return res;
}
node get_node(node a,double t)
{
	node ret;
	double res=-1;
	rep(i,0,80)
	{
		node w=node(a.x+t*(Rnd()*2-1),a.y+t*(Rnd()*2-1));
		legal(w);
		double tmp=calc(w);
		if(tmp>res)
		{
			res=tmp;
			ret=w;
		}
	}
	return ret;
}
int main()
{
	srand(233);
	int T;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%lf%lf%d",&X,&Y,&n);
		rep(i,0,n) scanf("%lf%lf",&p[i].x,&p[i].y);
		node now=p[0],ans=now;
//		printf("%f %f\n",calc(node(0,0)),calc(node(50,50)));
		double nans,res;
		nans=res=calc(now);
		double t=1e10;
		while(t>0.01)
		{
			node ton=get_node(now,t);
			double tans=calc(ton);
			double delta=tans-nans;
			if(tans>res) res=tans,ans=ton;
			if(delta>=0||exp(delta/t)>=Rnd())
			{
				now=ton;
				nans=tans;
			}
			t*=0.95;
		}
		printf("The safest point is (%.1f, %.1f).\n",ans.x,ans.y);
	}
	return 0;
} 
