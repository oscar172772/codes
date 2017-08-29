#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define debug(str,...) printf("In function %s("str"), line %d\n",__FUNCTION__,##__VA_ARGS__,__LINE__)
using namespace std;
unsigned int cur;
int ran(){return (cur+=(cur<<2)+1)&0x7fffffff;}
struct node
{
	int letter,dup,ldup,size,shift,ran;
	node *lson,*rson;
}*root,pool[60000000];
int top;
typedef pair<node*,node*> pnn;
inline int size(node *x){return x?x->size:0;}
void printtree(node *x){if(!x)return;cout<<"(";if(x->lson)printtree(x->lson);for(int i=1;i<=x->dup;i++)cout<<char(x->letter+'a');cout<<x->size;if(x->rson)printtree(x->rson);cout<<")";}
node *nn(node *x)
{
	//if(top%100000==0)cout<<top<<endl;
	node *tmp=&pool[top++];
	tmp->letter=x->letter;
	tmp->dup=x->dup;
	tmp->lson=x->lson;
	tmp->rson=x->rson;
	tmp->shift=x->shift;
	tmp->ldup=x->ldup;
	tmp->size=x->size;
	tmp->ran=x->ran;
	return tmp;
}
inline void ud(node *x)
{
	x->size=x->dup;
	if(x->lson)x->size+=x->lson->size;
	if(x->rson)x->size+=x->rson->size;
}
inline void fa_lazy(node *x)
{
	//debug("%d",size(x));
	if(!x)return;
	if(x->lson)x->lson=nn(x->lson);
	if(x->rson)x->rson=nn(x->rson);
	if(x->shift)
	{
		if(x->lson)
		{
			x->lson->letter=(x->lson->letter+x->shift)%26;
			x->lson->shift=(x->lson->shift+x->shift)%26;
		}
		if(x->rson)
		{
			x->rson->letter=(x->rson->letter+x->shift)%26;
			x->rson->shift=(x->rson->shift+x->shift)%26;
		}
		x->shift=0;
	}
	if(x->ldup!=1)
	{
		if(x->lson)
		{
			x->lson->size*=x->ldup;
			x->lson->ldup*=x->ldup;
			x->lson->dup*=x->ldup;
		}
		if(x->rson)
		{
			x->rson->size*=x->ldup;
			x->rson->ldup*=x->ldup;
			x->rson->dup*=x->ldup;
		}
		x->ldup=1;
	}
	/*
	x->size=x->dup;
	if(x->lson)x->size+=x->lson->size;
	if(x->rson)x->size+=x->rson->size;
	*/
}
node *merge(node *a,node *b)
{
	if(!a)return b;
	if(!b)return a;
	if(a->ran<b->ran)
	{
		fa_lazy(a);
		a->rson=merge(a->rson,b);
		ud(a);
		return a;
	}
	else
	{
		fa_lazy(b);
		b->lson=merge(a,b->lson);
		ud(b);
		return b;
	}
}
pnn splix(node *x,int lsize)
{
	fa_lazy(x);
	node *tmp=nn(x);
	tmp->dup=lsize;
	x->dup-=lsize;
	tmp->rson=0;
	x->lson=0;
	ud(tmp);
	ud(x);
	return pnn(tmp,x);
}
//<=k->left;>k->right
pnn split(node *x,int k)
{
	//debug("%d,%d",size(x),k);
	fa_lazy(x);
	//printtree(x);cout<<endl;
	if(k<size(x->lson))
	{
		//cout<<"leftson\n";
		pnn _;
		if(x->lson)
		{
			_=split(x->lson,k);
			x->lson=_.second;
		}
		ud(x);
		return pnn(_.first,x);
	}
	else if(k<=size(x->lson)+x->dup)
	{
		if(k==size(x->lson))
		{
			//cout<<"leftcut\n";
			node *ls=x->lson;
			x->lson=0;
			ud(x);
			return pnn(ls,x);
		}
		if(k==size(x->lson)+x->dup)
		{
			//cout<<"rightcut\n";
			node *rs=x->rson;
			x->rson=0;
			ud(x);
			return pnn(x,rs);
		}
		//cout<<"splix\n";
		return splix(x,k-size(x->lson));
	}
	else
	{
		//cout<<"rightson\n";
		pnn _;
		if(x->rson)
		{
			_=split(x->rson,k-size(x->lson)-x->dup);
			x->rson=_.first;
		}
		ud(x);
		return pnn(x,_.second);
	}
}
void duplicate1(int l,int r)
{
	//debug("%d,%d",l,r);
	pnn _=split(root,r);
	//printtree(_.first);cout<<endl;printtree(_.second);cout<<endl;
	pnn __=split(_.first,l-1);
	//printtree(__.first);cout<<endl;printtree(__.second);cout<<endl;
	node *tmp=nn(__.second);
	//printtree(tmp);cout<<endl;
	//system("pause");
	tmp->ldup*=2;
	tmp->dup*=2;
	tmp->size*=2;
	root=merge(__.first,merge(tmp,_.second));
}
void duplicate2(int l,int r)
{
	pnn _=split(root,r);
	pnn __=split(_.first,l-1);
	node *tmp=nn(__.second);
	root=merge(merge(__.first,tmp),merge(__.second,_.second));
}
void shiftl(int l,int r)
{
	pnn _=split(root,r);
	pnn __=split(_.first,l-1);
	node *tmp=nn(__.second);
	tmp->shift=(tmp->shift+1)%26;
	tmp->letter=(tmp->letter+1)%26;
	root=merge(__.first,merge(tmp,_.second));
}
void del(int l,int r)
{
	pnn _=split(root,r);
	pnn __=split(_.first,l-1);
	root=merge(__.first,_.second);
}
char str[1000010];
int end;
void getstr(node *x)
{
    fa_lazy(x);
    if(x->lson)getstr(x->lson);
    for(int i=1;i<=x->dup;i++)str[++end]=x->letter+'a';
    if(x->rson)getstr(x->rson);
}
void getstr()
{
	end=0;
	getstr(root);
	str[end+1]=0;
}
node* build(int l,int r)
{
	if(l>r)return 0;
	node *tmp=&pool[top++];
	int mid=(l+r)/2;
	tmp->letter=str[mid]-'a';
	tmp->dup=1;
	tmp->ldup=1;
	tmp->shift=0;
	tmp->ran=ran();
	if(l!=r)
	{
		tmp->lson=build(l,mid-1);
		tmp->rson=build(mid+1,r);
	}
	else tmp->lson=tmp->rson=0;
	ud(tmp);
	return tmp;
}
void rebuild()
{
    getstr();
    top=0;
    root=build(1,end);
}
int n,type,l,r;
int main()
{
	//freopen("way.in","r",stdin);
	//freopen("way.out","w",stdout);
	scanf("%s",str+1);
	scanf("%d",&n);
	int B=n/3/log2(n);
	root=build(1,strlen(str+1));
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(cnt>=B){rebuild();cnt=0;}
	    scanf("%d%d%d",&type,&l,&r);
	    if(type==1)
	    {
			duplicate1(l,r);
		}
	    else if(type==2)
	    {
			duplicate2(l,r);
		}
		else if(type==3)
		{
			shiftl(l,r);
		}
		else
		{
			del(l,r);
		}
		cnt++;
		//getstr();
		//printf("%s\n",str+1);
	}
	getstr();
	printf("%s\n",str+1);
	//system("pause");
	return 0;
}
