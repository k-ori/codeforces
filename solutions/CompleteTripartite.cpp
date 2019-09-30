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

// $ cp-batch CompleteTripartite | diff CompleteTripartite.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CompleteTripartite.cpp && ./a.out

/*
 
 9/29/2019
 
 6:47-7:22 WA
 7:40 WA
 7:48 AC
 
 It's necessary to see if constructed graph is sufficient.
 
 */

const int MAX_N=1e6+1;
VI G[MAX_N];
int N,M;

void nope() {
  println("-1");
  exit(0);
}
void solve() {
  VI col(N,-1);
  REP(c,3) {
    VI col2(N,-1);
    REP(st,N) if(col[st]==-1) {
      col2[st]=c;
      FORR(v,G[st]) if(col2[v]==-1) {
        col2[v]=c+1;
//        dump(st,v,col2[v]);
      }
      REP(i,N) if(col2[i]==-1) col2[i]=c;
//      dumpc(col2);
      if(count(ALL(col2),-1)>0) nope();
      int sameg = count(ALL(col2),c);
      REP(u,N) if(col2[u]==c) {
        if(SZ(G[u])!=N-sameg) nope();
        FORR(v,G[u]) {
          if(col2[v]==c) nope();
        }
      }
      break;
    }
    if(count(ALL(col2),c)==0)nope();
    REP(i,N)if(col2[i]==c) {
      if(col[i]!=-1) nope();
      col[i]=col2[i];
    }
  }
  if(count(ALL(col),-1)>0) nope();
  REP(i,N) printf("%d ",col[i]+1);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  solve();
  
  return 0;
}
