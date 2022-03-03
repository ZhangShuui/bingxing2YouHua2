#include <iostream>
#include <windows.h>
using  namespace std;
int a[100000];
int sum=0;

void countAll(int n){
    if (n==1)
        return ;
    else{
        for (int i = 0; i < n / 2; ++i) {
            a[i] += a[n-i-1];
        }           //类似“折叠”——利用for循环将后半部分数组加到前半部分，这个操作中同时访问了两个地址，充分利用了超标量
        n /=2;      //下一次递归将针对前半部分数组进行“折叠”()
        countAll(n);
    }
}
int main() {
    for (int i = 0; i < 100000; ++i) {
        a[i]=i;
    }
    int n=2;
    long long freq,start,end;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    while(n<100000){
        int counter=0;
        QueryPerformanceCounter((LARGE_INTEGER*)&start);
        QueryPerformanceCounter((LARGE_INTEGER*)&end);
        while(end-start<100000){
            sum=0;
            countAll(n);
            counter++;
            QueryPerformanceCounter((LARGE_INTEGER*)&end);
        }
        float seconds=float (end-start)/float (freq);
        cout<<n<<","<<counter<<","<<seconds<<","<<seconds/double (counter)<<endl;
        n*=2;
    }
    return 0;
}

