#include <iostream>
#include <string>
#include <vector>
#

using namespace std;

typedef pair<int, int> pii;
const int MODULE = 100007;
vector<pii> u1, uk, temp;

int process(string s){
    int res, n, i, j, k;
    res = n = s.length();
    // 2-Palindrome
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            if (s[i] == s[j]){
                u1.push_back(make_pair(i, j));
                uk.push_back(make_pair(i, j));
                res=(res + (j-i)) % MODULE;
            }
    for (k=2; k<= n/2; k++){
        for (i=0; i<uk.size(); i++) {
            for (j=0; j<u1.size(); j++){
                int a1 = uk[i].first;int b1 = uk[i].second;
                int a2 = u1[j].first;int b2 = u1[j].second;
                if (a2 > a1 && b2 < b1){
                    res=(res + b2-a2) % MODULE;
                    temp.push_back(make_pair(a2, b2));
                }
            }
        }
        uk.clear();
        for (i=0; i<temp.size(); i++)
            uk.push_back(temp[i]);
        temp.clear();
    }
    return res;
}

int main()
{
    int t, n=0;
    string s;
    cin>>t;
    while (n++ < t){
        cin>>s;
        cout<<"Case #"<<n<<": "<<process(s)<<endl;
        u1.clear();
        uk.clear();
        temp.clear();
    }

    return 0;
}
