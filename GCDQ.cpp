#include <bits/stdc++.h>
using namespace std;


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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
    	int n,k;
    cin>>n>>k;
    int a[n];
    for(int i=0;i<n;i++)
    	cin>>a[i];
    int tree[4*n+1];                                    //array to store the segment tree
    int index = 1;													//index of 1st node
    int s =0,e=n-1;
	buildTree(tree,a,index,s,e); 
	while(k--)
	{
		int l,r,l1=-1,l2=-1,r1=-1,r2=-1;
		cin>>l>>r;
		if(l!=1)
		{
			l1=0;r1=l-2;
		}
		if(r!=n)
		{
			l2 = r;
			r2 = n-1;
		}
		if(l1==-1 && l2!=-1)
		{
			cout<<query(tree,index,s,e,l2,r2)<<endl;
		}
		else
			if(l1!=-1 && l2==-1)
			{
				cout<<query(tree,index,s,e,l1,r1)<<endl;
			}
			else
			{
				int g1 = query(tree,index,s,e,l2,r2);
				int g2 = query(tree,index,s,e,l1,r1);
				cout<<__gcd(g1,g2)<<endl;
			}
	}

    }
    
    
    return 0;
}
