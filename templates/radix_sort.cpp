#include<iostream>
using namespace std;
int A[100000],B[100000],cnt[65536],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&A[i]);
    for(int i=1;i<=n;i++)cnt[(A[i])&65535]++;
    for(int i=1;i<65536;i++)cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--)B[cnt[A[i]&65535]--]=A[i];
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)cnt[(B[i])>>16]++;
    for(int i=1;i<65536;i++)cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--)A[cnt[B[i]>>16]--]=B[i];
    for(int i=1;i<=n;i++)printf("%d ",A[i]);
    system("pause");
    return 0;
}
