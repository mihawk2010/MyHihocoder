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

int main()
{

        ifstream fin("data.out");
        ofstream fout("bruteforce.out");
        int n, m, type;
        string str, temp;

        fin>>n>>m;
        fin>>str;

        for (int p=0; p<m; p++){
            fin>>temp>>type;
            int i, j, k;
            char c;
            switch (type){
                case 1:
                    fin>>i>>j>>c;
                    str.replace(i-1, j-i+1, j-i+1, c);
                    break;
                case 2:
                    fin>>i>>j>>k;
                    for (int q=i-1; q<=j-1; q++){
                        int res = str[q] - 'A' + k;
                        res = res % 26;
                        str[q] = res + 'A';
                    }
                    break;
                case 3:
                    fin>>k;
                    str = str.substr(k, n-k) + str.substr(0, k);
                    break;
                case 4:
                    fin>>i>>j;
                    int inc = 1;
                    for (int q=i-1; q<=j-1; q++){
                        int res = str[q] - 'A' + inc;
                        inc++;
                        res = res % 26;
                        str[q] = res + 'A';
                    }
                    break;
            }
        }

        fout<<str<<endl;
        return 0;
}
