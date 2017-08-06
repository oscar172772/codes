#include<iostream>
#include<cstdio>
using namespace std;
struct node
{
	int c[5];//lu,ld,ru,rd
	int l,r;
	node *lson,*rson;
}*root,pool[233333];
int top;
int upper[122222],lower[122222],vertical[122222];
int pa[10];
int find(int x){return pa[x]!=x?pa[x]=find(pa[x]):x;}
inline void onion(int x,int y)
{
	int px=find(x),py=find(y);
	if(px<py)pa[py]=px;
	else pa[px]=py;
}
inline void ud(node *x)
{
	//cout<<"ud("<<x->l<<','<<x->r<<")\n";
	if(x->l!=x->r)
	{
		for(int i=1;i<=4;i++)
		{
			pa[i]=x->lson->c[i];
			pa[i+4]=x->rson->c[i]+4;
		}
		if(upper[x->lson->r])onion(3,5);
		if(lower[x->lson->r])onion(4,6);
		x->c[1]=find(1);x->c[2]=find(2);x->c[3]=find(7);x->c[4]=find(8);
		if(x->c[4]>=3)
		{
			if(x->c[4]==x->c[3])x->c[4]=3;
			else x->c[4]=4;
		}
		if(x->c[3]>=3)x->c[3]=3;
	}
	else
	{
		if(vertical[x->l])
		{
			x->c[1]=x->c[2]=x->c[3]=x->c[4]=1;
		}
		else
		{
			x->c[1]=x->c[3]=1;
			x->c[2]=x->c[4]=2;
		}
	}
}
node* build(int l,int r)
{
	node *tmp=&pool[top++];
	tmp->l=l;
	tmp->r=r;
	if(l!=r)
	{
		int mid=(l+r)/2;
		tmp->lson=build(l,mid);
		tmp->rson=build(mid+1,r);
	}
	ud(tmp);
	return tmp;
}
void changev(node *cur,int pos)
{
	if(cur->l!=cur->r)
	{
		if(cur->lson->r>=pos)changev(cur->lson,pos);
		else changev(cur->rson,pos);
	}
	ud(cur);
}
void changeh(node *cur,int pos)
{
	if(cur->lson->r!=pos)
	{
		if(cur->lson->r>pos)changeh(cur->lson,pos);
		else changeh(cur->rson,pos);
	}
	ud(cur);
}
void query(node *cur,int a[],int l,int r)
{
//	cout<<"q"<<l<<' '<<r<<' '<<cur->l<<' '<<cur->r<<endl;
	if(cur->l==l&&cur->r==r)
	{
		for(int i=1;i<=4;i++)
			a[i]=cur->c[i];
	}
	else if(cur->lson->r>=r)query(cur->lson,a,l,r);
	else if(cur->rson->l<=l)query(cur->rson,a,l,r);
	else
	{
		int tmp1[5],tmp2[5];
		query(cur->lson,tmp1,l,cur->lson->r);
		query(cur->rson,tmp2,cur->rson->l,r);
		for(int i=1;i<=4;i++)
		{
			pa[i]=tmp1[i];
			pa[i+4]=tmp2[i]+4;
		}
		if(upper[cur->lson->r])onion(3,5);
		if(lower[cur->lson->r])onion(4,6);
		a[1]=find(1);a[2]=find(2);a[3]=find(7);a[4]=find(8);
		if(a[4]>=3)
		{
			if(a[4]==a[3])a[4]=3;
			else a[4]=4;
		}
		if(a[3]>=3)a[3]=3;
	}
}
int n;
char buf[20];
int arr[5],le[5],ri[5],a,b,c,d,type;
void pnt(node *x)
{
	cout<<"(";
	if(x->lson)pnt(x->lson);
	cout<<x->c[1]<<','<<x->c[2]<<','<<x->c[3]<<','<<x->c[4];
	if(x->rson)pnt(x->rson);
	cout<<")";
}
int main()
{
	scanf("%d",&n);
	root=build(1,n);
	while(buf[0]!='E')
	{
		scanf(" %s",buf);
		if(buf[0]=='A')
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			if(b>d)
			{
				swap(a,c);
				swap(b,d);
			}
			query(root,le,1,b);
			query(root,arr,b,d);
			query(root,ri,d,n);
			/*
			ll=a,rr=c+2;
			if(arr[ll]==arr[rr])printf("Y\n");
			else printf("N\n");
			*/
			if(a==1&&c==1)
			{
				if(arr[1]==arr[3]||(le[3]==le[4]&&arr[2]==arr[3])||(arr[1]==arr[4]&&ri[1]==ri[2])||(le[3]==le[4]&&arr[2]==arr[4]&&ri[1]==ri[2]))printf("Y\n");
				else printf("N\n");
			}
			else if(a==2&&c==2)
			{
				if(arr[2]==arr[4]||(le[3]==le[4]&&arr[1]==arr[4])||(arr[2]==arr[3]&&ri[1]==ri[2])||(le[3]==le[4]&&arr[1]==arr[3]&&ri[1]==ri[2]))printf("Y\n");
				else printf("N\n");
			}
			else if(a==1&&c==2)
			{
				if(arr[1]==arr[4]||(le[3]==le[4]&&arr[2]==arr[4])||(arr[1]==arr[3]&&ri[1]==ri[2])||(le[3]==le[4]&&arr[2]==arr[4])||(ri[1]==ri[2]&&arr[1]==arr[3]))printf("Y\n");
				else printf("N\n");
			}
			else if(a==2&&c==1)
			{
				if(arr[2]==arr[3]||(le[3]==le[4]&&arr[1]==arr[3])||(arr[2]==arr[4]&&ri[1]==ri[2])||(le[3]==le[4]&&arr[1]==arr[3])||(ri[1]==ri[2]&&arr[2]==arr[4]))printf("Y\n");
				else printf("N\n");
			}
			else while(1);
		}
		else if(buf[0]!='E')
		{
			type=(buf[0]=='O');
			scanf("%d%d%d%d",&a,&b,&c,&d);
			if(a==c)
			{
				if(a==1)upper[min(b,d)]=type;
				else if(a==2) lower[min(b,d)]=type;
				else while(1);
				changeh(root,min(b,d));
			}
			else if(a+c==3)
			{
				vertical[b]=type;
				changev(root,b);
			}
			else while(1);
		}
		/*
		pnt(root);cout<<endl;
		for(int i=1;i<n;i++)
			cout<<lower[i]<<' ';
		cout<<endl;
		for(int i=1;i<n;i++)
			cout<<upper[i]<<' ';
		cout<<endl;
		for(int i=1;i<=n;i++)
			cout<<vertical[i]<<' ';
		cout<<endl;
		*/
	}
	return 0;
}
