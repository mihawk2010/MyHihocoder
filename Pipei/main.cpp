#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

vector<vector<int> > graph;
vector<int> tag;
bool c;
int t;
int n, m;
int i;
int u,v;

void explore(int u){
    if (tag[u] == 1){
        for (int v=0; v<graph[u].size(); v++){
            int cur = graph[u][v];
            if (tag[cur] == -1){
                tag[cur] = 2;
                explore(cur);
            }
            else if (tag[cur] == 1){
                c = false;
                return;
            }
        }
    }else if (tag[u] == 2){
         for (int v=0; v<graph[u].size(); v++){
            int cur = graph[u][v];
            if (tag[cur] == -1){
                tag[cur] = 1;
                explore(cur);
            }
            else if (tag[cur] == 2){
                c = false;
                return;
            }
        }
    }
    return;
}

void dfs(){
    c = true;
    for (int i=1; i<=n; i++)
        if (tag[i] == -1){
            tag[i] = 1;
            explore(i);
        }
    if (!c)
        cout<<"Wrong"<<endl;
    else
        cout<<"Correct"<<endl;
}

int main()
{
    cin>>t;
    while (t-- > 0){
        bool c = true;
        cin>>n>>m;
        graph.resize(n+1);
        tag.resize(n+1);
        for (i=0; i<m; i++){
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
       for (i=0; i<=n; i++)
            tag[i] = -1;
       dfs();
       graph.clear();
       tag.clear();
    }

    //cout << "Hello world!" << endl;
    return 0;
}
