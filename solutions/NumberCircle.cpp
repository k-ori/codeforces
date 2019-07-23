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

// $ cp-batch NumberCircle | diff NumberCircle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NumberCircle.cpp && ./a.out

/*
 
 7/5/2019
 
 Sort and look at the largest
 YES <=> A[N-1] >= A[N-2]+A[N-3]
 
 8:11-8:26 AC
 
 https://codeforces.com/blog/entry/68079
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  sort(A,A+N);
  swap(A[N-1],A[N-2]);
  bool ok=true;
  REP(i,N) {
    int l=(N+i-1)%N,r=(i+1)%N;
    ok&=A[l]+A[r]>A[i];
  }
  if(ok) {
    println("YES");
    REP(i,N) printf("%lld ", A[i]);
    println("");
  } else {
    println("NO");
  }
}

void test() {
  N=4;
  VI A={1,2,3,4};
  do {
    bool ok=true;
    REP(i,N) {
      int l=(N+i-1)%N,r=(i+1)%N;
      ok&=A[l]+A[r]>A[i];
    }
    if(ok)dumpc(A);
  } while(next_permutation(ALL(A)));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}