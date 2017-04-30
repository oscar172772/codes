#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct Matrix
{
    int dim;
    const static int mod=65521;
    unsigned int mat[210][210];
    
    Matrix(){}
    Matrix(int x):dim(x){memset(mat,0,sizeof(mat));}
    Matrix(const Matrix &x):dim(x.dim){memcpy(mat,x.mat,sizeof(x.mat));}
    Matrix(int x,int *sz):dim(x){memcpy(mat,sz,sizeof(sz));}
    
    Matrix operator=(const Matrix &m)
    {
        memcpy(mat,m.mat,sizeof(m.mat));
        dim=m.dim;
        return *this;
    }
    Matrix operator*(const Matrix &m)const
    {
        Matrix tmp(dim);
        //if(dim!=m.dim)return tmp;
        for(int i=1;i<=dim;i++)
        {
            for(int j=1;j<=dim;j++)
            {
                for(int k=1;k<=dim;k++)
                {
                    tmp.mat[i][j]+=(unsigned int)(mat[i][k])*m.mat[k][j];
                    tmp.mat[i][j]%=mod;
                }
            }
        }
        return tmp;
    }
    Matrix operator*=(const Matrix &m)
    {
        *this=*this*m;
        return *this;
    }
    //*
    friend ostream& operator<<(ostream &os,Matrix tmp)
    {
        for(int i=1;i<=tmp.dim;i++)
        {
            for(int j=1;j<=tmp.dim;j++)
            {
                os<<tmp.mat[i][j]<<' ';
            }
            os<<'\n';
        }
        return os;
    }
    //*/
}ans,mult,idn;
int compress[600000],decompress[600],bit[60],connect[60],minconnect[60],top;
long long n;
int k;
void init(int cur)
{
    if(cur>k)
    {
        int tmp=0;
        for(int i=1;i<=k;i++)
        {
            tmp=tmp*10+bit[i];
        }
        top++;
        compress[tmp]=top;
        decompress[top]=tmp;
    }
    else
    {
        for(int i=1;i<=cur;i++)
        {
            bit[cur]=i;
            if(bit[i]==i)
            {
                init(cur+1);
            }
        }
    }
}
void manage_connectivity(int cur,int num)
{
    if(cur>k)
    {
        int flag=0,flag2=k+1;//flag--first node connects to node 1;;;;;flag2--first node connects to node k+1
        for(int i=k;i>=2;i--)
        {
            if(bit[i]==1)flag=i;
            if(connect[i])flag2=min(flag2,bit[i]==1?i:bit[i]);
        }
        if(flag||connect[1])
        {
            memset(minconnect,0,sizeof(minconnect));
            if(connect[1]&&flag)flag=flag2=min(flag,flag2);
            int newbit[6];
            for(int i=2;i<=k;i++)
            {
                if(bit[i]==1&&connect[i])
                    flag=flag2=min(flag,flag2);
            }
            for(int i=2;i<=k;i++)
            {
                if(bit[i]==1){if(minconnect[bit[i]]==0)minconnect[bit[i]]=flag;}
                else if(minconnect[bit[i]]==0) minconnect[bit[i]]=bit[i];
                if(connect[i])
                    minconnect[bit[i]]=min(minconnect[bit[i]],flag2);
            }
            for(int i=1;i<=k-1;i++)
            {
                newbit[i]=minconnect[bit[i+1]]-1;
                newbit[i]=newbit[newbit[i]];
            }
            if(flag2==k+1)newbit[k]=flag2-1;
            else newbit[k]=minconnect[bit[flag2]]-1;
            int tmp2=0;
            for(int i=1;i<=k;i++)
            {
                tmp2*=10;
                tmp2+=newbit[i];
            }
            /*
            if(!compress[tmp2])cout<<tmp2<<", RE!\n";
            cout<<num<<"---->"<<tmp2<<",connectivity=";
            for(int i=1;i<=k;i++)cout<<connect[i]<<' ';
            cout<<endl;
            //*/
            mult.mat[compress[num]][compress[tmp2]]++;
        }
    }
    else
    {
        bool flag=true;
        manage_connectivity(cur+1,num);
        for(int i=1;i<cur;i++)
        {
            if(bit[i]==bit[cur]&&connect[i])
                flag=false;
        }
        if(flag)
        {
            connect[cur]=1;
            manage_connectivity(cur+1,num);
            connect[cur]=0;
        }
    }
}
void initm()
{
    int tmp;
    for(int i=1;i<=top;i++)
    {
        tmp=decompress[i];
        for(int j=k;j>=1;j--)
        {
            bit[j]=tmp%10;
            tmp/=10;
        }
        manage_connectivity(1,decompress[i]);
    }
}
template <typename T>
inline T f_exp(T cur,const T &mult,long long y)
{
    if(y<=0)return cur;
    long long bit=1ll<<60;
    while(bit)
    {
        cur*=cur;
        if(y&bit)cur*=mult;
        /*
        cout<<"cur, after xxx'ing with "<<bit<<" bit:\n"<<cur<<endl;
        //*/
        bit>>=1;
        
    }
    
    return cur;
}
inline int fc(int x){if(x<=2)return 1;else return f_exp(1,x,x-2);}
int main()
{
    
    scanf("%d%lld",&k,&n);//cin>>k>>n;
    init(1);
    /*
    for(int i=1;i<=top;i++)
        cout<<i<<' '<<decompress[i]<<' '<<compress[decompress[i]]<<endl;
    //*/
    ans.dim=mult.dim=idn.dim=top;
    initm();
    for(int i=1;i<=top;i++)
    {
        idn.mat[i][i]=1;
    }
    /*
    cout<<"mult:\n"<<mult<<endl;
    //*/
    for(int i=1;i<=top;i++)
    {
        int tmp2=decompress[i];
        ans.mat[1][i]=1;
        memset(bit,0,sizeof(bit));
        for(int j=1;j<=k;j++)
        {
            bit[tmp2%10]++;
            tmp2/=10;
        }
        for(int j=1;j<=k;j++)ans.mat[1][i]*=fc(bit[j]);
    }
    /*
    cout<<"ans:\n"<<ans<<endl;
    //*/
    Matrix tmp=f_exp(idn,mult,n-k);
    /*
    cout<<"tmp (dim="<<tmp.dim<<"):\n"<<tmp<<endl;
    //*/
    ans*=tmp;
    /*
    cout<<"ans (dim="<<ans.dim<<"):\n"<<ans<<endl;
    //*/
    printf("%d\n",ans.mat[1][1]);//cout<<ans.mat[1][1]<<endl;
    //system("pause");
    return 0;
}
