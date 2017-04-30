#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const long long MAXN=500500;
const long long Inf=0x3f3f3f3f3f3f3f3fll;
struct node
{
    long long sum,maxx,lmax,rmax,num,size,lazy;
    bool rev;
    node *lson,*rson,*pa,*next;
}*rf,*root,*top,pool[MAXN];
long long dat[MAXN];
inline long long lmax(node *x){if(x)return x->lmax;return 0;}
inline long long rmax(node *x){if(x)return x->rmax;return 0;}
inline long long sum(node *x){if(x)return x->sum;return 0;}
inline long long maxx(node *x){if(x)return x->maxx;return -Inf;}
inline long long size(node *x){if(x)return x->size;return 0;}
inline node* new_node()
{
    node *tmp=top;
    top=top->next;
    tmp->lson=tmp->rson=tmp->pa=0;
    tmp->rev=false;
    tmp->sum=tmp->lmax=tmp->rmax=tmp->num=tmp->size;
    tmp->lazy=Inf;
    tmp->maxx=-Inf;
    return tmp;
}
void delete_tree(node *tmp)
{
    if(tmp->lson)delete_tree(tmp->lson);
    if(tmp->rson)delete_tree(tmp->rson);
    tmp->next=top;
    top=tmp;
}
void pntree(node *cur=root)
{
    /*
    if(cur->lson)pntree(cur->lson);
    cout<<cur->num<<' ';
    if(cur->rson)pntree(cur->rson);
    /*/
    cout<<'{';
    if(cur->lson){pntree(cur->lson);if(cur->lson->pa!=cur)cout<<"warning";}
    cout<<'('<<cur->num<<' '<<cur->size<<' '<<cur->sum<<' '<<cur->maxx<<' '<<cur->lmax<<' '<<cur->rmax<<')';
    if(cur->rson){pntree(cur->rson);if(cur->rson->pa!=cur)cout<<"warning";}
    cout<<'}';
    //*/
}
inline void fa_lazy(node *x)
{
    if(!x)return;
    if(x->lazy!=Inf)
    {
        x->num=x->lazy;
        if(x->lazy>0)x->lmax=x->rmax=x->maxx=(x->lazy)*(x->size);
        else
        {
            x->lmax=x->rmax=0;
            x->maxx=x->lazy;
        }
        x->sum=(x->lazy)*(x->size);
        if(x->lson)x->lson->lazy=x->lazy;
        if(x->rson)x->rson->lazy=x->lazy;
        x->lazy=Inf;
    }
    if(x->rev)
    {
        swap(x->lson,x->rson);
        swap(x->lmax,x->rmax);
        if(x->lson)x->lson->rev^=1;
        if(x->rson)x->rson->rev^=1;
        x->rev=false;
    }
}
inline void update(node *x)//size,sum,maxx,lmax,rmax
{
    /*
    x->size=1;
    x->sum=x->maxx=x->lmax=x->rmax=x->num;
    if(x->rson)x->lmax=max(x->lmax,x->rson->lmax+x->lmax);
    if(x->lson)
    {
        fa_lazy(x->lson);
        x->maxx=max(x->maxx,max(x->lson->rmax+x->num,x->lson->maxx));
        x->lmax=max(x->lson->sum+x->lmax,x->lson->lmax);
        x->rmax=max(x->rmax,x->lson->rmax+x->rmax);
        x->sum+=x->lson->sum;
        x->size+=x->lson->size;
    }
    if(x->rson)
    {
        fa_lazy(x->rson);
        x->maxx=max(x->maxx,max(x->rson->lmax+x->rmax,x->rson->maxx));
        x->rmax=max(x->rmax+x->rson->sum,x->rson->rmax);
        x->sum+=x->rson->sum;
        x->size+=x->rson->size;
    }
    /*/
    fa_lazy(x->lson);
    fa_lazy(x->rson);
    x->size=size(x->lson)+size(x->rson)+1;
    x->sum=sum(x->lson)+sum(x->rson)+x->num;
    x->lmax=max(lmax(x->lson),sum(x->lson)+x->num+lmax(x->rson));
    x->rmax=max(rmax(x->rson),sum(x->rson)+x->num+rmax(x->lson));
    x->maxx=max(maxx(x->lson),maxx(x->rson));
    x->maxx=max(x->maxx,rmax(x->lson)+x->num+lmax(x->rson));
    //*/
}
void rot(node *x)
{
    node *p=x->pa,*g=p->pa;
    fa_lazy(p);
    fa_lazy(x);
    if(p->lson==x)
    {
        p->lson=x->rson;
        if(p->lson)p->lson->pa=p;
        p->pa=x;
        x->rson=p;
        if(g->lson==p)g->lson=x;
        else g->rson=x;
        x->pa=g;
        if(root==p)root=x;
    }
    else
    {
        p->rson=x->lson;
        if(p->rson)p->rson->pa=p;
        p->pa=x;
        x->lson=p;
        if(g->lson==p)g->lson=x;
        else g->rson=x;
        x->pa=g;
        if(root==p)root=x;
    }
    update(p);
    update(x);
}
void Splay(node *cur,node *target)
{
    while(cur->pa!=target)
    {
        if(cur->pa->pa==target)rot(cur);
        else
        {
            node *p=cur->pa;
            if((p->lson==cur)^(p->pa->lson==p))
            {
                rot(cur);
                rot(cur);
            }
            else
            {
                rot(p);
                rot(cur);
            }
        }
    }
}
node* Find(node *cur,long long pos)
{
    if(cur==NULL||pos<=0||pos>cur->size)return NULL;
    fa_lazy(cur);
    if(cur->lson)
    {
        if(pos<=cur->lson->size)return Find(cur->lson,pos);
        else if(pos==cur->lson->size+1)return cur;
        else return Find(cur->rson,pos-cur->lson->size-1);
    }
    else
    {
        if(pos==1)return cur;
        else return Find(cur->rson,pos-1);
    }
}
/*void bt()
{
    rf=new_node();
    rf->lson=root;
    root->pa=rf;
}*/
node* bft(int l,int r)
{
    node *tmp=new_node();
    int m=(l+r)/2;
    tmp->num=dat[m];
    if(l!=m)
    {
        tmp->lson=bft(l,m-1);
        tmp->lson->pa=tmp;
        tmp->rson=bft(m+1,r);
        tmp->rson->pa=tmp;
    }
    else if(l!=r)
    {
        tmp->rson=bft(m+1,r);
        tmp->rson->pa=tmp;
    }
    update(tmp);
    return tmp;
}
void ins(long long pos,long long tot)
{
    for(int i=1;i<=tot;i++)scanf("%lld",&dat[i]);
    node *tmp=bft(1,tot);
    if(!root||root->size==0)
    {
        root=tmp;
        rf->lson=root;
        root->pa=rf;
        return;
    }
    if(pos==0)
    {
        node *tmp2=Find(root,1);
        Splay(tmp2,rf);
        tmp2->lson=tmp;
        tmp->pa=tmp2;
        update(tmp2);
    }
    else if(pos==root->size)
    {
        node *tmp1=Find(root,root->size);
        Splay(tmp1,rf);
        tmp1->rson=tmp;
        tmp->pa=tmp1;
        update(tmp1);
    }
    else
    {
        node *tmp1=Find(root,pos);
        node *tmp2=Find(root,pos+1);
        Splay(tmp1,rf);
        Splay(tmp2,root);
        tmp2->lson=tmp;
        tmp->pa=tmp2;
        update(tmp2);
        update(tmp1);
    }
    Splay(tmp,rf);
}//output num
void del(long long l,long long r)
{
    if(l==1)
    {
        if(r==root->size)
        {
            delete_tree(root);
            root=NULL;
            return;
        }
        node *tmp2=Find(root,r+1);
        Splay(tmp2,rf);
        delete_tree(tmp2->lson);
        tmp2->lson=NULL;
        update(tmp2);
    }
    else if(r==root->size)
    {
        node *tmp1=Find(root,l-1);
        Splay(tmp1,rf);
        delete_tree(tmp1->rson);
        tmp1->rson=NULL;
        update(tmp1);
    }
    else
    {
        node *tmp1=Find(root,l-1);
        node *tmp2=Find(root,r+1);
        Splay(tmp1,rf);
        Splay(tmp2,root);
        delete_tree(tmp2->lson);
        tmp2->lson=NULL;
        update(tmp2);
        update(tmp1);
    }
}
void ms(long long l,long long r,long long x)
{
    if(l==1)
    {
        if(r==root->size)
        {
            root->lazy=x;
            return;
        }
        node *tmp2=Find(root,r+1);
        Splay(tmp2,rf);
        tmp2->lson->lazy=x;
        update(tmp2);
    }
    else if(r==root->size)
    {
        node *tmp1=Find(root,l-1);
        Splay(tmp1,rf);
        tmp1->rson->lazy=x;
        update(tmp1);
    }
    else
    {
        node *tmp1=Find(root,l-1);
        node *tmp2=Find(root,r+1);
        Splay(tmp1,rf);
        Splay(tmp2,root);
        tmp2->lson->lazy=x;
        update(tmp2);
        update(tmp1);
    }
}
void rev(long long l,long long r)
{
    if(l==1)
    {
        if(r==root->size)
        {
            root->rev^=1;
            return;
        }
        node *tmp2=Find(root,r+1);
        Splay(tmp2,rf);
        tmp2->lson->rev^=1;
        update(tmp2);
    }
    else if(r==root->size)
    {
        node *tmp1=Find(root,l-1);
        Splay(tmp1,rf);
        tmp1->rson->rev^=1;
        update(tmp1);
    }
    else
    {
        node *tmp1=Find(root,l-1);
        node *tmp2=Find(root,r+1);
        Splay(tmp1,rf);
        Splay(tmp2,root);
        tmp2->lson->rev^=1;
        update(tmp2);
        update(tmp1);
    }
}
long long get_sum(long long l,long long r)
{
    fa_lazy(root);
    if(l==1)
    {
        if(r==root->size)return root->sum;
        node *tmp2=Find(root,r+1);
        Splay(tmp2,rf);
        return tmp2->lson->sum;
    }
    else if(r==root->size)
    {
        node *tmp1=Find(root,l-1);
        Splay(tmp1,rf);
        return tmp1->rson->sum;
    }
    else
    {
        node *tmp1=Find(root,l-1);
        node *tmp2=Find(root,r+1);
        Splay(tmp1,rf);
        Splay(tmp2,root);
        return tmp2->lson->sum;
    }
}
long long max_sum()
{
    fa_lazy(root);
    return root->maxx;
}
long long n,q,x,posi,tot;
char buf[256];
//void test(node *x=root){if(!x)return;fa_lazy(x);test(x->lson);test(x->rson);}
int main()
{
    /*
    freopen("in.txt","r",stdin);
    freopen("out.txt","wb",stdout);
    //*/
    top=&pool[0];
    for(int i=0;i<MAXN-1;i++)pool[i].next=&pool[i+1];
    rf=new_node();
    scanf("%lld%lld",&n,&q);
    for(long long i=1;i<=n;i++)
    {
        scanf("%lld",&dat[i]);
        //ins(x,i-1);
        //pntree(root);cout<<endl;
    }
    root=bft(1,n);
    rf->lson=root;root->pa=rf;
    //*
    for(long long i=1;i<=q;i++)
    /*/
    for(int i=1;i<=23;i++)
    //*/
    {
        //pntree();cout<<endl;
        scanf("%s",buf);
        switch(buf[2])
        {
            case 'S':
                 scanf("%lld%lld",&posi,&tot);
                 ins(posi,tot);
                 break;
            case 'L':
                 scanf("%lld%lld",&posi,&tot);
                 del(posi,posi+tot-1);
                 break;
            case 'K':
                 scanf("%lld%lld%lld",&posi,&tot,&x);
                 ms(posi,posi+tot-1,x);
                 break;
            case 'V':
                 scanf("%lld%lld",&posi,&tot);
                 rev(posi,posi+tot-1);
                 break;
            case 'T':
                 scanf("%lld%lld",&posi,&tot);
                 if(tot==0)printf("0\n");
                 else printf("%lld\n",get_sum(posi,posi+tot-1));
                 break;
            case 'X':
                 printf("%lld\n",max_sum());
                 break;
        }
    }
    //test();pntree();cout<<endl;
    //system("pause");
    return 0;
}//max_neg? -- What if all numbers in the array are negative? What's the max sum here?
//bt() in ins()? -- What if the data deleted all the numbers in the array? -- fixed
