#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <ctime>
#include "cv.h"

using namespace std;
using namespace cv;

#define ll long long
#define ios ios_base::sync_with_stdio(false)
#define fcin freopen("stdin.input","r",stdin)
#define fcout freopen("out.txt","w",stdout)
#define rep(i,n) for(unsigned i=0;i<n;i++)
#define reep(i,a,b) for(unsigned i=a;i<=b;i++)
#define per(i,n) for(unsigned i=0;i>n;i--)
#define peer(i,a,b) for(unsigned i=a;i>=b;i--)
#define vec vector
#define pb push_back

#include "Net.h"

int main()
{
    fcin;
    fcout;
    srand(time(NULL));
    // e.g., { 3, 2, 1 }
    vec<unsigned> topology;
    unsigned t;cin>>t;topology.pb(t);
    cin>>t;topology.pb(t);
    cin>>t;topology.pb(t);

    Net myNet(topology);

    unsigned T;cin>>T;

    rep(i,T)
    {
        vec<double> inVals;
        double t;cin>>t;cout<<t<<" ";
        inVals.pb(t/1000);
        cin>>t;cout<<t<<endl;
        inVals.pb(t/1000);
        myNet.feedForward(inVals);
        vec<double> res;
        myNet.getResults(res);
        cout<<res[0]*2000<<" ";
        vec<double> tar;cin>>t;cout<<t<<endl;
        tar.pb(t/2000);
        myNet.backProp(tar);
    }
}

