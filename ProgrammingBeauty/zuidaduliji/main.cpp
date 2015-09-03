#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

#define SIZE 1002
int num[SIZE];
int mat[SIZE][SIZE];  /*图矩阵*/
int dp[SIZE];
int mx;
int stack[SIZE][SIZE];
void dfs(int N,int num,int step){

    if(num==0){
        if(step > mx){
            mx=step;
        }
        return ;
    }

    for(int i=0;i<num;i++){
        int k = stack[step][i];
        if(step+N-k<=mx) return ;
        if(step+dp[k]<=mx) return ;
        int cnt = 0;
        for(int j=i+1;j<num;j++)
            if(mat[k][stack[step][j]]){
                 stack[step+1][cnt++]=stack[step][j];
            }
        dfs(N,cnt,step+1);
    }
}

void run(int N){

    mx =0;
    for(int i=N-1;i>=0;i--){
        int sz =0;
        for(int j=i+1;j<N;j++)
            if(mat[i][j]) stack[1][sz++]=j;
        dfs(N,sz,1);
        dp[i]=mx;
    }
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
        for (i=0; i<n; i++)
            scanf("%d", &num[i]);
        for (i=0; i<n; i++)
            for (j=0; j<n; j++)
                mat[i][j] = 0;
        for (i=0; i<n; i++){
            for (j=i+1; j<n; j++){
                if (!prime_related(num[i], num[j]))
                    mat[i][j] = mat[j][i] = 1;
            }
        }
        run(n);
        printf("Case #%d: %d\n", counter, dp[0]);
    }

    return 0;
}
