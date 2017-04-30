#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
const int MAXN=80010;
struct node
{
    int v,len;
    node *next;
}pool[MAXN*100], *h[MAXN];
struct ask
{
    int v,k;
    ask *next;
}poola[MAXN*2], *ha[MAXN];
int n,m,k,pa[MAXN],ltr[MAXN],top=0,topa=0,ans[MAXN],flag[MAXN];//0:never,1:processing,2:finished
int find(int c){return pa[c]?pa[c]=find(pa[c]):c;}
inline void addedge(int u,int v,int len)
{
    node *tmp=&pool[++top];
    tmp->v=v;
    tmp->len=len;
    tmp->next=h[u];
    h[u]=tmp;
    //cout<<"added: "<<u<<' '<<v<<' '<<len<<endl;
    /*for(int i=1;i<=n;i++)
    {
        cout<<i<<" is connected to: ";
        if(h[i])
        {
            for(node *tmp2=h[i];tmp2;tmp2=tmp2->next)
            {
                cout<<tmp2->v<<" ";
            }
        }
        cout<<endl;
    }*/
}
inline void addedgea(int u,int v,int k)
{
    ask *tmp=&poola[++topa];
    tmp->v=v;
    tmp->k=k;
    tmp->next=ha[u];
    ha[u]=tmp;
}
void dfs(int c,int ltr1)
{
    //cout<<"DFSing... "<<c<<endl;
    if(flag[c]==1)
    {
        //cout<<c<<" already searched!\n";
        return;
    }
    flag[c]=1;
    ltr[c]=ltr1;
    for(ask *tmp=ha[c];tmp;tmp=tmp->next)
    {
        if(flag[tmp->v])
        {
            int tmp2=find(tmp->v);
            ans[tmp->k]=(ltr[c]-ltr[tmp2])+(ltr[tmp->v]-ltr[tmp2]);
        }
        else
        {
            ans[tmp->k]=-1;
        }
    }
    for(node *tmp=h[c];tmp;tmp=tmp->next)
    {
        //ltr[tmp->v]=ltr[c]+tmp->len;
        dfs(tmp->v,ltr1+tmp->len);
        int px=find(tmp->v),py=find(c);
        if(px>py)
            pa[px]=py;
        else if(px<py)
            pa[py]=px;
    }
    //flag[c]=2;
    //cout<<"Returning from DFS("<<c<<");\n";
}

inline void init()
{
    int f1,f2,l;
    char d;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>f1>>f2>>l>>d;
        //cout<<f1<<f2<<l<<(char)(d)<<endl;
        addedge(f1,f2,l);
        addedge(f2,f1,l);
    }
    cin>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>f1>>f2;
        addedgea(f1,f2,i);
        addedgea(f2,f1,i);
        /*ask[i][1]=f1;
        ask[i][2]=f2;*/
    }
}

int main()
{
    init();
    /*for(int i=1;i<=n;i++)
    {
        cout<<i<<" is connected to: ";
        if(h[i])
            for(node *tmp=h[i];tmp;tmp=tmp->next)
            {
                cout<<tmp->v<<" ";
            }
        cout<<endl;
    }*/
    for(int i=1;i<=n;i++)
    {
        if(!flag[i])
            dfs(i,0);
    }
    /*for(int j=1;j<=n;j++)
        {
            cout<<ltr[j]<<' ';
        }
        cout<<endl;*/
    for(int i=1;i<=k;i++)cout<<ans[i]<<endl;
    //system("pause");
    return 0;
}
