#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 200200
using namespace std;
int n,ans;
char s[M];
map<pair<int,int>,int> m;
int sum[3][M];
int main()
{
    int i;
    cin>>n;
    scanf("%s",s+1);
    m[make_pair(0,0)]=0;
    for(i=1;i<=n;i++)
    {
        sum[0][i]=sum[0][i-1]+(s[i]=='J');
        sum[1][i]=sum[1][i-1]+(s[i]=='O');
        sum[2][i]=sum[2][i-1]+(s[i]=='I');
        if( m.find( make_pair(sum[0][i]-sum[1][i],sum[1][i]-sum[2][i]) )==m.end() )
            m[make_pair(sum[0][i]-sum[1][i],sum[1][i]-sum[2][i])]=i;
        else
            ans=max(ans,i-m[make_pair(sum[0][i]-sum[1][i],sum[1][i]-sum[2][i])]);
    }
    cout<<ans<<endl;
    return 0;
}
