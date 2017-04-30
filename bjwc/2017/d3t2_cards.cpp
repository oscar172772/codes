#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k;
long long a,b,p[5],c[5],maxx=-1000000000,minn=1000000000;
long long cl[16];//xxxx,x={0,1},4321
long long lft[16];
int bit[9]={0,1,2,0,3,0,0,0,4};
int flagr;
struct ppff
{
    long long num;
    int id;
    inline bool operator<(const ppff &c)const{return num<c.num;}
}pf[16];
bool IsPrime(long long x)
{
    if(x<=1)return false;
    for(long long k=2;k<=sqrt(x);k++)
    {
        if(x%k==0)return false;
    }
    return true;
}
inline bool cmp(const ppff &a,const ppff &b){return a.num>b.num;}
int main()
{
    freopen("cards.in","r",stdin);
    freopen("cards.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        flagr=0;
        scanf("%lld%lld",&a,&b);
        //cout<<a<<':';
        if(IsPrime(a))flagr|=1<<0;
        long long left=a,cnt=0,tmp=1,tmp2=1,sum=1;
        long long time=0;
        bool flag=true,flag2=false;
        for(long long p=2;p<=sqrt(left);p++)
        {
            if(IsPrime(p)&&left%p==0)
            {
                cnt=0;
                while(left%p==0)
                {
                    left/=p;
                    cnt++;
                    tmp2=tmp2*p+1;
                }
                tmp*=cnt+1;
                sum*=tmp2;
                tmp2=1;
                if(cnt%2==1&&cnt>0)time++;
                if(cnt%4!=3&&cnt%4!=0)flag=false;
                if(cnt>0&&cnt%4==3)flag2=true;
            }
        }
        if(left>=2)
        {
            tmp*=2;
            sum*=left+1;
            time++;
            flag=false;
        }
        if(IsPrime(tmp))flagr|=1<<1;
        if(IsPrime(sum))flagr|=1<<2;
        if(time>=2||flag||flag2)flagr|=1<<3;
        cl[flagr]+=b;
    }
    for(int i=1;i<=4;i++)scanf("%lld",&p[i]);
    for(int i=1;i<=4;i++)scanf("%lld",&c[i]);
    for(int i=0;i<16;i++)
    {
        int tmp=i,lowbit;
        while(tmp)
        {
            lowbit=bit[tmp&(-tmp)];
            pf[i].num+=p[lowbit];
            //cout<<i<<' '<<tmp<<' '<<1<<(lowbit-1)<<' '<<pf[i].num<<endl;
            tmp-=1<<(lowbit-1);
        }
        pf[i].id=i;
    }
    int used,need;
    long long point;
    sort(pf,pf+16,cmp);
    for(int i=0;i<1<<15;i++)
    {
        used=point=0;
        need=k;
        for(int j=0;j<16;j++)
        {
            if(i&(1<<pf[j].id) && cl[pf[j].id])
            {
                lft[pf[j].id]=cl[pf[j].id]-1;
                need--;
                used|=pf[j].id;
                point+=pf[j].num;
            }
            else lft[pf[j].id]=0;
        }
        if(need<0)continue;
        for(int j=0;j<16;j++)
        {
            if(lft[pf[j].id])
            {
                if(lft[pf[j].id]<=need)
                {
                    need-=lft[pf[j].id];
                    point+=pf[j].num*lft[pf[j].id];
                }
                else
                {
                    point+=pf[j].num*need;
                    need=0;
                }
            }
        }
        if(need)continue;
        for(int j=0;j<4;j++)
        {
            if(!(used&(1<<j)))point+=c[j+1];
        }
        if(point>maxx)maxx=point;
        //cout<<i<<' '<<point<<endl;
    }
    sort(pf,pf+16);
    for(int i=0;i<1<<15;i++)
    {
        used=point=0;
        need=k;
        for(int j=0;j<16;j++)
        {
            if(i&(1<<pf[j].id) && cl[pf[j].id])
            {
                lft[pf[j].id]=cl[pf[j].id]-1;
                need--;
                used|=pf[j].id;
                point+=pf[j].num;
            }
            else lft[pf[j].id]=0;
        }
        if(need<0)continue;
        for(int j=0;j<16;j++)
        {
            if(lft[pf[j].id])
            {
                if(lft[pf[j].id]<=need)
                {
                    need-=lft[pf[j].id];
                    point+=pf[j].num*lft[pf[j].id];
                }
                else
                {
                    point+=pf[j].num*need;
                    need=0;
                }
            }
        }
        if(need)continue;
        for(int j=0;j<4;j++)
        {
            if(!(used&(1<<j)))point+=c[j+1];
        }
        if(point<minn)minn=point;
        //cout<<i<<' '<<point<<endl;
    }
    printf("%lld %lld\n",maxx,minn);
    /*
    for(int i=0;i<16;i++)
    {
        cout<<i<<' '<<cl[i]<<' '<<lft[i]<<' '<<pf[i].id<<' '<<pf[i].num<<endl;
    }
    */
    return 0;
}
