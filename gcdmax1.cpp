#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

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
	tree[index]= __gcd(tree[2*index],tree[2*index+1]);
	return;
}

//function to query the segment tree for RMQ
int query(int *tree,int index,int s,int e,int qs,int qe)
{
	//base case: if query range is outside the node range
	if(qs>e || s>qe)
		return 0;
	//complete overlap
	if(s>=qs && e<=qe)
		return tree[index];
	//now partial overlap case is executed
	int m = (s+e)/2;
	int left_ans = query(tree,2*index,s,m,qs,qe);
	int right_ans = query(tree,2*index+1,m+1,e,qs,qe);
	return __gcd(left_ans,right_ans);
}

bool f(int a[],int si,int n,int *tree,int index,int s,int e,int k)
{
	int g=0;
	for(int i=0;i<=(n-si);i++)
	{
		g = query(tree,index,s,e,i,i+si-1);
		if(g>=k)
			return true;
	}
	return false;
}

int b_search(int a[],int n,int *tree,int index,int s,int e,int k)
{
	int low=1,high=n,mid,res=0;
	while(low<=high)
	{
		mid = low+(high-low)/2;
		if(f(a,mid,n,tree,index,s,e,k))
		{
			res=mid;
			low = mid+1;
		}
		else
			high=mid-1;
	}
	return res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    cin>>n>>k;
    int a[n];
    for(int i=0;i<n;i++)
    	cin>>a[i];
    int *tree = new int[4*n+1];                                    //array to store the segment tree
    int index = 1;													//index of 1st node
    int s =0,e=n-1;
	buildTree(tree,a,index,s,e); 
    cout<<b_search(a,n,tree,index,s,e,k)<<endl;
    return 0;
}
