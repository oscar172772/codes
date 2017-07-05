#include<iostream>
#include<cstdio>
using namespace std;
const int Inf=0x3f3f3f3f;
struct node
{
	int l,r,maxx;
	node *lson,*rson;
}*root,pool[2333333];
int top;
void bt()
{
	root=&pool[top++];
	root->l=-1000000001;
	root->r=1000000001;
	root->maxx=0;
}
int maxx(node *x){return x?x->maxx:0;}
void change(node *cur,int pos,int x)
{
	//cout<<"change("<<cur<<','<<pos<<','<<x<<")\n";
	if(cur->l==cur->r){cur->maxx=x;return;}
	int mid=(cur->l+cur->r)>>1;
	if(pos<=mid)
	{
		if(!(cur->lson))
		{
			cur->lson=&pool[top++];
			cur->lson->l=cur->l;
			cur->lson->r=mid;
			cur->lson->maxx=0;
		}
		change(cur->lson,pos,x);
	}
	else
	{
		//cout<<"case2\n";
		if(!(cur->rson))
		{
			cur->rson=&pool[top++];
			cur->rson->l=mid+1;
			cur->rson->r=cur->r;
			cur->rson->maxx=0;
		}
		change(cur->rson,pos,x);
	}
	cur->maxx=max(maxx(cur->lson),maxx(cur->rson));
}
int query(node *cur,int l,int r)
{
	if(l>r)return 0;
	if(!cur)return 0;
	if(cur->l==l&&cur->r==r)return cur->maxx;
	int mid=(cur->l+cur->r)>>1;
	if(mid>=r)return query(cur->lson,l,r);
	else if(mid+1<=l)return query(cur->rson,l,r);
	else return max(query(cur->lson,l,mid),query(cur->rson,mid+1,r));
}
struct node2
{
	int l,r,maxx;
	node2 *lson,*rson;
}*root2,pool2[2333333];
int top2;
void bt2()
{
	root2=&pool2[top2++];
	root2->l=-1000000001;
	root2->r=1000000001;
	root2->maxx=Inf;
}
int maxx(node2 *x){return x?x->maxx:Inf;}
void change2(node2 *cur,int pos,int x)
{
	if(cur->l==cur->r){cur->maxx=x;return;}
	int mid=(cur->l+cur->r)>>1;
	if(pos<=mid)
	{
		if(!(cur->lson))
		{
			cur->lson=&pool2[top2++];
			cur->lson->l=cur->l;
			cur->lson->r=mid;
			cur->lson->maxx=Inf;
		}
		change2(cur->lson,pos,x);
	}
	else
	{
		if(!(cur->rson))
		{
			cur->rson=&pool2[top2++];
			cur->rson->l=mid+1;
			cur->rson->r=cur->r;
			cur->rson->maxx=Inf;
		}
		change2(cur->rson,pos,x);
	}
	cur->maxx=max(maxx(cur->lson),maxx(cur->rson));
}
int query2(node2 *cur,int l,int r)
{
	if(l>r)return 0;
	if(!cur)return Inf;
	if(cur->l==l&&cur->r==r)return cur->maxx;
	int mid=(cur->l+cur->r)>>1;
	if(mid>=r)return query2(cur->lson,l,r);
	else if(mid+1<=l)return query2(cur->rson,l,r);
	else return max(query2(cur->lson,l,mid),query2(cur->rson,mid+1,r));
}
int main()
{
	int n,m,a,b,ra,rb,ans1,ans2,ans3,ans4,ans5,ans6,ans7,ans8;
	scanf("%d",&n);
	bt();bt2();
	while(n--)
	{
		scanf("%d%d",&a,&b);
		change(root,a,b);
		change2(root2,a,b);
	}
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&a,&b);
		ra=query(root,a,a);
		rb=query(root,b,b);
		if(rb==0&&ra==0)
		{
			printf("maybe\n");
			continue;
		}
		if(rb==0)
		{
			if(query(root,a+1,b-1)>=ra)printf("false\n");
			else printf("maybe\n");
			continue;
		}
		if(ra==0)
		{
			if(query(root,a+1,b-1)>=rb)printf("false\n");
			else printf("maybe\n");
			continue;
		}
		if(ra<rb||query(root,a+1,b-1)>=rb)printf("false\n");
		else if(query2(root2,a+1,b-1)>=rb)printf("maybe\n");
		else printf("true\n");
		/*ans1=(query(root,a,a)>=query(root,b,b)&&query(root,a+1,b-1)<query(root,b,b));
		ans2=(query2(root2,a,a)>=query(root,b,b)&&query(root,a+1,b-1)<query(root,b,b));
		ans3=(query(root,a,a)>=query2(root2,b,b)&&query(root,a+1,b-1)<query2(root2,b,b));
		ans4=(query2(root2,a,a)>=query2(root2,b,b)&&query(root,a+1,b-1)<query2(root2,b,b));
		ans5=(query(root,a,a)>=query(root,b,b)&&query2(root2,a+1,b-1)<query(root,b,b));
		ans6=(query2(root2,a,a)>=query(root,b,b)&&query2(root2,a+1,b-1)<query(root,b,b));
		ans7=(query(root,a,a)>=query2(root2,b,b)&&query2(root2,a+1,b-1)<query2(root2,b,b));
		ans8=(query2(root2,a,a)>=query2(root2,b,b)&&query2(root2,a+1,b-1)<query2(root2,b,b));
		printf("%s\n",res[ans1+ans2+ans3+ans4+ans5+ans6+ans7+ans8].c_str());*/
	}
	return 0;
}
