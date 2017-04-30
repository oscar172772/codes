#include<cstdio>
using namespace std;
int T,n,a,ns,flag;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ns=flag=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d",&a);
            ns^=a;
            flag+=a-1;
        }
        if((flag==0&&ns==0)||(flag!=0&&ns!=0))printf("John\n");
        else printf("Brother\n");
    }
    return 0;
}
