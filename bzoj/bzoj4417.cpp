#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<stack>
using namespace std;

struct Matrix
{
    int dimx,dimy;
    int mod;
    long long mat[110][110];
    
    Matrix(int x,int y):mod(30011),dimx(x),dimy(y){memset(mat,0,sizeof(mat));}
    Matrix(const Matrix &x):mod(30011),dimx(x.dimx),dimy(x.dimy){memcpy(mat,x.mat,sizeof(x.mat));}
    
    Matrix operator*(const Matrix m)const
    {
        Matrix tmp=*this;
        if(dimy!=m.dimx)return tmp;
        for(int i=1;i<=dimx;i++)
        {
            for(int j=1;j<=m.dimy;j++)
            {
                tmp.mat[i][j]=0;
                for(int k=1;k<=dimy;k++)
                {
                    tmp.mat[i][j]+=mat[i][k]*m.mat[k][j];
                    tmp.mat[i][j]%=mod;
                }
            }
        }
        tmp.dimx=dimx;
        tmp.dimy=m.dimy;
        return tmp;
    }
    Matrix operator*=(const Matrix m)
    {
        *this=*this*m;
        return *this;
    }
};
stack<int> st;
Matrix f_exp(Matrix m,long long T)
{
    Matrix tmp=m;      //m^1
    if(T<=0)
    {
        for(int i=1;i<=tmp.dimx;i++)
        {
            for(int j=1;j<=tmp.dimy;j++)
            {
                if(i==j)tmp.mat[i][j]=1;
                else tmp.mat[i][j]=0;
            }
        }
        return tmp;
    }
    while(T>1)
    {
        if(T%2)
            st.push(1);
        else
            st.push(0);
        T/=2;
    }
    while(!st.empty())
    {
        m*=m;
        if(st.top())
            m*=tmp;
        st.pop();
    }
    return m;
}
int main()
{
    int N;
    long long M;
    cin>>N>>M;
    if(M<=2)
    {
        cout<<1<<endl;
        return 0;
    }
    Matrix m=Matrix(2*N,2*N);
    for(int i=N+1;i<=2*N;i++)
    {
        m.mat[i][i]=1;
        m.mat[i][i+1]=1;
        m.mat[i+1][i]=1;
        m.mat[i-N][i]=1;
        m.mat[i][i-N]=1;
    }
    /*for(int i=1;i<=2*N;i++)
    {
        for(int j=1;j<=2*N;j++)
        {
            cout<<m.mat[i][j]<<' ';
        }
        cout<<endl;
    }*/
    Matrix ans=Matrix(1,2*N);
    if(N==1)
    {
        ans.mat[1][1]=1;
        ans.mat[1][2]=1;
    }
    else
    {
        ans.mat[1][1]=1;
        ans.mat[1][2]=1;
        ans.mat[1][N+1]=2;
        ans.mat[1][N+2]=2;
        ans.mat[1][N+3]=1;
    }
    Matrix tmp=f_exp(m,M-3);
    /*for(int i=1;i<=2*N;i++)
    {
        for(int j=1;j<=2*N;j++)
        {
            cout<<tmp.mat[i][j]<<' ';
        }
        cout<<endl;
    }*/
    ans*=tmp;
    cout<<ans.mat[1][2*N]<<endl;
    return 0;
}
