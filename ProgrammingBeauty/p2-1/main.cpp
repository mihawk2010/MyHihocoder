#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

inline int compare(string str1, string str2)
{
      if(str1.size() > str2.size()) //长度长的整数大于长度小的整数
            return 1;
      else if(str1.size() < str2.size())
            return -1;
      else
            return str1.compare(str2); //若长度相等，从头到尾按位比较，compare函数：相等返回0，大于返回1，小于返回－1
}

//高精度加法
string ADD_INT(string str1, string str2)
{
      string MINUS_INT(string str1, string str2);
      int sign = 1; //sign 为符号位
      string str;
      if(str1[0] == '-') {
           if(str2[0] == '-') {
                 sign = -1;
                 str = ADD_INT(str1.erase(0, 1), str2.erase(0, 1));
           }else {
                 str = MINUS_INT(str2, str1.erase(0, 1));
           }
      }else {
           if(str2[0] == '-')
                 str = MINUS_INT(str1, str2.erase(0, 1));
           else {
                 //把两个整数对齐，短整数前面加0补齐
                 string::size_type l1, l2;
                 int i;
                 l1 = str1.size(); l2 = str2.size();
                 if(l1 < l2) {
                       for(i = 1; i <= l2 - l1; i++)
                       str1 = "0" + str1;
                 }else {
                       for(i = 1; i <= l1 - l2; i++)
                       str2 = "0" + str2;
                 }
                 int int1 = 0, int2 = 0; //int2 记录进位
                 for(i = str1.size() - 1; i >= 0; i--) {
                       int1 = (int(str1[i]) - 48 + int(str2[i]) - 48 + int2) % 10;  //48 为 '0' 的ASCII 码
                       int2 = (int(str1[i]) - 48 + int(str2[i]) - 48 +int2) / 10;
                       str = char(int1 + 48) + str;
                 }
                 if(int2 != 0) str = char(int2 + 48) + str;
          }
     }
     //运算后处理符号位
     if((sign == -1) && (str[0] != '0'))
          str = "-" + str;
     return str;
}

//高精度减法
string MINUS_INT(string str1, string str2)
{
     string MULTIPLY_INT(string str1, string str2);
     int sign = 1; //sign 为符号位
     string str;
     if(str2[0] == '-')
            str = ADD_INT(str1, str2.erase(0, 1));
     else {
            int res = compare(str1, str2);
            if(res == 0) return "0";
            if(res < 0) {
                  sign = -1;
                  string temp = str1;
                  str1 = str2;
                  str2 = temp;
            }
            string::size_type tempint;
            tempint = str1.size() - str2.size();
            for(int i = str2.size() - 1; i >= 0; i--) {
                 if(str1[i + tempint] < str2[i]) {
                       str1[i + tempint - 1] = char(int(str1[i + tempint - 1]) - 1);
                       str = char(str1[i + tempint] - str2[i] + 58) + str;
                 }
                 else
                       str = char(str1[i + tempint] - str2[i] + 48) + str;
            }
           for(int i = tempint - 1; i >= 0; i--)
                str = str1[i] + str;
     }
     //去除结果中多余的前导0
     str.erase(0, str.find_first_not_of('0'));
     if(str.empty()) str = "0";
     if((sign == -1) && (str[0] != '0'))
          str = "-" + str;
     return str;
}

