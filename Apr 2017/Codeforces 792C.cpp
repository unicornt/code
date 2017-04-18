#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=a,i##_END_=b;i<i##_END_;++i)
#define per(i,a,b) for(int i=(b)-1,i##_BEGIN_=a;i>=i##_BEGIN_;--i)
#define pb(x) push_back(x)
#define dig(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
inline void rd(int&res)
{
	res=0;char c;bool flag=false;
	while(c=getchar(),c!='-'&&(c<'0'||c>'9'));
	if(c=='-') flag=true,c=getchar();
	do res=res*10+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	if(flag) res=-res;
}
const int M=100000;
const int INF=0x7fffffff;
string a,b,c;
int val(string s)
{
	int ret=0;
	rep(i,0,s.length()) ret+=s[i]-'0';
	return ret%3;
}
void work(string&s)
{
	while(s[0]=='0'&&s.length()>1) s.erase(0,1);
}
int main()
{
	cin>>a;
	int sa=val(a),sb=3-sa;
	if(sa==0)
	{
		work(a);
		cout<<a<<endl;
		return 0;
	}
	b=c=a;
	int cnt1=1,cnt2=2;
	per(i,0,a.length())
	{
		if((a[i]-'0')%3==sa&&cnt1) cnt1--,b.erase(i,1);
		if((a[i]-'0')%3==sb&&cnt2) cnt2--,c.erase(i,1);
	}
	work(b);
	work(c);
	if(cnt1) b="";
	if(cnt2) c="";
	if((val(b)&&val(c))||(b.length()==0&&c.length()==0)) puts("-1");
	else cout<<(b.length()>c.length()?b:c)<<endl;
	return 0;
}
