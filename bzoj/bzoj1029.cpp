#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=150010;
struct node
{
	int l,r,sum,lazy;
	node *lson,*rson;
}*root,pool[MAXN*3];
int top;
int arr[MAXN];
node *bt(int l,int r)
{
	node *tmp=&pool[top++];
	tmp->l=l;tmp->r=r;
	if(l!=r)
	{
		int mid=(l+r)/2;
		tmp->lson=bt(l,mid);
		tmp->rson=bt(mid+1,r);
		tmp->sum=tmp->lson->sum+tmp->rson->sum;
	}
	else tmp->sum=arr[l];
	return tmp;
}
int query(node *cur,int l,int r)
{
	if(cur->l==l&&cur->r==r)return cur->sum;
	if(cur->sum==0)return 0;
	if(cur->lson->r>=r)return query(cur->lson,l,r);
	if(cur->rson->l<=l)return query(cur->rson,l,r);
	return query(cur->lson,l,cur->lson->r)+query(cur->rson,cur->rson->l,r);
}
void change(node *cur,int pos,int num)
{
	//cout<<"change["<<cur->l<<','<<cur->r<<"],"<<pos<<','<<num<<endl;
	if(cur->l==cur->r||(cur->r==pos&&cur->sum==num))
	{
		cur->sum-=num;
		return;
	}
	if(pos<=cur->lson->r)change(cur->lson,pos,num);
	else
	{
		int tmp=query(cur->rson,cur->rson->l,pos);
		if(tmp>=num)change(cur->rson,pos,num);
		else
		{
			change(cur->rson,pos,tmp);
			change(cur->lson,cur->lson->r,num-tmp);
		}
	}
	cur->sum-=num;//cur->sum=cur->lson->sum+cur->rson->sum;//为什么会错啊 
}
struct atom
{
	int len,end,id;
	inline bool operator<(const atom &x)const{return len<x.len;}
}b[MAXN];
inline bool cmp(const atom &x,const atom &y){return x.end<y.end;}
int n,ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&b[i].len,&b[i].end);
	}
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		arr[i]=b[i].end-b[i-1].end;
		b[i].id=i;
	}
	root=bt(1,n);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		int tmp=query(root,1,b[i].id);
		//cout<<i<<':'<<b[i].id<<' '<<tmp<<endl;
		if(tmp>=b[i].len)
		{
			change(root,b[i].id,b[i].len);
			ans++;
			//cout<<b[i].len<<' '<<b[i].end<<endl;
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXN=150010;
struct atom
{
	int len,end;
	inline bool operator<(const atom &x)const{return len<x.len;}
}b[MAXN];
inline bool cmp(const atom &x,const atom &y){return x.end<y.end;}
int n,ans;
priority_queue<atom> pq;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&b[i].len,&b[i].end);
	}
	sort(b+1,b+n+1,cmp);
	int usedtime=0;
	for(int i=1;i<=n;i++)
	{
		if(usedtime+b[i].len>b[i].end)
		{
			if((!pq.empty())&&pq.top().len>b[i].len)
			{
				usedtime-=pq.top().len;
				pq.pop();
				pq.push(b[i]);
				usedtime+=b[i].len;
			}
		}
		else
		{
			pq.push(b[i]);
			usedtime+=b[i].len;
			++ans;
		}
	}
	//while(!pq.empty())
	//{
	//	printf("%d %d\n",pq.top().len,pq.top().end);
	//	pq.pop();
	//}
	printf("%d\n",ans);
	return 0;
}
*/
