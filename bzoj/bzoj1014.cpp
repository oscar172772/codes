#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN=100010,SHIFT=29;
int pows[MAXN*2];
struct node
{
	int hash,siz,letter;
	node *pa,*lson,*rson;
}*root,*rf,pool[MAXN*2];
int top;
inline void ud(node *x)
{
	x->siz=1;
	x->hash=0;
	if(x->lson)
	{
		x->hash=x->lson->hash;
		x->siz+=x->lson->siz;
	}
	x->hash+=x->letter*pows[x->siz-1];
	if(x->rson)
	{
		x->hash+=x->rson->hash*pows[x->siz];
		x->siz+=x->rson->siz;
	}
}
char buf[MAXN*2];
node* build(int l,int r)
{
	int mid=(l+r)/2;
	node *tmp=&pool[top++];
	tmp->letter=buf[mid-1]-'a'+1;
	if(l!=mid)
	{
		tmp->lson=build(l,mid-1);
		tmp->lson->pa=tmp;
	}
	if(mid!=r)
	{
		tmp->rson=build(mid+1,r);
		tmp->rson->pa=tmp;
	}
	ud(tmp);
	return tmp;
}
inline void rot(node *x)
{
	node *p=x->pa;
	if(p->lson==x)
	{
		p->lson=x->rson;
		if(p->lson)p->lson->pa=p;
		if(p->pa->lson==p)p->pa->lson=x;
		else p->pa->rson=x;
		x->pa=p->pa;
		x->rson=p;
		p->pa=x;
		if(root==p)root=x;
	}
	else
	{
		p->rson=x->lson;
		if(p->rson)p->rson->pa=p;
		if(p->pa->lson==p)p->pa->lson=x;
		else p->pa->rson=x;
		x->pa=p->pa;
		x->lson=p;
		p->pa=x;
		if(root==p)root=x;
	}
	ud(p);
	ud(x);
}
inline void spaly(node *x,node *tar)
{
	while(x->pa!=tar)
	{
		if(x->pa->pa==tar)rot(x);
		else if((x->pa->pa->lson==x->pa)^(x->pa->lson==x))rot(x),rot(x);
		else rot(x->pa),rot(x);
	}
}
inline int siz(node *x){return x?x->siz:0;}
node* find(node *cur,int pos)
{
	if(siz(cur->lson)>=pos)return find(cur->lson,pos);
	else if(siz(cur->lson)==pos-1)return cur;
	else return find(cur->rson,pos-siz(cur->lson)-1);
}
int len,m;
inline void change(int pos,char letter)
{
	if(pos==1)
	{
		node *r=find(root,2);
		spaly(r,rf);
		r->lson->letter=letter-'a'+1;
		ud(r->lson);
		ud(r);
	}
	else if(pos==len)
	{
		node *l=find(root,len-1);
		spaly(l,rf);
		l->rson->letter=letter-'a'+1;
		ud(l->rson);
		ud(l);
	}
	else
	{
		node *l=find(root,pos-1),*r=find(root,pos+1);
		spaly(l,rf);
		spaly(r,l);
		r->lson->letter=letter-'a'+1;
		ud(r->lson);
		ud(r);
		ud(l);
	}
}
inline void ins(int pos,char letter)
{
	if(pos==0)
	{
		node *r=find(root,1);
		spaly(r,rf);
		r->lson=&pool[top++];
		r->lson->letter=letter-'a'+1;
		r->lson->pa=r;
		ud(r->lson);
		ud(r);
	}
	else if(pos==len)
	{
		node *l=find(root,len);
		spaly(l,rf);
		l->rson=&pool[top++];
		l->rson->letter=letter-'a'+1;
		l->rson->pa=l;
		ud(l->rson);
		ud(l);
	}
	else
	{
		node *l=find(root,pos),*r=find(root,pos+1);
		spaly(l,rf);
		spaly(r,l);
		r->lson=&pool[top++];
		r->lson->letter=letter-'a'+1;
		r->lson->pa=r;
		ud(r->lson);
		ud(r);
		ud(l);
	}
}
inline int q(int x,int y)
{
	//cout<<"q"<<x<<' '<<y<<endl;
	if(x==1)
	{
		if(y==len)
		{
			return root->hash;
		}
		else
		{
			node *r=find(root,y+1);//cout<<"\\ "<<char(r->letter+'a'-1)<<endl;
			spaly(r,rf);
			return r->lson->hash;
		}
	}
	else
	{
		node *l=find(root,x-1);//cout<<char(l->letter+'a'-1);
		spaly(l,rf);
		if(y==len)
		{
			//cout<<" \\"<<endl;
			return l->rson->hash;
		}
		else
		{
			node *r=find(root,y+1);//cout<<" "<<char(r->letter+'a'-1)<<endl;
			spaly(r,l);
			return r->lson->hash;
		}
	}
}
inline int query(int a,int b)
{
	if(a>b)swap(a,b);
	int l=0,r=len-b+1,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		int t1=q(a,a+mid-1),t2=q(b,b+mid-1);
		if(t1==t2)
		{
			//printf("(%d,%d)(%d)==(%d,%d)(%d)\n",a,a+mid-1,t1,b,b+mid-1,t2);
			l=mid;
		}
		else
		{
			//printf("(%d,%d)(%d)!=(%d,%d)(%d)\n",a,a+mid-1,t1,b,b+mid-1,t2);
			r=mid-1;
		}
	}
	return l;
}
void pnt(node *tmp){if(!tmp)return;cout<<"(";pnt(tmp->lson);cout<<char(tmp->letter+'a'-1)<<tmp->siz;pnt(tmp->rson);cout<<")";};
int main()
{
	//freopen("data.txt","r",stdin);
	//freopen("dump.txt","w",stdout);
	int cur=1;
	for(int i=0;i<=198789;i++)
	{
		pows[i]=cur;
		cur=cur*SHIFT;
	}
	scanf("%s",buf);
	rf=&pool[top++];
	len=strlen(buf);
	root=build(1,len);
	root->pa=rf;rf->lson=root;
	scanf("%d",&m);
	char type,x;
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf(" %c",&type);
		switch(type)
		{
			case 'Q':
				scanf("%d%d",&a,&b);
				//cout<<type<<' '<<a<<' '<<b<<endl;
				printf("%d\n",query(a,b));
				break;
			case 'R':
				scanf("%d %c",&a,&x);
				//cout<<type<<' '<<a<<' '<<x<<endl;
				change(a,x);
				break;
			case 'I':
				scanf("%d %c",&a,&x);
				//cout<<type<<' '<<a<<' '<<x<<endl;
				ins(a,x);
				len++;
				break;
		}
		//pnt(root);
	}
	return 0;
}
