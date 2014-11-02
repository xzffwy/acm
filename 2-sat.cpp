#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <cmath>
#include <algorithm>
#include<iostream>
#include<queue>
using namespace std;
#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define N 100
struct pp{
public:
	int n,m;
	int dfn[N*2+10],low[N*2+10],sign[N*2+10],con[N*2+10];
	int len,ror,tot,col,sstack[N*2+10];
	int pre[N*2+10];
	int vec[N*2+10][N*2+10];
	int flag[N*2+10];
	int point[N*2+10];
	int cont[N*2+10];
	struct node{
		int y,pre,x;
	};
	node a[N*2+10];
	void init()
	{
		len=0;
		ror=1; tot=1;col=0;
		memset(pre,-1,sizeof(pre));
		memset(dfn,0,sizeof(dfn));
		memset(low,-1,sizeof(low));
	}
	void addpage(int x,int y)
	{
		a[len].x=x;
		a[len].y=y;
		a[len].pre=pre[x];
		pre[x]=len++;
	}
	void dfs(int s)//direction
	{
		dfn[s]=low[s]=ror++;
		sstack[tot++]=s;
		sign[s]=true;
		for(int i=pre[s]; i!=-1; i=a[i].pre)
		{
			int y=a[i].y;
			if(dfn[y]==0)
			{
				dfs(y);
				low[s]=min(low[s],low[y]);
			}else if(sign[y]==true)
				low[s]=min(low[s],low[y]);
		}
		if(dfn[s]==low[s]){
			++col;
			while(sstack[--tot]!=s){
				sign[sstack[tot]]=false;
                con[sstack[tot]]=col; 
			}
			sign[s]=false;
			con[s]=col;
		}
	}
	bool judge()
	{
		rep(i,n)//rang is 0~n-1 
		  if(con[2*i]==con[2*i+1])
			  return false;
		return true;
	}
	void do_col(){
		memset(flag,0,sizeof(flag));
		memset(cont,0,sizeof(cont));
		repf(i,1,col)
			vec[i][0]=0;
		int len=m*2+1;//边的长度，由于确定了个顶点，所以多加了一条边
		rep(i,len)
			if(con[a[i].x]!=con[a[i].y])
			{
				//加边的时候反向
			    cont[con[a[i].x]]++;
				vec[con[a[i].y]][++vec[con[a[i].y]][0]]=con[a[i].x];
			}
		rep(i,n){
	       point[con[2*i]]=con[2*i+1];		
		   point[con[2*i+1]]=con[2*i];
		}
		queue<int>q;
		repf(i,1,col)
			if(cont[i]==0)
				q.push(i);
		while(!q.empty()){
			int x=q.front(); q.pop();
			if(flag[x]==0)
				flag[x]=1,flag[point[x]]=2;
			for(int i=1; i<=vec[x][0]; ++i)
			{
				int y=vec[x][i];
				cont[y]--;
				if(cont[y]==0){
					q.push(y);
				}
			}
		}
	}
	void print(){//输出和新娘一边的但是要保持新郎那边的没有通奸
		int p=flag[con[1]];
		repf(i,1,n-1){
			if(flag[con[2*i]]==p)
				printf("%dh ",i);
			else printf("%dw ",i);
		}
		printf("\n");
	}
	
};
pp sa;
int n,m;
char s[20];
void fun(char s[])
{
	int len=strlen(s);
	int x[3]={0,0,0},j=0;
	rep(i,len)
		if(s[i]>='0' && s[i]<='9')
			x[j]=x[j]*10+s[i]-'0';
		else if(s[i]=='h')
			x[j]=2*x[j],++j;
		else if(s[i]=='w') 
			x[j]=x[j]*2+1,++j;
	sa.addpage(x[0],x[1]^1);
	sa.addpage(x[1],x[0]^1);
}
int main()
{
	while(scanf("%d%d",&n,&m) && n!=0 && m!=0)
	{
		sa.init();
		sa.n=n;//is important and easy to ignore
		sa.m=m;
		getchar();
		while(m--)
		{
			gets(s);
			fun(s);
		}
		sa.addpage(1,0);//bride is must
		rep(i,2*n)
			if(sa.dfn[i]==0)
				sa.dfs(i);
		if(!sa.judge())
		{
			puts("bad luck");
			continue;
		}
			sa.do_col();
		sa.print();
	}
}


