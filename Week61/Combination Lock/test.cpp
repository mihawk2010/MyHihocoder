#include <fstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)

using namespace std;

const int N = 10000;
const int M = 10000;


int main(){

    ofstream fout("data.out");

    srand((int)time(0));
    fout<<N<<' '<<M<<endl;
    for (int i=0; i<N; i++){
        fout<<char(random(26)+'A');
    }
    fout<<endl;
    for (int p=0; p<N; p++){
        fout<<"CMD ";
        int type = random(4)+1;
        int i = random(N)+1;
        int j = random(N)+1;

        if (i>j){
            int temp = j;
            j = i;
            i = temp;
        }

        switch (type){
            case 1:
                fout<<type<<" "<<i<<" "<<j<<" "<<char(random(26)+'A')<<endl;
                break;
            case 2:
                fout<<type<<" "<<i<<" "<<j<<" "<<random(50000)+1<<endl;
                break;
            case 3:
                fout<<type<<" "<<i<<endl;
                break;
            case 4:
                fout<<type<<" "<<i<<" "<<j<<endl;
                break;
        }
    }

    return 0;
}
