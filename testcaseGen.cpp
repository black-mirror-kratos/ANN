#include <iostream>
#include <ctime>
using namespace std;
#define ll long long
#define ios ios_base::sync_with_stdio(false)
#define fcin freopen("stdin.input","r",stdin)
#define fcout freopen("stdin.input","w",stdout)
#define rep(i,n) for(ll i=0;i<n;i++)
#define vec vector
#define pb push_back
#define pp pair<ll,ll>
#define mp make_pair
#define mt make_tuple
#define precisionfixed std::cout << std::fixed;std::cout.precision(3)
#define bp __builtin_popcount
#define MOD 1000000007

int R()
{
	double t = rand() / double(RAND_MAX);
	int tt = t*1000;
	return tt;
}

 int main()
{
	ios;
	//fcin;
	fcout;
	//precisionfixed;
	srand(time(NULL));
	/* code */
	cout<<2<<" "<<1<<" "<<1<<endl;
	cout<<10000<<endl;
	rep(i,10000)
	{
		int a = R();
		int b = R();
		int c = a + b;
		cout<<a<<" "<<b<<endl;
		cout<<c<<endl;
	}
	return 0;
}