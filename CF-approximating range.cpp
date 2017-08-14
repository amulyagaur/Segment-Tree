#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
int tree_max[400001];
int tree_min[400001];
int a[100001];
void buildTree_min(int index,int s,int e)
{
	//base case
	if(s>e)
		return;
	//reached leaf node
	if(s==e)
	{
		tree_min[index]=a[s];
		return ;
	}
	//now build the segment tree in bottom up manner
	int m = (s+e)/2;
	buildTree_min(2*index,s,m);
	buildTree_min(2*index+1,m+1,e);
	tree_min[index]= min(tree_min[2*index],tree_min[2*index+1]);
	return;
}
int query_min(int index,int s,int e,int qs,int qe)
{
	//base case: if query range is outside the node range
	if(qs>e || s>qe)
		return INT_MAX;
	//complete overlap
	if(s>=qs && e<=qe)
		return tree_min[index];
	//now partial overlap case is executed
	int m = (s+e)/2;
	int left_ans = query_min(2*index,s,m,qs,qe);
	int right_ans = query_min(2*index+1,m+1,e,qs,qe);
	return min(left_ans,right_ans);
}
void buildTree_max(int index,int s,int e)
{
	//base case
	if(s>e)
		return;
	//reached leaf node
	if(s==e)
	{
		tree_max[index]=a[s];
		return ;
	}
	//now build the segment tree in bottom up manner
	int m = (s+e)/2;
	buildTree_max(2*index,s,m);
	buildTree_max(2*index+1,m+1,e);
	tree_max[index]= max(tree_max[2*index],tree_max[2*index+1]);
	return;
}

//function to query the segment tree for RMQ
int query_max(int index,int s,int e,int qs,int qe)
{
	//base case: if query range is outside the node range
	if(qs>e || s>qe)
		return INT_MIN;
	//complete overlap
	if(s>=qs && e<=qe)
		return tree_max[index];
	//now partial overlap case is executed
	int m = (s+e)/2;
	int left_ans = query_max(2*index,s,m,qs,qe);
	int right_ans = query_max(2*index+1,m+1,e,qs,qe);
	return max(left_ans,right_ans);
}
bool f(int index,int s,int e,int si,int n)
{
	for(int i=0;i<=(n-si);i++)
	{
		if((query_max(index,s,e,i,i+si-1)-query_min(index,s,e,i,i+si-1))<=1)
			return true;
	}
	return false;
}
int b_search(int index,int s,int e,int n)
{
	int low =1,high=n,mid,res;
	while(low<=high)
	{
		int mid = low+(high-low)/2;
		if(f(index,s,e,mid,n))
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
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    	cin>>a[i];
    int index=1,s=0,e=n-1;
    buildTree_min(index,s,e);
    buildTree_max(index,s,e);
    cout<<b_search(index,s,e,n)<<endl;
    return 0;
}
