#include <iostream>

using namespace std;

int a[100005];
int b[100005];
long long sum = 0;

void Merge(int x[], int l, int mid, int r){
        int start1 = l;
        int start2 = mid + 1;
        int count = 0;
        int remaing_b=0;
        while(start1<=mid && start2<=r){
            if (x[start1] >x[start2] ){
                b[count++] = x[start2++];
                remaing_b++;
            }else {
                b[count++] = x[start1++];
                sum+=remaing_b;
            }
        }
        while(start1 <= mid){
            b[count++] = x[start1++];
            sum+=remaing_b;
        }
        while(start2<=r){
            b[count++] = x[start2++];
        }
        for (int i=0; i<count; i++){
            x[i+l] = b[i];
        }
}

void MergeSort(int x[],  int l, int r){
    if (l == r)
        return;
    int mid = (l+r) >> 1;
    MergeSort(x, l, mid);
    MergeSort(x, mid+1, r);
    Merge(x, l, mid, r);
}

int main()
{
    int n;
    int i;
    cin>>n;
    for (i=0; i<n; i++){
        cin>>a[i];
    }
    MergeSort(a, 0, n-1);
    cout<<sum<<endl;
    return 0;
}
