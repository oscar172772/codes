#include<iostream>
#include<cstdio>
using namespace std;
struct node
{
	int l,r,lmax,rmax,maxx,lazy;
	node *lson,*rson;
}*root,pool[300000];
int top;
int n,m,type,len,l;
node* bt(int l,int r)
{
	node *tmp=&pool[top++];
	tmp->l=l;tmp->r=r;
	tmp->lmax=tmp->rmax=tmp->maxx=r-l+1;
	tmp->lazy=-1;
	if(l!=r)
	{
		int m=(l+r)/2;
		tmp->lson=bt(l,m);
		tmp->rson=bt(m+1,r);
	}
	return tmp;
}
inline void fa_lazy(node *cur)
{
	if(cur->lazy!=-1)
	{
		if(cur->lson)
		{
			cur->lson->lazy=cur->lazy;
			if(cur->lazy)
			{
				cur->lson->lmax=cur->lson->rmax=cur->lson->maxx=0;
			}
			else
			{
				cur->lson->lmax=cur->lson->rmax=cur->lson->maxx=cur->lson->r-cur->lson->l+1;
			}
		}
		if(cur->rson)
		{
			cur->rson->lazy=cur->lazy;
			if(cur->lazy)
			{
				cur->rson->lmax=cur->rson->rmax=cur->rson->maxx=0;
			}
			else
			{
				cur->rson->lmax=cur->rson->rmax=cur->rson->maxx=cur->rson->r-cur->rson->l+1;
			}
		}
		cur->lazy=-1;
	}
}
void change(node *cur,int l,int r,int type)
{
	//cout<<"change("<<cur->l<<','<<cur->r<<','<<l<<','<<r<<")\n";
	if(cur->l==l&&cur->r==r)
	{
		cur->lazy=type;
		if(type)
		{
			cur->lmax=cur->rmax=cur->maxx=0;
		}
		else
		{
			cur->lmax=cur->rmax=cur->maxx=r-l+1;
		}
		return;
	}
	fa_lazy(cur);
	if(cur->lson->r>=r)change(cur->lson,l,r,type);
	else if(cur->rson->l<=l)change(cur->rson,l,r,type);
	else
	{
		change(cur->lson,l,cur->lson->r,type);
		change(cur->rson,cur->rson->l,r,type);
	}
	
//	fa_lazy(cur->lson);
//	fa_lazy(cur->rson);
	
	if(cur->lson->lmax==cur->lson->r-cur->lson->l+1)cur->lmax=cur->lson->lmax+cur->rson->lmax;
	else cur->lmax=cur->lson->lmax;
	if(cur->rson->rmax==cur->rson->r-cur->rson->l+1)
	{
		cur->rmax=cur->rson->rmax+cur->lson->rmax;
	}
	else
	{
		cur->rmax=cur->rson->rmax;
	}
	cur->maxx=max(cur->lson->maxx,cur->rson->maxx);
	cur->maxx=max(cur->maxx,cur->lson->rmax+cur->rson->lmax);
}
inline int query(node *cur,int len)
{
	//cout<<"query("<<cur->l<<','<<cur->r<<','<<len<<")\n";
	int tmp=0;
	fa_lazy(cur);
	fa_lazy(cur->lson);
	fa_lazy(cur->rson);
	if(cur->lson->maxx>=len)return query(cur->lson,len);
	else if(cur->lson->rmax+cur->rson->lmax>=len)
	{
		tmp=cur->lson->r-cur->lson->rmax+1;
		change(root,tmp,tmp+len-1,1);
	}
	else if(cur->rson->maxx>=len) return query(cur->rson,len);
	return tmp;
}
void pntree(node *cur)
{
	if(cur->lson)pntree(cur->lson);
	cout<<'('<<cur->l<<','<<cur->r<<','<<cur->maxx<<','<<cur->lmax<<','<<cur->rmax<<','<<cur->lazy<<')';
	if(cur->rson)pntree(cur->rson);
}
int main()
{
	scanf("%d%d",&n,&m);
	root=bt(1,n);
	while(m--)
	{
		scanf("%d",&type);
		if(type==1)
		{
			scanf("%d",&len);
			printf("%d\n",query(root,len));
		}
		else
		{
			scanf("%d%d",&l,&len);
			change(root,l,l+len-1,0);
		}
		//pntree(root);cout<<endl;
	}
	return 0;
}
