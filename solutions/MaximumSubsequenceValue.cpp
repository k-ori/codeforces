#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch MaximumSubsequenceValue | diff MaximumSubsequenceValue.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaximumSubsequenceValue.cpp && ./a.out

/*

 6/7/2020

 9:30-9:51 WA
 11:30-11:50 AC after bug fix

 https://codeforces.com/blog/entry/78504

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  LL res=0;
  REP(i,N)REP(j,N)REP(k,N) SMAX(res,A[i]|A[j]|A[k]);
  cout<<res<<endl;
}

bool ith(LL x, int i) { return (x>>i)&1; }
void solve_wrong() {
  LL res=0;
  set<int> ks;
  REP(i,N) REP(j,61) if(ith(A[i],j)) ks.emplace(j);
  VI ksks(ALL(ks));
  sort(ALL(ksks)),reverse(ALL(ksks));
  VV<int> xs(min(3,SZ(ksks)));
  REP(i,min(3,SZ(ksks))) REP(j,N) if(ith(A[j],ksks[i])) xs[i].push_back(j);
  REP(i,SZ(xs[0])) {
    LL ans=A[xs[0][i]];
    SMAX(res,ans);
    if(SZ(xs)>=2) REP(j,SZ(xs[1])) {
      ans|=A[xs[1][j]];
      SMAX(res,ans);
      if(SZ(xs)>=3) REP(k,SZ(xs[2])) {
        ans|=A[xs[2][k]];
        SMAX(res,ans);
      }
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
