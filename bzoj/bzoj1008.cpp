#include<iostream>
#include<stack>
using namespace std;

stack<int> st;
long long f_exp(long long m,long long T)
{
    int tmp=m%100003;      //m^1
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
        m%=100003;
        m*=(m%100003);
        m%=100003;
        if(st.top())
            m*=(tmp%100003);
        m%=100003;
        st.pop();
    }
    return m;
}
long long n,m;
int main()
{
    cin>>m>>n;
    //cout<<(f_exp(m,n)%100003+100003)%100003<<endl;
    long long x=(m%100003*f_exp(m-1,n-1))%100003;
    long long y=f_exp(m,n);
    cout<<((y-x)%100003+100003)%100003<<endl;
    return 0;
}
