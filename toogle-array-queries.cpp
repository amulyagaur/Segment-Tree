#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

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
	tree[index] = tree[2*index]+tree[2*index+1];
}

void updateRange(int *tree,bool *lazy,int index,int s,int e,int rs,int re)
{
	if(lazy[index])
	{
		lazy[index]=false;
		tree[index] = e-s+1-tree[index];
		if(s<e)
		{
			lazy[2*index] = !(lazy[2*index]);
			lazy[2*index+1] = !(lazy[2*index+1]);
		}
		
	}
	if(s>e || s>re || e<rs)
		return;
	if(s>=rs && e<=re)
	{
		tree[index] = e-s+1-tree[index];
		if(s!=e)
		{
			lazy[2*index] = !lazy[2*index];
			lazy[2*index+1] = !lazy[2*index+1];
		}
		return;
	}

	int m= (s+e)/2;
	updateRange(tree,lazy,2*index,s,m,rs,re);
	updateRange(tree,lazy,2*index+1,m+1,e,rs,re);
	tree[index] = tree[2*index]+tree[2*index+1];
}

int query(int *tree,bool *lazy,int index,int s,int e,int rs,int re)
{

	if(s>e || s>re || e<rs)
		return 0;
	if(lazy[index])
	{
		tree[index] = e-s+1-tree[index];
		if(s<e)
		{
			lazy[2*index] = !lazy[2*index];
			lazy[2*index+1] = !lazy[2*index+1];
		}
		lazy[index]=false;
	}
	
	if(s>=rs && e<=re)
		return tree[index];

	int m= (s+e)/2;
	int left=query(tree,lazy,2*index,s,m,rs,re);
	int right = query(tree,lazy,2*index+1,m+1,e,rs,re);
	return (left+right);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // binary array
    int a[6]={1,0,0,1,0,1};
    int n =6;
    int s=0,e=n-1,index=1;
    int *tree = new int[4*n+1];
    bool *lazy = new bool[4*n+1];
    buildTree(tree,a,index,s,e);
    cout<<query(tree,lazy,index,s,e,1,5)<<endl;
    updateRange(tree,lazy,index,s,e,1,3);
    cout<<query(tree,lazy,index,s,e,0,5)<<endl;
    for(int i=0;i<6;i++)
    	cout<<query(tree,lazy,index,s,e,i,i)<<endl;
    return 0;
}
