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
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

const int MOD=1e9+7;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

// $ ../batch MakotoAndABlackboard | diff MakotoAndABlackboard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MakotoAndABlackboard.cpp && ./a.out

/*
 
 1/8/2019
 
 9:03-10:03 give up
 16:30-17:10 Ok. Prime factorization...
 17:30-18:22 Ok. Independence of events. Implemented and Codeforces got down 👎
 18:35 got AC after 2WA (overflow, TLE due to too large max exponent)
 
 My approaches
 - monotone: divisor(v)<=v
 - HCN(v)<=3e4
 => dp?
 - prime factorization (11 dimensions, 50 exponents)
 - formula transformation
 
 Choice of exponents of prime factors is independent choice
 => E[p1^e1*p2^e2*..*pk^ek] = E[p1^e1] * E[p2^e2] * ... * E[p3^e3]
 
 Hmmmm this is hard to notice... 😞
 Now we can solve independent problems of prime factors based on below recurrence relation.
 
 E[p^e,k] = ∑ { E[p^i,k-1] : i=0..e }
 E[p^e,0] = p^e
 
 Key:
  - dp
  - Independence of expectation on prime exponent
 
 Summary:
  - Beautiful problem to decompose by prime factors 👍
  - Try to leverage 
 
 */

int K;
LL N;

const int MAX_K=1e4+10;
const int MAX_E=1e2+10;

ModInt dp[MAX_K][MAX_E];
ModInt f(LL p, int e) {
  int E=e+10;
  REP(i,MAX_K)REP(j,E) dp[i][j]=ModInt(0);
  REP(i,E) dp[0][i]=ModInt(p).pow(i);
  
  FORE(k,1,K) {
    ModInt cum[E]; cum[0]=ModInt(0);
    REP(e,E-1) cum[e+1]=cum[e]+dp[k-1][e];
    REP(e,E-1) dp[k][e]+=cum[e+1]/ModInt(e+1);
  }
  return dp[K][e];
}

void solve() {
  ModInt res(1);
  for(LL p=2; p*p<=N; ++p) if(N%p==0) {
    int cnt=0;
    while(N%p==0) ++cnt,N/=p;
    
    ModInt a=f(p,cnt);
//    dump3(p,cnt,a.val);
    res*=a;
  }
  if(N>1) {
    ModInt a=f(N,1);
//    dump3(N,1,a);
    res*=a;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  solve();
  
  return 0;
}
