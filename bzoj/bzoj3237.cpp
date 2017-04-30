#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int curr=123124125;
inline int ran(){return (curr+=(curr<<2)+1)&0x7fffffff;}
int pa[201000];
int find(int x){return pa[x]?pa[x]=find(pa[x]):x;}
struct edge
{
    int v,id,ch;
    edge *next,*rev;
}*h[201000],pool[1501000];
int top;
void addedge(int u,int v,int id)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;tmp->id=id;
    edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;pmt->id=id;
    tmp->rev=pmt;pmt->rev=tmp;
}
int n,m,q;
int k;
int u,v;
int val[1501000],sum[201000],start;
int nodeval[201000],vis[201000];
void bfs(int u)
{
    vis[u]=1;
    nodeval[u]=sum[u];
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(tmp->ch&&!vis[tmp->v])
        {
            bfs(tmp->v);
            nodeval[u]^=nodeval[tmp->v];
            val[tmp->id]=nodeval[tmp->v];
        }
    }
}
inline void build()
{
    for(int i=1;i<=n;i++)
    {
        int cnt=0;
        for(edge *tmp=h[i];tmp;tmp=tmp->next)
        {
            int px=find(i),py=find(tmp->v);
            if(px!=py)
            {
                tmp->ch=1;tmp->rev->ch=1;
                pa[px]=py;
            }
            else if((!tmp->ch)&&!val[tmp->id])
            {
                int t=ran();
                val[tmp->id]=t;
                sum[i]^=t;
                sum[tmp->v]^=t;
            }
            if(tmp->ch)cnt++;
        }
        if(cnt==1)start=i;
    }
    bfs(start);
}
int c[50],cnt;
int lb[32];
inline int lowbit(int x)
{
    switch(x&-x)
    {
        case 0x1:return 0;
        case 0x2:return 1;
        case 0x4:return 2;
        case 0x8:return 3;
        case 0x10:return 4;
        case 0x20:return 5;
        case 0x40:return 6;
        case 0x80:return 7;
        case 0x100:return 8;
        case 0x200:return 9;
        case 0x400:return 10;
        case 0x800:return 11;
        case 0x1000:return 12;
        case 0x2000:return 13;
        case 0x4000:return 14;
        case 0x8000:return 15;
        case 0x10000:return 16;
        case 0x20000:return 17;
        case 0x40000:return 18;
        case 0x80000:return 19;
        case 0x100000:return 20;
        case 0x200000:return 21;
        case 0x400000:return 22;
        case 0x800000:return 23;
        case 0x1000000:return 24;
        case 0x2000000:return 25;
        case 0x4000000:return 26;
        case 0x8000000:return 27;
        case 0x10000000:return 28;
        case 0x20000000:return 29;
        case 0x40000000:return 30;
        case 0x80000000:return 31;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v,i);
    }
    build();
    scanf("%d",&q);
    int flag;
    for(int qq=1;qq<=q;qq++)
    {
        memset(lb,0,sizeof(lb));flag=0;
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
        {
            scanf("%d",&c[i]);
        }
        for(int i=1;i<=k;i++)
        {
            int tmp=val[c[i]];
            while(tmp!=0&&lb[lowbit(tmp)])tmp^=lb[lowbit(tmp)];
            if(tmp==0)
            {
                printf("Disconnected\n");
                flag=1;
                break;
            }
            else
            {
                lb[lowbit(tmp)]=tmp;
            }
        }
        if(!flag){printf("Connected\n");cnt++;}
    }
    return 0;
}
