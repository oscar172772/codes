#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MOD=3,MOD2=10337;
inline int ksm(int x,int y,int mod)
{
	int bit=1<<20,ans=1;
	while(bit)
	{
		ans*=ans,ans%=mod;
		if(y&bit)ans*=x,ans%=mod;
		bit>>=1;
	}
	return ans;
}
inline int inv(int x,int mod)
{
	return ksm(x,mod-2,mod);
}
int n,m,u[1111][111],v[1111][111],top[111];
int mat[111][111];
inline int det(int siz,int mod)
{
	//cout<<"DET-in,mod="<<mod<<"\n";
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			mat[i][j]=(mat[i][j]%mod+mod)%mod;
		}
	}
	//cout<<"DET-A.1\n";
	for(int i=1;i<siz;i++)
	{
		int flag=0;
		for(int j=i;j<=siz;j++)
		{
			if(mat[j][i]!=0)
			{
				flag=j;
				break;
			}
		}
		if(!flag){/*cout<<"DET-break\n";*/return 0;}
		if(flag!=i)
		{
			ans=-ans;
			for(int j=i;j<=siz;j++)
			{
				swap(mat[i][j],mat[flag][j]);
			}
		}
		for(int j=i+1;j<=siz;j++)//row
		{
			int tmp=(mat[j][i]*inv(mat[i][i],mod))%mod;
			for(int k=i;k<=siz;k++)//column
			{
				mat[j][k]-=(mat[i][k]*tmp)%mod;
				mat[j][k]=(mat[j][k]+mod)%mod;
			}
		}
	}
	for(int i=1;i<=siz;i++)
	{
		ans=(ans*mat[i][i])%mod;
	}
	ans=(ans+mod)%mod;
	//cout<<"DET-out\n";
	return ans;
}
int rt[111],le;
/*
int find(int x){return rt[x]?rt[x]=find(rt[x]):x;}
void onion(int x,int y)
{
	int px=find(x),py=find(y);
	if(px<py)
		rt[py]=px;
	else
		rt[px]=py;
}
*/
int pa[111];
int find(int x){return pa[x]!=x?pa[x]=find(pa[x]):x;}
void onion(int x,int y)
{
	int px=find(x),py=find(y);
	if(px<py)
		pa[py]=px;
	else
		pa[px]=py;
}
int tmp[111];
int ans1=1,ans2=1;
struct atom
{
	int x,id,a,b;
	inline bool operator<(const atom &r)const{return x<r.x;}
}arr[1111];
//inline bool cmp(const atom &a,const atom &b){return a.id<b.id;}
int bck[111][111];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&arr[i].a,&arr[i].b,&arr[i].x);
		//u[c][++top[c]]=a;
		//v[c][top[c]]=b;
	}
	sort(arr+1,arr+m+1);
	int cn=0;
	for(int i=1;i<=m;i++)
	{
		if(arr[i].x!=arr[i-1].x)cn++;
		u[cn][++top[cn]]=arr[i].a;
		v[cn][top[cn]]=arr[i].b;
	}
	for(int i=1;i<=n;i++)rt[i]=i;
	le=n;
	for(int l=1;l<=cn;l++)
	{
		if(le==1)break;
		for(int i=1;i<=le;i++)
		{
			pa[i]=i;
		}
		//cout<<"A.1\n";
		for(int i=1;i<=top[l];i++)
		{
			int x=rt[u[l][i]],y=rt[v[l][i]];
			if(find(x)!=find(y))
			{
				//cout<<"onion"<<x<<','<<y<<endl;
				onion(x,y);
				//cout<<find(x)<<' '<<find(y)<<endl;
			}
		}
		int cnt;
		//cout<<"A.2\n";
		//for(int i=1;i<=le;i++)cout<<find(i)<<' ';cout<<endl;
		for(int i=1;i<=le;i++)
		{
			cnt=0;
			memset(mat,0,sizeof(mat));
			memset(tmp,0,sizeof(tmp));
			//memset(pmt,0,sizeof(pmt));
			for(int j=i;j<=le;j++)
			{
				if(find(j)==i)
				{
					cnt++;
					//pmt[cnt]=j;//->new_matrix
					tmp[j]=cnt;//->old_node
				}
			}
			//cout<<"B.1."<<i<<"\n";
			//for(int k=1;k<=cnt;k++)cout<<tmp[k]<<' ';cout<<endl;
			for(int j=1;j<=top[l];j++)
			{
				int &x=rt[u[l][j]],&y=rt[v[l][j]];
				if(find(x)==i&&find(y)==i)
				{
					mat[tmp[x]][tmp[y]]--;
					mat[tmp[y]][tmp[x]]--;
					mat[tmp[x]][tmp[x]]++;
					mat[tmp[y]][tmp[y]]++;
				}
			}
			//cout<<"B.2."<<i<<"\n";
			if(cnt>=2)
			{
				for(int s=1;s<=cnt-1;s++)
				{
					for(int t=1;t<=cnt-1;t++)
					{
						bck[s][t]=mat[s][t];
					}
				}
				if(ans1!=0)ans1*=det(cnt-1,MOD);
				/*
				for(int i=1;i<=cnt;i++)
				{
					for(int j=1;j<=cnt;j++)
					{
						cout<<mat[i][j]<<' ';
					}
					cout<<endl;
				}
				cout<<ans1<<endl;
				*/
				for(int s=1;s<=cnt-1;s++)
				{
					for(int t=1;t<=cnt-1;t++)
					{
						mat[s][t]=bck[s][t];
					}
				}
				if(ans2!=0)ans2*=det(cnt-1,MOD2);
				ans1%=MOD,ans2%=MOD2;
			}
		}
		for(int i=1;i<=n;i++)
		{
			arr[i].x=find(rt[i]);
			arr[i].id=i;
			//cout<<find(rt[i])<<' ';
		}
		sort(arr+1,arr+n+1);
		cnt=0;
		//arr[0].x=-1;
		for(int i=1;i<=n;i++)
		{
			if(arr[i].x!=arr[i-1].x)cnt++;
			rt[arr[i].id]=cnt;
		}
		le=cnt;
		//for(int i=1;i<=n;i++)cout<<rt[i]<<' ';cout<<endl;
	}
	//cout<<ans1<<' '<<ans2<<endl;
	if(le==1)
		for(int i=0;i<MOD*MOD2;i++)
		{
			if(i%MOD==ans1&&i%MOD2==ans2)
				printf("%d\n",i);
		}
	else printf("0\n");
	return 0;
}
