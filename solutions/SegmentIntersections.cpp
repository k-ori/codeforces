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

// $ cp-batch SegmentIntersections | diff SegmentIntersections.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SegmentIntersections.cpp && ./a.out

/*

 7/29/2020

 8:57-9:46 RE

 8/3/2020

 9:30-9:50 AC by fixing zero division bug

 https://codeforces.com/blog/entry/80809
 https://twitter.com/hanseilimak/status/1290331053563904001

 https://twitter.com/laycrs/status/1288515164434649088
 https://twitter.com/n_vip/status/1288514780920152066

 */

LL L1,R1,L2,R2,K;
int N;

LL Inf=2e18;
LL solve() {
  if(L1>L2) swap(L1,L2),swap(R1,R2);
  LL res=Inf;

  LL T=K;
  LL cur=max(0LL,min(R1,R2)-max(L1,L2))*N;
  if(cur>=K) return 0;
  T-=cur;

  LL prep=max(0LL,L2-R1);

  REPE(cnt,N) {
    // step 1
    LL cost=prep*cnt;
    LL l1=L1,r1=R1,l2=L2,r2=R2;
    if(prep>0) r1=l2;

    // step 2
    LL maxs=abs(r2-r1)+abs(l2-l1);
    LL t=T;
    LL x=Inf;
    if(maxs>0){
      x=min((LL)cnt,T/maxs);
      cost+=x*maxs;
      t-=x*maxs;
    }

    //dump(cnt,t);
    // step 3
    if(x<cnt) {
      assert(t<=maxs);
      cost+=t;
    } else if(cnt>0) {
      cost+=t*2;
    } else {
      cost=Inf;
    }
    //dump(cnt,prep*cnt,maxs,x,t,cost);
    SMIN(res,cost);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>L1>>R1>>L2>>R2;
    cout<<solve()<<endl;
  }

  return 0;
}
