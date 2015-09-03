#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <fstream>

using namespace std;

typedef pair<int, int> pii;
int n,m,a,b;
int x1[1005], x2[1005];
int p1[105], p2[105];
unsigned long long int sumx=0, temp = 0;


unsigned long long int calculate(int guess, int x[], int y){
    unsigned long long int res = 0;
    int i;
    for (i=1; i<=a; i++){
        res += (x[i] - guess) * (x[i] - guess);
    }
    return res+abs(guess - y);
}

unsigned long long int minCost(int x[], int y){
    int i, k;
    unsigned long long int res = 0;
    sumx = 0;
    for (i=1; i<=a; i++)
        sumx += x[i];
    for (k=0; k<=1; k++){
        double approx = double(2*sumx - 2*k+1) / (2*a);
        int guess1 = ceil(approx), guess2 = floor(approx);
        //cout<<"Guess "<<guess1<<' '<<guess2<<endl;
        if (k ==0 && guess1 <= y)
            if (res == 0)
                res = calculate(guess1, x, y);
            else res = min(res, calculate(guess1, x, y));
        if (k ==0 && guess2 <= y)
            if (res == 0)
                res = calculate(guess1, x, y);
            else
                res = min(res, calculate(guess2, x, y));
        if (k ==1 && guess1 >= y)
            if (res == 0)
                res = calculate(guess1, x, y);
            else
                res = min(res, calculate(guess1, x, y));
        if (k ==1 && guess2 >= y)
            if (res == 0)
                res = calculate(guess1, x, y);
            else
                res = min(res, calculate(guess2, x, y));
    }
    //cout<<"res = "<<res<<endl;
    return res;
}

int main()
{
    int t, counter=0;
    int i;
    cin>>t;
    while (counter++ < t){
        scanf("%d %d %d %d", &n, &m, &a, &b);
        for (i=1; i<=a; i++)
            scanf("%d %d", &x1[i], &x2[i]);
        for (i=1; i<=b; i++)
            scanf("%d %d", &p1[i], &p2[i]);
        temp = 0;
        for (i=1; i<=b; i++)
            if (temp == 0)
                temp = minCost(x1,p1[i]) + minCost(x2,p2[i]);
            else temp = min(temp, minCost(x1,p1[i]) + minCost(x2,p2[i]));

        cout<<"Case #"<<counter<<": "<<temp<<endl;
    }
    return 0;
}
