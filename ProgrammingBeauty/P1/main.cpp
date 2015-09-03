#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

map<string, int> Month = {{"January", 1}, {"February",2}, {"March", 3}, {"April", 4},
                    {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8}, {"September", 9},
                    {"October", 10}, {"November", 11}, {"December", 12}};

bool isLeapYear(int year){
    return (((year % 4 == 0) && (year % 100 != 0))|| (year % 400 == 0));
}

int calculate(int year1, int year2, int gap){
    if (year1 > year2) return 0;
    int n = (year2 - year1 + 1) / gap;
    int remainder = (year2 - year1 + 1) % gap;
    for (int i=0; i<remainder; i++){
        if ((year1+i) % gap == 0){
            n++;
            break;
        }
    }
    return n;
}

bool beforeLeap(string smonth, int syear){

    return (isLeapYear(syear) && (Month[smonth]<=2) );
}

bool afterLeap(string smonth, string sday, int syear){
    char day[5];
    int i;
    for (i=0; i<sday.length()-1; i++)
        day[i] = sday[i];
    day[i] = '\0';
    return ((isLeapYear(syear) && ((Month[smonth]>2) || ((Month[smonth]==2) && (atoi(day)
     == 29)))));
}

int main()
{
    string smonth, sday, eday, emonth;
    int syear, eyear, t;
    int n=0;
    cin>>t;
    while(n++ < t){
        cin>>smonth>>sday>>syear>>emonth>>eday>>eyear;
        int res = calculate(syear+1, eyear-1, 4) - calculate(syear+1, eyear-1, 100) \
            + calculate(syear+1, eyear-1, 400);
        //cout<<"res = "<<res<<endl;
        if (syear == eyear && beforeLeap(smonth, syear) && afterLeap(emonth, eday, eyear))
            res++;
        else if (syear != eyear){
            if (beforeLeap(smonth, syear))
                res++;
            if (afterLeap(emonth, eday, eyear))
                res++;
        }

        cout<<"Case #"<<n<<": "<<res<<endl;
    }

    //cout << "Hello world!" << endl;
    return 0;
}
