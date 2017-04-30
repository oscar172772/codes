#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const double eps=4e-7,maxt=58274,Inf=1927481374820.0;
struct edge
{
    int v;
    double f;
    edge *next,*rev;
}*h[110],pool[100000];
int top;
const int S=105,T=106,rightpoint=52;
int m,n,B[55],A[55],C[55][55];
double l,r=maxt,sum,ans;
void addedge(int u,int v,double c)//u->v,cap=c
{
    edge *tmp=&pool[top++],*pmt=&pool[top++];
    tmp->v=v;pmt->v=u;
    tmp->f=c;pmt->f=0;
    tmp->next=h[u];pmt->next=h[v];
    h[u]=tmp;h[v]=pmt;
    tmp->rev=pmt;pmt->rev=tmp;
}
int level[110];
queue<int> q;
inline bool mklevel()
{
    memset(level,-1,sizeof(level));
    while(!q.empty())q.pop();
    q.push(S);
    level[S]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(edge *tmp=h[u];tmp;tmp=tmp->next)
        {
            if(level[tmp->v]==-1&&tmp->f>0)
            {
                level[tmp->v]=level[u]+1;
                q.push(tmp->v);
            }
        }
        if(level[T]!=-1)return true;
    }
    return false;
}
inline void pt(int x){if(x==S)cout<<'S';else if(x==T)cout<<'T';else if(x>rightpoint)cout<<"A"<<x-rightpoint;else cout<<"B"<<x;}
double dinic(int cur,double minn)
{
    //cout<<"dinic'ing at point ";pt(cur);cout<<", starting with flow "<<minn<<endl;
    if(cur==T)return minn;
    double curf=0;
    for(edge *tmp=h[cur];tmp;tmp=tmp->next)
    {
        if(level[tmp->v]==level[cur]+1&&tmp->f>0)
        {
            double f=dinic(tmp->v,min(minn-curf,tmp->f));
            if(f)
            {
                tmp->f-=f;
                tmp->rev->f+=f;
                curf+=f;
            }
            if(minn==curf)break;
        }
    }
    if(curf==0)level[cur]=-1;
    //cout<<"ended dinic at point ";pt(cur);cout<<" with flow "<<curf<<endl;
    return curf;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
        //addedge(S,i,x);
        sum+=A[i];
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&B[i]);
        //addedge(rightpoint+i,T,x);
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&C[i][j]);
            //if(C[i][j])addedge(i,j,Inf);
        }
    }
    while(r-l>eps)
    {
        //cout<<"binary searching at "<<l<<endl;
        ans=0;top=0;
        memset(h,0,sizeof(h));
        double mid=(l+r)/2;
        for(int i=1;i<=m;i++)
        {
            addedge(S,i,B[i]*mid);
        }
        for(int i=1;i<=n;i++)
        {
            addedge(rightpoint+i,T,A[i]);
        }
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(C[i][j])addedge(i,rightpoint+j,Inf);
            }
        }
        while(mklevel())
        {
            /*cout<<"mklevel success\n"/*, levels are:\n";
            pt(S);cout<<'='<<level[S]<<endl;
            for(int i=1;i<=n;i++){pt(i);cout<<'='<<level[i]<<endl;}
            for(int i=1+rightpoint;i<=m+rightpoint;i++){pt(i);cout<<'='<<level[i]<<endl;}
            pt(T);cout<<'='<<level[T]<<endl*/;
            ans+=dinic(S,Inf);
        }
        //cout<<"one turn ended...\nAfter all, the current flow equals "<<ans<<"\n";
        if(sum-ans<eps)r=mid;
        else l=mid;
    }
    printf("%lf\n",(l+r)/2);
    //system("pause");
    return 0;
}
