#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 7/31/2018
 
 24:40-24:51 AC
 
 Editorials:
  - https://atcoder.jp/img/arc074/editorial.pdf
  - https://youtu.be/O2wcqAqGQG8?t=706
  - http://htkb-procon.hateblo.jp/entry/2017/05/21/013035
  - https://kimiyuki.net/writeup/algo/atcoder/arc-074-c/
  - http://kazune-lab.net/contest/2017/05/20/abc062/
  - http://bttb.s1.valueserver.jp/wordpress/blog/2017/05/21/atcoder-beginner-contest-062-c-chocolate-bar/
  - http://hamayanhamayan.hatenablog.jp/entry/2017/05/20/230731
  - http://hamko.hatenadiary.jp/entry/2017/06/29/092932
  - http://nafmo.hatenablog.jp/entry/2017/05/20/224253
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
//LL A[MAX_N];
LL H,W;
const LL Inf=1e11;
LL f() {
  LL res=Inf;
  FOR(h,1,H) {
    LL s1=W*h;
    LL hh=H-h;
    if(hh>1) {
      LL h1=hh/2,h2=hh-h1;
      LL s2=W*h1,s3=W*h2;
      LL x=max({s1,s2,s3})-min({s1,s2,s3});
      SMIN(res,x);
    }
    LL w1=W/2,w2=W-w1;
    LL s2=hh*w1,s3=hh*w2;
    LL x=max({s1,s2,s3})-min({s1,s2,s3});
    SMIN(res,x);
  }
  return res;
}

LL solve() {
  LL res=f();
  swap(H,W);
  SMIN(res,f());
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>H>>W;
  cout<<solve()<<endl;
  
  return 0;
}
