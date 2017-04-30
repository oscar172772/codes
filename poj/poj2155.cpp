#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN=1000;
int cass,n,t,c[MAXN+100][MAXN+100];
int x1,x2,y1,y2;
char ch;
int lowbit(int x){return x&(x^(x-1));}
void change(int x,int y,int s)
{
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=n;j+=lowbit(j))
            c[i][j]+=s;
}
int query(int x,int y)
{
    int s=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            s+=c[i][j];
    return s%2;
}
int main()
{
    scanf("%d",&cass);
    for(int kase=1;kase<=cass;kase++)
    {
        memset(c,0,sizeof(c));
        scanf("%d%d",&n,&t);
        for(int i=1;i<=t;i++)
        {
            scanf("%c%c",&ch,&ch);
            if(ch=='C')
            {
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                change(x1,y1,1);
                change(x2+1,y1,1);
                change(x1,y2+1,1);
                change(x2+1,y2+1,1);
            }
            if(ch=='Q')
            {
                scanf("%d%d",&x1,&y1);
                printf("%d\n",query(x1,y1));
            }
            /*for(int x=1;x<=n;x++)
            {
                for(int y=1;y<=n;y++)
                    cout<<c[x][y]<<' ';
                cout<<endl;
            }*/
        }
        printf("\n");
    }
    //system("pause");
    return 0;
}
