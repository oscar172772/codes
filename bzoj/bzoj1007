#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
struct line
{
    int id;
    double a,b;
    inline bool operator<(const line &l)const{return a<l.a;}
    inline line operator=(const line &l){id=l.id;a=l.a;b=l.b;return *this;}
}l[50050];
line st[50050];
int top;
inline bool cmp(const line &a,const line &b){return a.id<b.id;}
inline double intersection(const line &a,const line &b)
{
    return (b.b-a.b)/(a.a-b.a);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){scanf("%lf%lf",&l[i].a,&l[i].b);l[i].id=i;}
    sort(l+1,l+n+1);
    st[++top]=l[1];
    for(int i=2;i<=n;i++)
    {
        if(st[top].a==l[i].a&&st[top].b<l[i].b)top--;
        else if(st[top].a==l[i].a)continue;
        while(top>1&&intersection(l[i],st[top])<=intersection(l[i],st[top-1]))top--;
        st[++top]=l[i];
    }
    sort(st+1,st+top+1,cmp);
    for(int i=1;i<=top;i++)printf("%d ",st[i].id);
    return 0;
}