//高精度乘法
string MULTIPLY_INT(string str1, string str2)
{
     int sign = 1; //sign 为符号位
     string str;
     if(str1[0] == '-') {
           sign *= -1;
           str1 = str1.erase(0, 1);
     }
     if(str2[0] == '-') {
           sign *= -1;
           str2 = str2.erase(0, 1);
     }
     int i, j;
     string::size_type l1, l2;
     l1 = str1.size(); l2 = str2.size();
     for(i = l2 - 1; i >= 0; i --) {  //实现手工乘法
           string tempstr;
           int int1 = 0, int2 = 0, int3 = int(str2[i]) - 48;
           if(int3 != 0) {
                  for(j = 1; j <= (int)(l2 - 1 - i); j++)
                        tempstr = "0" + tempstr;
                  for(j = l1 - 1; j >= 0; j--) {
                        int1 = (int3 * (int(str1[j]) - 48) + int2) % 10;
                        int2 = (int3 * (int(str1[j]) - 48) + int2) / 10;
                        tempstr = char(int1 + 48) + tempstr;
                  }
                  if(int2 != 0) tempstr = char(int2 + 48) + tempstr;
           }
           str = ADD_INT(str, tempstr);
     }
     //去除结果中的前导0
     str.erase(0, str.find_first_not_of('0'));
     if(str.empty()) str = "0";
     if((sign == -1) && (str[0] != '0'))
           str = "-" + str;
     return str;
}
//高精度除法
string DIVIDE_INT(string str1, string str2, int flag)
{
     //flag = 1时,返回商; flag = 0时,返回余数
     string quotient, residue; //定义商和余数
     int sign1 = 1, sign2 = 1;
     if(str2 == "0") {  //判断除数是否为0
           quotient = "ERROR!";
           residue = "ERROR!";
           if(flag == 1) return quotient;
           else return residue;
     }
     if(str1 == "0") { //判断被除数是否为0
           quotient = "0";
           residue = "0";
     }
     if(str1[0] == '-') {
           str1 = str1.erase(0, 1);
           sign1 *= -1;
           sign2 = -1;
     }
     if(str2[0] == '-') {
           str2 = str2.erase(0, 1);
           sign1 *= -1;
     }
     int res = compare(str1, str2);
     if(res < 0) {
           quotient = "0";
           residue = str1;
     }else if(res == 0) {
           quotient = "1";
           residue = "0";
     }else {
           string::size_type l1, l2;
           l1 = str1.size(); l2 = str2.size();
           string tempstr;
           tempstr.append(str1, 0, l2 - 1);
           //模拟手工除法
           for(int i = l2 - 1; i < l1; i++) {
                 tempstr = tempstr + str1[i];
                 for(char ch = '9'; ch >= '0'; ch --) { //试商
                       string str;
                       str = str + ch;
                       if(compare(MULTIPLY_INT(str2, str), tempstr) <= 0) {
                              quotient = quotient + ch;
                              tempstr = MINUS_INT(tempstr, MULTIPLY_INT(str2, str));
                              break;
                       }
                 }
           }
           residue = tempstr;
     }
     //去除结果中的前导0
     quotient.erase(0, quotient.find_first_not_of('0'));
     if(quotient.empty()) quotient = "0";
     if((sign1 == -1) && (quotient[0] != '0'))
     quotient = "-" + quotient;
     if((sign2 == -1) && (residue[0] != '0'))
     residue = "-" + residue;
     if(flag == 1) return quotient;
     else return residue;
}

//高精度除法,返回商
string DIV_INT(string str1, string str2)
{
      return DIVIDE_INT(str1, str2, 1);
}
//高精度除法,返回余数
string MOD_INT(string str1, string str2)
{
      return DIVIDE_INT(str1, str2, 0);
}

int v[14], appear[14];
vector<int> p;

long long int factorial(int n){
    int res=1;
    if (n<1)
        return 0;
    for (int i=1; i<=n; i++)
        res *= i;
    return res;
}

int main()
{
    int t, counter=0, n;
    int i, j;
    string s;

    cin>>t;
    while (counter++ < t){
        scanf("%d", &n);
        p.clear();
        for (i=0; i<13; i++)
            appear[i] = v[i] = 0;

        for (i=0; i<n; i++){
            cin>>s;
            if (char(s[0])>='2' && char(s[0])<='9'){
                if (!v[char(s[0])-'0']){
                    p.push_back(char(s[0])-'0');
                    v[char(s[0])-'0'] = 1;

                }
                appear[char(s[0])-'0']++;
            }
            else if (s[0] == 'A'){
               if  (!v[1]){
                    p.push_back(1);
                    v[1]=1;
                }
                appear[1]++;
            }else if (s[0] == 'T'){
               if  (!v[10]){
                    p.push_back(10);
                    v[10] = 1;

                }
                appear[10]++;
            }else if (s[0] == 'J'){
               if  (!v[11]){
                    p.push_back(11);
                    v[11] = 1;
                }
                appear[11]++;
            }else if (s[0] == 'Q'){
                if (!v[12]){
                    p.push_back(12);
                    v[12] = 1;

                }
                appear[12]++;
            }else if (s[0] == 'K'){
               if  (!v[13]){
                    p.push_back(13);
                    v[13] = 1;
                }
                appear[13]++;
            }
        }



        /**
        vector<int> q, maxappear=0;;

        for (i=0; i<p.size(); i++){
            if (appear[p[i]]>1){
                q.push_back(p[i]);
            }
            maxappear = max(maxappear, appear[p[i]]);
        }

        int res = 0, k;
        for (k=0; k<=q.size(); k++){

        }
        **/
        //printf("Case #%d: %d\n", counter, MaxMatch());
    }

    return 0;
}
