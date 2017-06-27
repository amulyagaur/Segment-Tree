#include <bits/stdc++.h>
using namespace std;

void buildTree(int *tree,int *a,int index,int s,int e)
{
	if(s>e)
		return ;
	if(s==e)
	{
		tree[index]=a[s];
		return ;
	}
	int m = (s+e)/2;
	buildTree(tree,a,2*index,s,m);
	buildTree(tree,a,2*index+1,m+1,e);
	tree[index] = min(tree[2*index],tree[2*index+1]);
}

void updateNode(int *tree,int index,int s,int e,int pos,int val)
{
	if(pos<s || pos>e)
		return ;
	if(s==e)
	{
		tree[index] = val;
		return ;
	}
	int m = (s+e)/2;
	updateNode(tree,2*index,s,m,pos,val);
	updateNode(tree,2*index+1,m+1,e,pos,val);
	tree[index] = min(tree[2*index],tree[2*index+1]);
	return;
}

void updateRange(int *tree,int *lazy,int index,int s,int e,int rs,int re,int inc)
{
	if(lazy[index]!=0)
	{
		tree[index] += lazy[index];
		if(s!=e)
		{
			lazy[2*index] += lazy[index];
			lazy[2*index+1] += lazy[index];
		}
		lazy[index]=0;
	}

	if(s>e || s>re || e<rs)
		return;

	if(s>=rs && e<=re)
	{
		tree[index] += inc;
		if(s!=e)
		{
			lazy[2*index]+=inc;
			lazy[2*index+1] +=inc;
		}
		return;
	}

	int m= (s+e)/2;
	updateRange(tree,lazy,2*index,s,m,rs,re,inc);
	updateRange(tree,lazy,2*index+1,m+1,e,rs,re,inc);
	tree[index] = min(tree[2*index],tree[2*index+1]);
}

int query(int *tree,int *lazy,int index,int s,int e,int rs,int re)
{
	if(lazy[index]!=0)
	{
		tree[index] += lazy[index];
		if(s!=e)
		{
			lazy[2*index] += lazy[index];
			lazy[2*index+1] += lazy[index];
		}
		lazy[index]=0;
	}

	if(s>e || s>re || e<rs)
		return INT_MAX;
	if(s>=rs && e<=re)
		return tree[index];
	int m= (s+e)/2;
	int left=query(tree,lazy,2*index,s,m,rs,re);
	int right = query(tree,lazy,2*index+1,m+1,e,rs,re);
	return min(left,right);

}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a[6]={1,3,5,7,9,11};
    int n =6;
    int s=0,e=n-1,index=1;
    int *tree = new int[4*n+1];
    int *lazy = new int[4*n+1];
    buildTree(tree,a,index,s,e);
    //cout<<query(tree,lazy,index,s,e,3,5)<<endl;
    updateRange(tree,lazy,index,s,e,2,5,10);
    
    updateRange(tree,lazy,index,s,e,1,4,3);
   	cout<<query(tree,lazy,index,s,e,2,5)<<endl;
   	updateRange(tree,lazy,index,s,e,3,4,-12);
   	cout<<query(tree,lazy,index,s,e,2,5)<<endl;
    return 0;
}
