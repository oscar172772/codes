#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long LL;
const int MAXN=100100;
const LL Inf=27539297523874ll;
inline LL min3(LL x,LL y,LL z){return min(x,min(y,z));}
struct node
{
	LL num,size,lend,rend,maxx,minn,delta;
	node *lson,*rson,*pa;
}*rf,*root,pool[MAXN*2];
int n,m,x,pos,l,r,top;
char buf[256];
void update(node *x)
{
	x->size=1;
	x->lend=x->rend=x->num;
	x->maxx=x->minn=x->num;
	x->delta=Inf;
	if(x->lson)
	{
		x->size+=x->lson->size;
		x->lend=x->lson->lend;
		x->maxx=max(x->maxx,x->lson->maxx);
		x->minn=min(x->minn,x->lson->minn);
		x->delta=min3(x->delta,x->lson->delta,abs(x->lson->rend-x->num));
	}
	if(x->rson)
	{
		x->size+=x->rson->size;
		x->rend=x->rson->rend;
		x->maxx=max(x->maxx,x->rson->maxx);
		x->minn=min(x->minn,x->rson->minn);
		x->delta=min3(x->delta,x->rson->delta,abs(x->rson->lend-x->num));
	}
}
void rot(node *x)
{
	node *p=x->pa,*g=p->pa;
	if(p->lson==x)
	{
		if(g->lson==p)g->lson=x;
		else g->rson=x;
		x->pa=g;
		p->lson=x->rson;
		if(p->lson)p->lson->pa=p;
		x->rson=p;
		p->pa=x;
		if(root==p)root=x;
	}
	else
	{
		if(g->lson==p)g->lson=x;
		else g->rson=x;
		x->pa=g;
		p->rson=x->lson;
		if(p->rson)p->rson->pa=p;
		x->lson=p;
		p->pa=x;
		if(root==p)root=x;
	}
	update(p);
	update(x);
}
void Splay(node *x,node *target)
{
	while(x->pa!=target)
	{
		if(x->pa->pa==target)
		{
			rot(x);
		}
		else
		{
			node *p=x->pa;
			if((p->lson==x)^(p->pa->lson==p))
			{
				rot(x);
				rot(x);
			}
			else
			{
				rot(p);
				rot(x);
			}
		}
	}
}
void bt(int x)
{
	rf=&pool[top++];
	root=&pool[top++];
	rf->lson=root;
	root->pa=rf;
	root->num=x;
	update(root);
}//ÌØÅÐ n+1ºÍ 0 
node* Find(node *cur,int pos)
{
	if(pos==0||pos>cur->size)return 0;
	if(cur->lson)
	{
		if(cur->lson->size>=pos)return Find(cur->lson,pos);
		else if(cur->lson->size==pos-1)return cur;
		else return Find(cur->rson,pos-cur->lson->size-1);
	}
	else 
	{
		if(pos==1)return cur;
		else return Find(cur->rson,pos-1);
	}
}
void ins(int x,int pos)
{
	node *tmp=&pool[top++];
	tmp->num=x;
	update(tmp);
	if(pos==0)
	{
		node *tmp1=Find(root,pos+1);
		Splay(tmp1,rf);
		tmp1->lson=tmp;
		tmp->pa=tmp1;
		update(tmp1);
	}
	else if(pos==root->size)
	{
		node *tmp2=Find(root,pos);
		Splay(tmp2,rf);
		tmp2->rson=tmp;
		tmp->pa=tmp2;
		update(tmp2);
	}
	else
	{
		node *tmp1=Find(root,pos);
		node *tmp2=Find(root,pos+1);
		Splay(tmp1,rf);
		Splay(tmp2,root);
		tmp2->lson=tmp;
		tmp->pa=tmp2;
		update(tmp2);
		update(tmp1);
	}
}
void del(int pos)
{
	node *tmp1=Find(root,pos-1);
	node *tmp2=Find(root,pos+1);
	if(!tmp1)
	{
		Splay(tmp2,rf);
		tmp2->lson=NULL;
		update(tmp2);
	}
	else if(!tmp2)
	{
		Splay(tmp1,rf);
		tmp1->rson=NULL;
		update(tmp1);
	}
	else
	{
		Splay(tmp1,rf);
		Splay(tmp2,root);
		tmp2->lson=NULL;
		update(tmp2);
		update(tmp1);
	}
}
LL get_max(int l,int r)
{
	node *tmp1=Find(root,l-1);
	node *tmp2=Find(root,r+1);
	if(!tmp1&&!tmp2)
	{
		return root->maxx-root->minn;
	}
	else if(!tmp1)
	{
		Splay(tmp2,rf);
		return tmp2->lson->maxx-tmp2->lson->minn;
	}
	else if(!tmp2)
	{
		Splay(tmp1,rf);
		return tmp1->rson->maxx-tmp1->rson->minn;
	}
	else
	{
		Splay(tmp1,rf);
		Splay(tmp2,root);
		return tmp2->lson->maxx-tmp2->lson->minn;
	}
}
LL get_min(int l,int r)
{
	node *tmp1=Find(root,l-1);
	node *tmp2=Find(root,r+1);
	if(!tmp1&&!tmp2)
	{
		return root->delta;
	}
	else if(!tmp1)
	{
		Splay(tmp2,rf);
		return tmp2->lson->delta;
	}
	else if(!tmp2)
	{
		Splay(tmp1,rf);
		return tmp1->rson->delta;
	}
	else
	{
		Splay(tmp1,rf);
		Splay(tmp2,root);
		return tmp2->lson->delta;
	}
}
inline void merge(int x,int pos)
{
	del(pos);
	del(pos);
	ins(x,pos-1);
}
int main()
{
	//freopen("atom.in","r",stdin);
	//freopen("atom.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%d",&x);
	bt(x);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		ins(x,i-1);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",buf);
		switch(buf[1])
		{
			case 'e':
				scanf("%d%d",&pos,&x);
				merge(x,pos);
				break;
			case 'n':
				scanf("%d%d",&pos,&x);
				ins(x,pos);
				break;
			case 'a':
				scanf("%d%d",&l,&r);
				printf("%d\n",get_max(l,r));
				break;
			case 'i':
				scanf("%d%d",&l,&r);
				printf("%d\n",get_min(l,r));
				break;
			default:cout<<"-1\n";
		}
	}
	return 0;
}

