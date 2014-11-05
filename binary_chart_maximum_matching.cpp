#define N 1025
class pp{
	public:
		vector<int>vec[N+10];
		bool sign[N+10];
		int next[N+10];
		int n,m;
		void init()
		{
			repf(i,1,n) 
				vec[i].clear();
		}
		void addpage(int x,int y)
		{
			vec[x].push_back(y);
		}
		bool dfs(int s)
		{
			rep(i,vec[s].size())
			{
				int r=vec[s][i];
				if(sign[r]==false)
				{
					sign[r]=true;
					if(next[r]==-1 || dfs(next[r]))
					{
						next[r]=s;
						return true;
					}
				}
			}
			return false;
		}
		int fun()
		{
			memset(next,-1,sizeof(next));
			int ans=0;
			repf(i,1,n)
			{
				memset(sign,false,sizeof(sign));
				if(dfs(i))
					ans++;
			}
			return ans;
		}

};
pp sa;

int n,m;
int sign[N*2];
char s[12];
int main()
{
	while(scanf("%d%d",&m,&n) && n)
	{
		memset(sign,false,sizeof(sign));
		int j=0;
		rep(i,n)
		{
			scanf("%s",s);
			int t=0,k=0;
			rep(i,m)
			{
				if(s[i]=='*')
					t=1,k=k<<1;
				else
					k=(k<<1)+s[i]-'0',t=t<<1;
			}
			sign[j++]=k;
			if(t>0)
				sign[j++]=k|t;
		}
		sort(sign,sign+j);
		j=unique(sign,sign+j)-sign;
		sa.init();
		sa.n=j;		
		rep(i,j)
			repf(k,0,j-1)
			{
				int r=sign[i]^sign[k];
				while((r&1)==0 && r!=0)
					r=r>>1;
				if(r==1)
					sa.addpage(i+1,k+1);
			}
		int ans=sa.fun();
		printf("%d\n",j-ans/2);
	}
	return 0;
}



