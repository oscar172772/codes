#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100010;
struct node
{
	int l,r,cnt;
	long long sum;
	node *lson,*rson;
}*root[MAXN*2],pool[MAXN*100],*empty=&pool[MAXN*100-1];
int top;
int lsh[MAXN],hsl[MAXN*100];
node* nn(node *cp)
{
	node *tmp=&pool[top++];
	tmp->l=cp->l;
	tmp->r=cp->r;
	tmp->lson=cp->lson;
	tmp->rson=cp->rson;
	tmp->sum=cp->sum;
	tmp->cnt=cp->cnt;
	return tmp;
}
node* build(int l,int r)
{
	node *tmp=nn(empty);
	tmp->l=l;tmp->r=r;tmp->sum=0;tmp->cnt=0;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		tmp->lson=build(l,mid);
		tmp->rson=build(mid+1,r);
	}
	return tmp;
}
node* change(node *pre,int pos,int type)
{
	node *tmp=nn(pre);
	if(tmp->l==tmp->r)
	{
		tmp->sum+=lsh[tmp->l]*type;
		tmp->cnt+=type;
	}
	else
	{
		if(tmp->lson->r>=pos)tmp->lson=change(pre->lson,pos,type);
		else tmp->rson=change(pre->rson,pos,type);
		tmp->sum=tmp->lson->sum+tmp->rson->sum;
		tmp->cnt=tmp->lson->cnt+tmp->rson->cnt;
	}
	return tmp;
}
long long query(node *cur,int k)
{
	//cout<<"query "<<cur->l<<' '<<cur->r<<' '<<cur->cnt<<' '<<cur->sum<<' '<<k<<endl; 
	if(cur->l==cur->r)
	{
		return cur->sum/cur->cnt*k;
	}
	if(cur->cnt<=k)return cur->sum;
	else if(k<=cur->lson->cnt)return query(cur->lson,k);
	else return cur->lson->sum+query(cur->rson,k-cur->lson->cnt);
}
struct atom
{
	int p,time,type,id;
	inline bool operator<(const atom &a)const{return p<a.p;}
}arr[MAXN*2];
inline bool cmp(const atom &a,const atom &b){return a.time<b.time;}
int top2;
int n,m;
int endver[MAXN],top3;
void pnt(node *x)
{
	cout<<"(";
	if(x->lson)pnt(x->lson);
	cout<<x->cnt<<','<<x->sum;
	if(x->rson)pnt(x->rson);
	cout<<")"; 
}
int main()
{
	//freopen("data.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	long long a,b,c;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		top2++;
		arr[top2].p=c;
		arr[top2].time=a;
		arr[top2].type=1;
		top2++;
		arr[top2].p=c;
		arr[top2].time=b+1;
		arr[top2].type=-1;
	}
	sort(arr+1,arr+top2+1);
	int cnt=0;
	for(int i=1;i<=top2;i++)
	{
		/*
		if(arr[i].type==1)
		{
			cnt++;
			lsh[cnt]=arr[i].p;
			hsl[arr[i].p]=cnt;
			arr[i].id=cnt;
		}
		else
		{
			arr[i].id=hsl[arr[i].p];
		}
		/*/
		if(arr[i].p!=arr[i-1].p)
			cnt++;
		lsh[cnt]=arr[i].p;
		arr[i].id=cnt;
		//*/
	}
	sort(arr+1,arr+top2+1,cmp);
	root[0]=build(1,cnt);
	for(int i=1;i<=top2;i++)
	{
		if(arr[i].time!=arr[i-1].time)
			while(top3<arr[i].time)
				endver[top3++]=i-1;
		root[i]=change(root[i-1],arr[i].id,arr[i].type);
	}
	while(top3<m+1)endver[top3++]=top2;
	//for(int i=0;i<=top2;i++)pnt(root[i]),cout<<endl;cout<<endl;
	//for(int i=0;i<=n+1;i++)pnt(root[endver[i]]),cout<<endl;
	long long x,pre=1,k;
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&x,&a,&b,&c);
		k=1+(a*pre+b)%c;
		//cout<<x<<' '<<k<<endl;
		pre=query(root[endver[x]],k);
		printf("%lld\n",pre);
	}
	return 0;
}
/*
���: 
���������5�������� 
֮ǰһ��д�Ĵ���һֱԼ750msWA�������� 
������д��һ�Σ���Σ����ͱ�����������ô����ô�� 
�ύ��ȥ����Լ750msWA
Asriel_Dreemurr�����������ȥ������ύ���� 
����70�֣�ȥ�������� 
������ɢ���Ժ�����ظ���Ȩֵ�� 
��Ȩֵ��ΧС�����ݺ�ȥ�غ�ͻῨһЩĪ�������bug
��ѯ�ʵ�Ҷ�ӽڵ�ʱ���ܴ���˶����cnt���� 
����ֱ�ӷ����˸�Ҷ�ӽڵ��Ȩֵ�ͣ� 
�ͱ�����С�����ٶ��Ķ������ύ��1A�ˡ��� 
�����Ժ���ֻ�Ĵ����ݡ����� 
P.S.�Ҿ��ǲ�д��ţ����ֲ��ܰ��Ұ���jianpowvg4p g'mw54
p]l]h,b354
;h
[t\h[bp\[
*/
