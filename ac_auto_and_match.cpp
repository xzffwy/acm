/////////////////////////////////////////////////////////////////////////
// File Name: hdoj_2896.cpp
// Author: wang
// mail: 1062239606@qq.com
// Created Time: 2014/11/3 21:22:07
/////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <cstdlib>
#define N 10000
#define NN 130 //决定自动机字母的个数
char s[N+100];
int flag[555];
int n,m;
class pp{
	public:
		struct node{
			int point,sign;
			int next[NN];
		};
		int tot;
		node a[N*100+100];
		void init()
		{
			a[0].point=0;
			a[0].sign=-1;
			tot=1;
			memset(a[0].next,-1,sizeof(a[0].next));
		}
		int change(char s)
		{
			return s-32;//只是字母数字的下移量
		}
		void tree(int num,char s[])
		{
			int len=strlen(s);
			int q=0;
			rep(i,len)
			{
				int x=change(s[i]);
				if(a[q].next[x]==-1)
				{
					memset(a[tot].next,-1,sizeof(a[tot].next));
					a[tot].sign=-1;
					a[tot].point=0;
					a[q].next[x]=tot;
					q=tot++;
				}
				else q=a[q].next[x];
				if(i==len-1)
					a[q].sign=num;
			}
		}
		int fail(int u,int k)
		{
			if(a[u].next[k]!=-1)
				return a[u].next[k];
			if(u==0)
				return 0;
			return fail(a[u].point,k);
		}
		void build()
		{
			queue<int>q;
			q.push(0);
			while(!q.empty())
			{
				int u=q.front(); q.pop();
				rep(i,NN)
					if(a[u].next[i]!=-1){
						q.push(a[u].next[i]);
						if(u==0)
							a[a[u].next[i]].point=0;
						else
							a[a[u].next[i]].point=fail(a[u].point,i);
					}
			}
		}
		void match(char s[])
		{
			int len=strlen(s);
			int u=0;
			rep(i,len)
			{
				int x=change(s[i]);
				while(a[u].next[x]==-1 && u!=0)
					u=a[u].point;
				if(a[u].next[x]==-1) u=0;
				else
				u=a[u].next[x];
				int p=u;
				while(p!=0)
				{
                    if(a[p].sign!=-1)
						flag[a[p].sign]++;
					p=a[p].point;
				}

			}
		}
};
pp sa;
int main()
{
	while(scanf("%d",&n)!=EOF)//找到在匹配串中给的对比串
	{
		sa.init();
		repf(i,1,n)
		{
			scanf("%s",s);
			sa.tree(i,s);
		}
		sa.build();
		int ans=0;
		scanf("%d",&m);
		repf(i,1,m)
		{
			scanf("%s",s);
			memset(flag,0,sizeof(flag));
            sa.match(s);
			int sum=0;
			repf(j,1,n)
				if(flag[j]) sum++;
			if(sum>0)
			{
                printf("web %d:",i);
				repf(j,1,n)
					repf(k,1,flag[j])
						printf(" %d",j);
				printf("\n");
				ans++;
			}
		}
		printf("total: %d\n",ans);
	}
	return 0;

}

