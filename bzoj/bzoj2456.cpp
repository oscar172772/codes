#include<cstdio>
using namespace std;
int n,a,cur,cnt;
int main()
{
    scanf("%d",&n);
    scanf("%d",&a);cur=a,cnt=1;
    while(--n)
    {
        scanf("%d",&a);
        if(a==cur)cnt++;
        else if(cnt)cnt--;
        else cnt=1,cur=a;
    }
    printf("%d\n",cur);
    return 0;
}
