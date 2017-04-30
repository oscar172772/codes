#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500500;
int dep[MAXN],siz[MAXN],maxson[MAXN],pa[MAXN],pathtop[MAXN],val[MAXN],itn[MAXN],nti[MAXN],deg[MAXN];//id_to_node/node_to_id
struct node
{
    int l,r,s;
    node *lson,*rson;
}*root,pool[MAXN*2];
int top;
node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->l=l;tmp->r=r;
    if(l==r)
    {
        tmp->s=val[itn[l]];
    }
    else
    {
        int m=(l+r)>>1;
        tmp->lson=bt(l,m);
        tmp->rson=bt(m+1,r);
        tmp->s=tmp->lson->s^tmp->rson->s;
    }
    return tmp;
}
void change(node *cur,int pos,int k)
{
    if(cur->l==cur->r)
    {
        cur->s=k;
        return;
    }
    else if(cur->lson->r>=pos)
        change(cur->lson,pos,k);
    else
        change(cur->rson,pos,k);
    cur->s=cur->lson->s^cur->rson->s;
}
int query(node *cur,int l,int r)
{
    //cout<<"query "<<cur->l<<' '<<cur->r<<' '<<l<<' '<<r<<endl;
    if(cur->l==l&&cur->r==r)return cur->s;
    if(cur->lson->r>=r)return query(cur->lson,l,r);
    else if(cur->rson->l<=l)return query(cur->rson,l,r);
    else return query(cur->lson,l,cur->lson->r)^query(cur->rson,cur->rson->l,r);
}
struct edge
{
    int v;
    edge *next;
}*h[MAXN],epool[MAXN*2];
int etop,ltop;
inline void addedge(int u,int v)
{
    edge *tmp=&epool[etop++];tmp->v=v;tmp->next=h[u];h[u]=tmp;
    edge *pmt=&epool[etop++];pmt->v=u;pmt->next=h[v];h[v]=pmt;
}
void dfs1(int u)
{
    //cout<<"dfs1 "<<u<<endl;
    siz[u]=1;
    int ms=0;
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(dep[tmp->v]==-1)
        {
            dep[tmp->v]=dep[u]+1;
            pa[tmp->v]=u;
            dfs1(tmp->v);
            siz[u]+=siz[tmp->v];
            if(siz[tmp->v]>siz[ms])ms=tmp->v;
        }
    }
    maxson[u]=ms;
}
int curtop;
void dfs2(int u)
{
    //cout<<"dfs2 "<<u<<endl;
    pathtop[u]=curtop;
    int ms=maxson[u];
    itn[++ltop]=u;nti[u]=ltop;
    if(ms)
    {
        dfs2(ms);
    }
    for(edge *tmp=h[u];tmp;tmp=tmp->next)
    {
        if(dep[tmp->v]==dep[u]+1&&tmp->v!=ms)
        {
            curtop=tmp->v;
            dfs2(tmp->v);
        }
    }
}
inline void ctree(int pos,int k)
{
    change(root,nti[pos],k);
}
inline int qtree(int a,int b)
{
    int ans=0;
    while(pathtop[a]!=pathtop[b])
    {
        //cout<<"qtree_jump "<<a<<' '<<b<<endl;
        if(dep[pathtop[a]]>dep[pathtop[b]])
        {
            ans^=query(root,nti[pathtop[a]],nti[a]);
            a=pa[pathtop[a]];
        }
        else
        {
            ans^=query(root,nti[pathtop[b]],nti[b]);
            b=pa[pathtop[b]];
        }
    }
    //cout<<"qtree_same_chain"<<a<<' '<<b<<endl;
    if(dep[a]>dep[b])swap(a,b);
    ans^=query(root,nti[a],nti[b]);
    return ans;
}
const string ans[2]={"Yes\n","No\n"};
int main()
{
    int n,q,u,v,maxdeg=0,start;char ch;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&val[i]);
    }
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        addedge(u,v);
        deg[u]++;deg[v]++;
        if(maxdeg<deg[u])maxdeg=deg[u];
        if(maxdeg<deg[v])maxdeg=deg[v];
    }
    if(maxdeg>2)
    {
        memset(dep,-1,sizeof(dep));
        dep[1]=0;
        dfs1(1);
        curtop=1;
        dfs2(1);
    }
    else
    {
        for(int i=1;i<=n;i++)
            if(deg[i]==1)
            {
                start=i;
                break;
            }
        int cur=start,depcnt=0;
        while(1)
        {
            //cout<<"dfs "<<cur<<endl;
            dep[cur]=depcnt;
            itn[depcnt+1]=cur;nti[cur]=depcnt+1;
            pathtop[cur]=start;
            for(edge *tmp=h[cur];tmp;tmp=tmp->next)
            {
                if(!nti[tmp->v])
                {
                    pa[tmp->v]=cur;
                    maxson[cur]=tmp->v;
                    cur=tmp->v;
                    break;
                }
            }
            depcnt++;
            if(nti[cur])break;
        }
    }
    root=bt(1,n);
    scanf("%d",&q);
    for(int i=1;i<=q;i++)
    {
        scanf(" %c%d%d",&ch,&u,&v);
        if(ch=='Q')
            printf("%s",ans[qtree(u,v)==0].c_str());
        else
            ctree(u,v);
    }
    return 0;
}
