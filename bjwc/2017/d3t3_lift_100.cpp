#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
using namespace std;
short mark[51][51][51][512];
//0=a.move,1~2=a.lift,00=a.empty_handed,01=a.thrown,10=a.lift_b,11=a.lift_c;3~5=b;6~8=c;512-876543210
short x1,x2,x3,m1,m2,m3,t1,t2,t3;
short search(short apos,short bpos,short cpos,short flag)
{
    
    if(mark[apos][bpos][cpos][flag]!=-1)return mark[apos][bpos][cpos][flag];
    /*debug
    cout<<"searching "<<apos<<' '<<bpos<<' '<<cpos<<' ';
    int tmp=flag;
    for(int i=1;i<=9;i++){cout<<(tmp&1);tmp>>=1;}
    cout<<endl;
    //end_of_debug*/
    short curmax=max(apos,bpos);
    curmax=max(curmax,cpos);
    //search a
    //move a
    if(!(flag&0001)&&apos!=bpos&&apos!=cpos)
        for(short i=max(apos-m1,0);i<=apos+m1;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                curmax=max(curmax,search(i,bpos,cpos,flag|0001));
    //lift a
    if(!(flag&0006)&&((flag&0060)!=0040)&&((flag&0600)!=0400))
    {
        if(bpos==apos+1||bpos==apos-1)
            if(bpos!=cpos)
                curmax=max(curmax,search(apos,apos,cpos,flag|0004));
            else if((flag&0060)==0060)
                curmax=max(curmax,search(apos,apos,apos,flag|0004));
        if(cpos==apos+1||cpos==apos-1)
            if(bpos!=cpos)
                curmax=max(curmax,search(apos,bpos,apos,flag|0006));
            else if((flag&0600)==0600)
                curmax=max(curmax,search(apos,apos,apos,flag|0006));
    }
    //throw a
    if((flag&0004)&&((flag&0060)!=0040)&&((flag&0600)!=0400))
        for(short i=max(apos-t1,0);i<=apos+t1;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                if(apos==bpos&&apos==cpos)
                    curmax=max(curmax,search(apos,i,i,(flag&0771)|0002));
                else if(apos==bpos)
                    curmax=max(curmax,search(apos,i,cpos,(flag&0771)|0002));
                else
                    curmax=max(curmax,search(apos,bpos,i,(flag&0771)|0002));
    //search b
    //move b
    if(!(flag&0010)&&apos!=bpos&&bpos!=cpos)
        for(short i=max(bpos-m2,0);i<=bpos+m2;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                curmax=max(curmax,search(apos,i,cpos,flag|0010));
    //lift b
    if(!(flag&0060)&&((flag&0006)!=0004)&&((flag&0600)!=0600))
    {
        if(bpos==apos+1||bpos==apos-1)
            if(apos!=cpos)
                curmax=max(curmax,search(bpos,bpos,cpos,flag|0040));
            else if((flag&0006)==0006)
                curmax=max(curmax,search(bpos,bpos,bpos,flag|0040));
        if(cpos==bpos+1||cpos==bpos-1)
            if(apos!=cpos)
                curmax=max(curmax,search(apos,bpos,bpos,flag|0060));
            else if((flag&0600)==0400)
                curmax=max(curmax,search(bpos,bpos,bpos,flag|0060));
    }
    //throw b
    if((flag&0040)&&((flag&0006)!=0004)&&((flag&0600)!=0600))
        for(short i=max(bpos-t2,0);i<=bpos+t2;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                if(apos==bpos&&bpos==cpos)
                    curmax=max(curmax,search(i,bpos,i,(flag&0717)|0020));
                else if(apos==bpos)
                    curmax=max(curmax,search(i,bpos,cpos,(flag&0717)|0020));
                else
                    curmax=max(curmax,search(apos,bpos,i,(flag&0717)|0020));
    //search c
    //move c
    if(!(flag&0100)&&cpos!=bpos&&apos!=cpos)
        for(short i=max(cpos-m3,0);i<=cpos+m3;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                curmax=max(curmax,search(apos,bpos,i,flag|0100));
    //lift c
    if(!(flag&0600)&&((flag&0006)!=0006)&&((flag&0060)!=0060))
    {
        if(cpos==apos+1||cpos==apos-1)
            if(apos!=bpos)
                curmax=max(curmax,search(cpos,bpos,cpos,flag|0400));
            else if((flag&0006)==0004)
                curmax=max(curmax,search(cpos,cpos,cpos,flag|0400));
        if(cpos==bpos+1||cpos==bpos-1)
            if(apos!=bpos)
                curmax=max(curmax,search(apos,cpos,cpos,flag|0600));
            else if((flag&0060)==0040)
                curmax=max(curmax,search(cpos,cpos,cpos,flag|0600));
    }
    //throw c
    if((flag&0400)&&((flag&0006)!=0006)&&((flag&0060)!=0060))
        for(short i=max(cpos-t3,0);i<=cpos+t3;i++)
            if(i!=apos&&i!=bpos&&i!=cpos)
                if(apos==cpos&&bpos==cpos)
                    curmax=max(curmax,search(i,i,cpos,(flag&0177)|0200));
                else if(apos==cpos)
                    curmax=max(curmax,search(i,bpos,cpos,(flag&0177)|0200));
                else
                    curmax=max(curmax,search(apos,i,cpos,(flag&0177)|0200));
    /*debug
    cout<<apos<<' '<<bpos<<' '<<cpos<<' ';
    int tmp2=flag;
    for(int i=1;i<=9;i++){cout<<(tmp2&1);tmp2>>=1;}
    cout<<endl;
    //end_of_debug*/
    return mark[apos][bpos][cpos][flag]=curmax;
}
int main()
{
    freopen("lift.in","r",stdin);
    freopen("lift.out","w",stdout);
    memset(mark,-1,sizeof(mark));
    cin>>x1>>m1>>t1>>x2>>m2>>t2>>x3>>m3>>t3;
    cout<<search(x1,x2,x3,0)<<endl;
    return 0;
}
