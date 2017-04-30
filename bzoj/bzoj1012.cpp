#include<cstdio>
int n,d,num;
int a[300000],pos[300000];
int top,l,r,mid,t;
char ch;
int main()
{
    scanf("%d %d",&n,&d);
    for(int i=0;i<n;)
    {
        scanf(" %c %d",&ch,&num);
        if(ch=='A')
        {
            num=(num+t)%d;i++;
            while(top>0&&num>a[top])top--;
            a[++top]=num;pos[top]=i;
        }
        else
        {
            l=1,r=top;
            while(l!=r)
            {
                mid=l+r>>1;
                if(pos[mid]<i-num+1)l=mid+1;
                else r=mid;
            }
            printf("%d\n",t=a[l]);
            n--;
        }
    }
    return 0;
}
