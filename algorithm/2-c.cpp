#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int a[1001][1001];
int main()
{
	int t;
	scanf("%d",&t);
	int n,m,x,y;
	
	while(t--)
	{
		scanf("%d%d%d%d",&m,&n,&x,&y);
		memset(a,0,sizeof(a));
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++){
				int z;
				scanf("%d",&z);
				a[i][j]=a[i-1][j]+a[i][j-1]+z-a[i-1][j-1];
			}
		
		int ans=0;
		for(int i=x;i<=m;i++)
			for(int j=y;j<=n;j++)
				ans=max(ans,a[i][j]-a[i-x][j]-a[i][j-y]+a[i-x][j-y]);
		printf("%d\n",ans);
	}
	return 0;
}
