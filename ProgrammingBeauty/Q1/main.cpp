#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN=1100;
const int INF=1<<28;
int g[MAXN][MAXN],Mx[MAXN],My[MAXN],Nx,Ny;
int dx[MAXN],dy[MAXN],dis;
int num[MAXN];
bool vst[MAXN];

bool searchP()
{
    queue<int>Q;
    dis=INF;

    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for(int i=0;i<Nx;i++)
        if(Mx[i]==-1)
        {
            Q.push(i);
            dx[i]=0;
        }
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        if(dx[u]>dis)  break;
        for(int v=0;v<Ny;v++)
            if(g[u][v]&&dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if(My[v]==-1)  dis=dy[v];
                else
                {
                    dx[My[v]]=dy[v]+1;
                    Q.push(My[v]);
                }
            }
    }
    return dis!=INF;
}

bool DFS(int u)
{
    for(int v=0;v<Ny;v++)
       if(!vst[v]&&g[u][v]&&dy[v]==dx[u]+1)
       {
           vst[v]=1;
           if(My[v]!=-1&&dy[v]==dis) continue;
           if(My[v]==-1||DFS(My[v]))
           {
               My[v]=u;
               Mx[u]=v;
               return 1;
           }
       }
    return 0;
}

int MaxMatch()
{
    int res=0;
    memset(Mx,-1,sizeof(Mx));
    memset(My,-1,sizeof(My));
    while(searchP())
    {
        memset(vst,0,sizeof(vst));
        for(int i=0;i<Nx;i++)
          if(Mx[i]==-1&&DFS(i))  res++;
    }
    return res;
}

bool isprime(int n)
{
    if(n<2)
        return false;
    for (int i=2;i*i<=n;i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}

bool prime_related(int i, int j){
    int a, b;
    a = max(i, j);
    b = min(i, j);
    if (isprime(a / b) && (a % b ==0))
        return true;
    return false;
}

int main(){
    int t, i, n, j;
    int counter=0;

    scanf("%d", &t);
    while (counter++ < t){
        scanf("%d", &n);
        scanf("%d", &num[0]);
        for (i=1; i<n; i++){
            scanf("%d", &num[i]);
            for (j=i-1; j>=0; j--){
                if (!prime_related(num[i], num[j]))
                    g[i][j] = g[j][i] = 1;
            }
        }
        Nx = Ny = n;
        printf("Case #%d: %d\n", counter, MaxMatch());
    }

    return 0;
}


