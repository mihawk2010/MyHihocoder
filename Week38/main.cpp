#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

#define PB push_back
#define MP make_pair

#define REP(i,n) for(i=0;i<(n);++i)
#define FOR(i,l,h) for(i=(l);i<=(h);++i)
#define FORD(i,h,l) for(i=(h);i>=(l);--i)

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;

const int INF = 1<<30;

vector< list<pair<int, int>> > graph;
int dist[10005][10005];

int main()
{
        int n,m,k,t;
        int u,v,w;
        int i,j;
        cin>>n>>m>>k>>t;
        graph.resize(n+1);

        FOR(i,1,m){
                cin>>u>>v>>w;
                graph[u].PB({v, w});
                graph[v].PB({u, w});
        }

        FOR(i,1,n)
            FOR(j,0,k)
                dist[i][j] = INF;
        dist[1][0] = 0;
        FOR(i, 1, k){
            FOR(j, 1, n){
                if (dist[j][i-1] != INF){
                    for (auto it: graph[j]){
                        v = it.first;
                        w = it.second;
                        dist[v][i] = min(dist[v][i],max(dist[j][i-1],w));
                    }
                }
            }
        }
        int ans=INF;
        FOR(i,0,k){
           //cout<<dist[t][i]<<' '<<t<<' '<<i<<endl;
           ans = min(ans, dist[t][i]);
        }
        cout<<ans<<endl;

        return 0;
}

