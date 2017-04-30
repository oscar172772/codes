#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int N,M,K,cnt;
struct edge
{
    int v;
    edge *next;
}pool[400200],*h[400100];
int top,top2;
void addedge(int u,int v)
{
    edge *tmp=&pool[top++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&pool[top++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
bool flag[400100];
int seq[400100],pa[400100],seq2[400100];
int find(int x){return pa[x]<0?x:pa[x]=find(pa[x]);}
void onion(int x,int y)
{
    int px=find(x),py=find(y);
    if(px!=py)
    {
        cnt--;
        pa[px]=py;
    }
}
int main()
{
    scanf("%d%d",&N,&M);
    int x,y;
    for(int i=0;i<M;i++)
    {
        scanf("%d%d",&x,&y);
        addedge(x,y);
    }
    memset(flag,1,sizeof(flag));
    memset(pa,-1,sizeof(pa));
    scanf("%d",&K);
    for(int i=0;i<K;i++)
    {
        scanf("%d",&seq[i]);
        flag[seq[i]]=false;
    }
    cnt=N;
    for(int i=0;i<N;i++)
    {
        if(flag[i])
        {
            for(edge *tmp=h[i];tmp;tmp=tmp->next)
            {
                if(flag[tmp->v])onion(i,tmp->v);
            }
        }
    }
    seq2[top2++]=cnt;
    for(int i=K-1;i>=0;i--)
    {
        flag[seq[i]]=true;
        for(edge *tmp=h[seq[i]];tmp;tmp=tmp->next)
        {
            if(flag[tmp->v])onion(seq[i],tmp->v);
        }
        seq2[top2++]=cnt;
    }
    for(int i=top2-1;i>=0;i--)
    {
        printf("%d\n",seq2[i]-top2+i+1);
    }
    return 0;
}
