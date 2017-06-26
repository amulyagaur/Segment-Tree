#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
//function to build the segment tree
void buildTree(int *tree,int *a,int index,int s,int e)
{
	//base case
	if(s>e)
		return;
	//reached leaf node
	if(s==e)
	{
		tree[index]=a[s];
		return ;
	}
	//now build the segment tree in bottom up manner
	int m = (s+e)/2;
	buildTree(tree,a,2*index,s,m);
	buildTree(tree,a,2*index+1,m+1,e);
	tree[index]= (tree[2*index]*tree[2*index+1])/__gcd(tree[2*index],tree[2*index+1]);
	return;
}

//function to query the segment tree for RLQ
int query(int *tree,int index,int s,int e,int qs,int qe)
{
	//base case: if query range is outside the node range
	if(qs>e || s>qe)
		return 1;
	//complete overlap
	if(s>=qs && e<=qe)
		return tree[index];
	//now partial overlap case is executed
	int m = (s+e)/2;
	int left_ans = query(tree,2*index,s,m,qs,qe);
	int right_ans = query(tree,2*index+1,m+1,e,qs,qe);
	return (left_ans*right_ans)/__gcd(left_ans,right_ans);
}

//function to update a value at position to "pos"
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
	tree[index]= (tree[2*index]*tree[2*index+1])/__gcd(tree[2*index],tree[2*index+1]);
	return;
}

//function to update the values in a range
void updateRange(int *tree,int index,int s,int e,int rs,int re,int inc)
{
	//query range outside the node range
	if(s>re || e<rs)
		return;
	if(s==e)
	{
		tree[index] += inc;
		return ;
	}
	int m = (s+e)/2;
	updateRange(tree,2*index,s,m,rs,re,inc);
	updateRange(tree,2*index+1,m+1,e,rs,re,inc);
	tree[index]= (tree[2*index]*tree[2*index+1])/__gcd(tree[2*index],tree[2*index+1]);
	return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a[] ={3,40,5,12};										 //input array	
    int n =4;														//size of input array
    int *tree = new int[4*n+1];                                    //array to store the segment tree
    int index = 1;													//index of 1st node
    int s =0,e=n-1;
    buildTree(tree,a,index,s,e);									//now tree has been built
    
    cout<<query(tree,index,s,e,1,2)<<endl;
    updateNode(tree,index,s,e,1,5);
    updateNode(tree,index,s,e,2,50);
    //updateNode(tree,index,s,e,3,100);
	cout<<query(tree,index,s,e,2,3)<<endl;
	updateRange(tree,index,s,e,1,3,10);
	cout<<query(tree,index,s,e,1,2)<<endl;
    return 0;
}
