#include <iostream>
#include <vector>

using namespace std;

vector<vector <int> > g;

int main()
{
    int t, i, n, j;
    int counter=0;

    scanf("%d", &t);
    while (counter++ < t){
        scanf("%d", &n);
        g.resize(n+1);
        for (i=0; i<n; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (i=0; i<n; i++)
            if (g[i]


        printf("Case #%d: %d\n", counter, MaxMatch());
        g.clear();
    }

    return 0;
}
