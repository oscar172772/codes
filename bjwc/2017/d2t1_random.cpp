#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=5000100;
int n,c,k,a[MAXN];
int p,a0,to,ha;
inline int f(int x){return (int)(((long long)(x)*x+c)%p);}
int cnt1,cnt2;
struct biao
{
    int a,time;
    bool operator<(const biao &c)const{return a<c.a;}
}tmp[MAXN];
int main()
{
    freopen("random.in","r",stdin);
    freopen("random.out","w",stdout);
    scanf("%d%d%d%d%d",&a0,&n,&c,&p,&k);
    to=ha=a0;
    do
    {
        to=f(to);ha=f(f(ha));
    }while(to!=ha);
    ha=a0;
    while(to!=ha)
    {
        to=f(to);ha=f(ha);
        if(to==ha)break;
        tmp[++cnt1].a=ha;
        tmp[cnt1].time=1;
    }
    if(n<=cnt1)
    {
        a[0]=a0;
        for(int i=1;i<=n;i++)
        {
            a[i]=f(a[i-1]);
        }
        sort(a+1,a+n+1);
        cout<<a[n-k+1]<<endl;
        return 0;
    }
    cnt2=cnt1;
    do
    {
        tmp[++cnt2].a=ha;
        ha=f(ha);
    }while(to!=ha);
    int left=n-cnt1;
    int right=left%(cnt2-cnt1),s=left/(cnt2-cnt1);
    for(int i=cnt1+1;i<=cnt2;i++)
    {
        if(i-cnt1<=right)tmp[i].time=s+1;
        else tmp[i].time=s;
    }
    sort(tmp+1,tmp+cnt2+1);
    //for(int i=1;i<=cnt2;i++){cout<<tmp[i].a<<' '<<tmp[i].time<<endl;}
    for(int i=cnt2;i>=1;i--)
    {
        k-=tmp[i].time;
        if(k<=0)
        {
            printf("%d\n",tmp[i].a);
            break;
        }
    }
    return 0;
}
