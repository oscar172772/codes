#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=20000,Inf=0x3f3f3f3f;
struct edge
{
	int v,len,id;
	edge *next;
}*h[MAXN],epool[MAXN*2];
int etop;
inline void addedge(int u,int v,int len,int id)
{
    //cout<<"addedge("<<u<<','<<v<<','<<len<<','<<id<<")\n";
	edge *tmp=&epool[etop++];tmp->v=v;tmp->len=len;tmp->id=id;tmp->next=h[u];h[u]=tmp;
	edge *pmt=&epool[etop++];pmt->v=u;pmt->len=len;pmt->id=id;pmt->next=h[v];h[v]=pmt;
}
struct node
{
    int l,r,maxx;
    node *lson,*rson;
}*root,pool[MAXN*4];
int top;
/*debug
inline void disp(int a[],int size,string name="")
{
	cout<<name;
	for(int i=1;i<=size;i++)cout<<' '<<a[i];
	cout<<endl;
}
inline void debug(string name,int u)
{
	cout<<name<<'('<<u<<')'<<endl;
}
inline void debug(string name,int u,int v)
{
    cout<<name<<'('<<u<<','<<v<<')'<<endl;
}
//end_of_debug*/
//segment_tree
int len[MAXN],ltop;
inline node* bt(int l,int r)
{
    node *tmp=&pool[top++];
    tmp->l=l;tmp->r=r;
    if(l==r)
    {
        tmp->maxx=len[++ltop];//scanf("%lld",&tmp->maxx);
    }
    else
    {
        int m=(l+r)>>1;
        tmp->lson=bt(l,m);
        tmp->rson=bt(m+1,r);
        tmp->maxx=max(tmp->lson->maxx,tmp->rson->maxx);
    }
    return tmp;
}
inline void change(node *cur,int pos,int d)
{
    if(cur->l==pos&&cur->r==pos)
    {
        cur->maxx=d;
    }
    else
    {
        if(pos<=cur->lson->r)
        {
            change(cur->lson,pos,d);
        }
        else if(pos>=cur->rson->l)
        {
            change(cur->rson,pos,d);
        }
        else
        {
            change(cur->lson,pos,d);
            change(cur->rson,pos,d);
        }
        cur->maxx=max(cur->lson->maxx,cur->rson->maxx);
    }
}
int query(node *cur,int l,int r)
{
    if(cur->l==l&&cur->r==r)
    {
        return cur->maxx;
    }
    else
    {
        if(r<=cur->lson->r)
        {
            return query(cur->lson,l,r);
        }
        else if(l>=cur->rson->l)
        {
            return query(cur->rson,l,r);
        }
        else
        {
            return max(query(cur->lson,l,cur->lson->r),
					   query(cur->rson,cur->rson->l,r));
        }
    }
}
//HLD
int dep[MAXN],siz[MAXN],pathpa[MAXN],pathtop[MAXN],paedge[MAXN],edgeid[MAXN];
edge *maxsonedge[MAXN];
void dfs1(int u)
{
	//debug("dfs1",u);
	siz[u]=1;
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if(dep[tmp->v]==-1)
		{
			dep[tmp->v]=dep[u]+1;
			dfs1(tmp->v);
			if( (!maxsonedge[u]) || siz[tmp->v]>siz[maxsonedge[u]->v])
			{
				maxsonedge[u]=tmp;
			}
			siz[u]+=siz[tmp->v];
		}
	}
}
int currenttop;
void dfs2(int u)
{
	//debug("dfs2",u);
	pathtop[u]=currenttop;
	edge *mse=maxsonedge[u];
	if(mse)
	{
        pathpa[mse->v]=pathpa[u];
		len[paedge[mse->v]=++ltop]=mse->len;//possibly error
		edgeid[mse->id]=ltop;
		dfs2(mse->v);
	}
	for(edge *tmp=h[u];tmp;tmp=tmp->next)
	{
		if(dep[tmp->v]==dep[u]+1&&tmp!=mse)
		{
			currenttop=tmp->v;
			pathpa[tmp->v]=u;
			len[paedge[tmp->v]=++ltop]=tmp->len;//possibly error
			edgeid[tmp->id]=ltop;
			dfs2(tmp->v);
		}
	}
}
void ctree(int pos,int d)
{
	//debug("ctree",pos);
	change(root,edgeid[pos],d);
}
int qtree(int a,int b)
{
    //debug("qtree",a,b);
	int cura=a,curb=b,ans=0;
	while(pathtop[cura]!=pathtop[curb])
	{
        //debug("qtree-jump",cura,curb);
		if((!pathpa[curb])||(dep[pathtop[cura]]>dep[pathtop[curb]]&&pathpa[cura]))
		{
			ans=max(ans,query(root,paedge[pathtop[cura]],paedge[cura]));
			cura=pathpa[cura];
		}
		else
		{
			ans=max(ans,query(root,paedge[pathtop[curb]],paedge[curb]));
			curb=pathpa[curb];
		}
	}
	//debug("qtree-same_chain",cura,curb);
	if(dep[cura]>dep[curb])swap(cura,curb);
	if(dep[cura]!=dep[curb])
		ans=max(ans,query(root,paedge[cura]+1,paedge[curb]));
	return ans;
}
//main
int main()
{
    /*
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    //*/
    int t,n,l,r,d;
    char buf[20];
    scanf("%d",&t);
    while(t--)
    {
	    bool flag=1;
	    scanf("%d",&n);
	    ltop=top=etop=0;
    	memset(h,0,sizeof(h));
    	memset(len,0,sizeof(len));
		memset(dep,-1,sizeof(dep));
		memset(siz,0,sizeof(siz));
		memset(maxsonedge,0,sizeof(maxsonedge));
		//memset(maxsonlen,0,sizeof(maxsonlen));
		memset(pathpa,0,sizeof(pathpa));
		memset(pathtop,0,sizeof(pathtop));
		memset(paedge,0,sizeof(paedge));
		memset(edgeid,0,sizeof(edgeid));
    	//input(don't forget ID)
    	for(int i=1;i<n;i++)
    	{
    		scanf("%d%d%d",&l,&r,&d);
    		addedge(l,r,d,i);
		}
		dep[1]=0;
		dfs1(1);
		currenttop=1;
		dfs2(1);
		/*
		disp(dep,n,"dep");
		disp(siz,n,"siz");
		//disp(maxson,n,"maxson");//edge*
		disp(pathpa,n,"pathpa");
		disp(pathtop,n,"pathtop");
		disp(paedge,n,"paedge");
		disp(len,n-1,"len");
		disp(edgeid,n-1,"id->edge");
		//*/
    	ltop=0;
    	root=bt(1,n-1);
    	while(flag)
    	{
    	    scanf(" %s",buf);
    	    switch(buf[0])
    	    {
    	        case 'Q':
    	            scanf(" %d %d",&l,&r);
    	            printf("%d\n",qtree(l,r));
    	            break;
        	    case 'C':
        	        scanf(" %d %d",&l,&d);
        	        ctree(l,d);
        	        break;
        	    case 'D':
        		    flag=false;
           		 	break;
        	}
    	}
	}
    return 0;
}
