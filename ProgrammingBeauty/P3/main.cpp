#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

int n,m,a,b;
bool visited[10000005];
int x1[1005], x2[1005];
int p1[105], p2[105];
long long int sumx=0, temp = 0;


long long int calculate(int guess, int x[], int y[]){
    int res = 0;
    int i;
    for (i=1; i<=a; i++)
        res += (x[i] - guess) * (x[i] - guess);
    for (i=1; i<=b; i++)
        res += abs(y[i] - guess);
    return res;
}

bool isInRange(int guess, int k, int y[]){
    return (guess >= y[k] && guess <=y[k+1]);
}

int minCost(int x[], int y[]){
    int i, k;

    sumx = 0;temp = 0;
    y[0] = 0;y[b+1] = max(n, m)+1;
    memset(visited, 0, sizeof(visited));
    for (i=1; i<=a; i++)
        sumx += x[i];
    sort(y, y+b);
    for (k=0; k<=b; k++){
        double approx = double(b-2*k+2*sumx) / (2*a);
        int guess1 = ceil(approx), guess2 = floor(approx);
        if (!visited[guess1] && isInRange(guess1, k, y)){
            if (temp == 0)
                temp = calculate(guess1, x, y);
            else
                temp = min(temp, calculate(guess1, x, y));
            visited[guess1] = 1;
        }
        if (!visited[guess2] && isInRange(guess1, k, y)){
            if (temp == 0)
                temp = calculate(guess2, x, y);
            else
                temp = min(temp, calculate(guess2, x, y));
            visited[guess2] = 1;
        }
        cout<<guess1<<' '<<guess2<<endl;
    }

    return temp;
}

int main()
{
    int t, counter=0;
    int i, j;
    cin>>t;
    while (counter++ < t){
        scanf("%d %d %d %d", &n, &m, &a, &b);
        for (i=1; i<=a; i++)
            scanf("%d %d", &x1[i], &x2[i]);
        for (i=1; i<=b; i++)
            scanf("%d %d", &p1[i], &p2[i]);

        cout<<"Row "<<minCost(x1, p1)<<endl;
        cout<<"Coloum "<<minCost(x2, p2)<<endl;
        cout<<"Case #"<<counter<<": "<<(minCost(x1, p1) + minCost(x2, p2))<<endl;
    }
    return 0;
}
