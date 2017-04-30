#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=10000007;
int n,m;
struct matrix
{
    int mat[15][15];
    matrix()
	{
	    memset(mat,0,sizeof(mat));
	}
    matrix operator=(const matrix &m)
	{
	    for(int i=1;i<=n+1;i++)
	    {
		    for(int j=1;j<=n+1;j++)
		    {
			    mat[i][j]=m.mat[i][j];
			}
		}
		return *this;
	}
    matrix operator*=(const matrix &m)
	{
	    matrix tmp;
	    for(int i=1;i<=n+1;i++)
	    {
		    for(int j=1;j<=n+1;j++)
		    {
			    for(int k=1;k<=n+1;k++)
			    {
				    tmp.mat[i][j]=(tmp.mat[i][j]+ (long long)(mat[i][k]) * m.mat[k][j] )%10000007;
				}
			}
		}
		*this=tmp;
		return *this;
	}
}mult,ans,idn,cur;
void f_exp(matrix x,int y)
{
    int bit=1<<30;
    cur=idn;
    while(bit)
    {
	    cur*=cur;
	    if(y&bit)cur*=x;
	    bit>>=1;
	}
}
int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	while(scanf("%d%d",&n,&m)==2)
	{
	for(int i=2;i<=n;i++)scanf("%d",&(ans.mat[1][i+1]));
	for(int i=1;i<=n+1;i++){idn.mat[i][i]=1;}
	ans.mat[1][1]=1;
	ans.mat[1][2]=233;
	mult.mat[1][1]=1;
	mult.mat[1][2]=3;
	mult.mat[2][2]=10;
	for(int j=3;j<=n+1;j++)
	    for(int i=2;i<=j;i++)
	        mult.mat[i][j]=1;
	/*for(int i=1;i<m;i++)
	{
		//for(int i=1;i<=n+1;i++)cout<<ans.mat[1][i]<<' ';
		//cout<<endl;
		
	    ans*=mult;
	}*/
	
	/*{
		for(int i=1;i<=n+1;i++)cout<<ans.mat[1][i]<<' ';
		cout<<endl;
	    for(int i=1;i<=n+1;i++)
		{
	        for(int j=1;j<=n+1;j++)
	    	{
		        cout<<mult.mat[i][j]<<' ';
			}
			cout<<endl;
		}
	}*/
	f_exp(mult,m-1);
	ans*=cur;
	printf("%d\n",ans.mat[1][n+1]);
    }
	return 0;
}
