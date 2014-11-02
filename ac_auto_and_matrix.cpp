#define NN 4//决定ac自动机的字母的个数的
#define NM 50 //数组的大小
#define mod 100000
int n,m;
int nnum;//结构体只能访问全局，所以定义在了这里
class pp;

class pp{
	public:
		struct node{
			int point,sign,num;//num为最终节点标记
			//sign标记是否是结束节点
			int next[NN];
		};
		int tot;
		node a[10000];//
		void init()
		{
			a[0].point=0;//指向上一个的
			a[0].sign=0;
			a[0].num=-1;
			tot=1;
			memset(a[0].next,-1,sizeof(a[0].next));
		}
		static int change(char s)
		{
			switch(s){
				case 'A': return 0;
				case 'T': return 1;
				case 'C': return 2;
				default: return 3;
			}
		}
		void tree(char s[])
		{
			int len=strlen(s);
			int q=0;
			rep(i,len)
			{
				int x=change(s[i]);//转换为数字
				if(a[q].next[x]==-1){
					memset(a[tot].next,-1,sizeof(a[tot].next));
					a[tot].sign=0;
					a[q].next[x]=tot;
					a[tot].num=-1;
					q=tot++;
				}
				else q=a[q].next[x];
				if(i==len-1)
					a[q].sign=1;
			}
		}
		int fail(int u,int k)
		{
			if(a[u].next[k]!=-1){
				if(a[a[u].next[k]].sign) return-1;
				return a[u].next[k];
			}
			if(u==0) return 0;
			return fail(a[u].point,k);
		}
		void build()
		{
			queue<int>q;
			q.push(0);
			while(!q.empty())
			{
				int u=q.front(); q.pop();
				if(a[u].sign!=1){
					rep(i,NN)
						if(a[u].next[i]!=-1){
							q.push(a[u].next[i]);
							if(u==0)
								a[a[u].next[i]].point=0;
							else{
								int y=fail(a[u].point,i);
								if(y==-1) 
									a[a[u].next[i]].sign=-1;
								else a[a[u].next[i]].point=y;
							}
						}
				}
				else{
					rep(i,NN)
						if(a[u].next[i]!=-1)
						{
							q.push(a[u].next[i]);
							a[a[u].next[i]].sign=1;
						}
				}

			}
		}
		//简历状态转移矩阵
		struct no{
			ll mp[NM][NM];
			no(){
				rep(i,nnum) rep(j,nnum) this->mp[i][j]=0;
			}
			no (ll mp[NM][NM]){
				rep(i,nnum) rep(j,nnum) this->mp[i][j]=mp[i][j];
			}
			no operator *(no &a)
			{
				no c;
				rep(i,nnum)
					rep(j,nnum)
					rep(k,nnum){
						c.mp[i][j]+=(this->mp[i][k]*a.mp[k][j])%mod;
						c.mp[i][j]%=mod;
					}
				return c;
			}
		};
		int find(int x,int y)
		{
			if(a[x].next[y]!=-1){
				if(!a[a[x].next[y]].sign) return a[x].next[y];
				else return -1;
			}
			if(x==0)
				return 0;
			return find(a[x].point,y);
		}

		no mul(no b,int n)
		{
			//	cout<<n<<endl;
			if(n==1)
				return b;
			no a=mul(b,n/2);
			if(n%2==0)
				return a*a;
			return b*a*a;
		}
		int extract(){
			nnum=0;
			no mu;
			memset(mu.mp,0,sizeof(mu.mp));
			rep(i,tot)
			{
				if(a[i].sign) continue;
				if(a[i].num==-1) a[i].num=nnum++;
				rep(j,NN){
					int y=find(i,j);
					if(y!=-1)
					{
						if(a[y].num==-1) a[y].num=nnum++;
						mu.mp[a[i].num][a[y].num]++;
					}
				}
			}
			mu=mul(mu,n);
			int ans=0;
			rep(j,nnum){
				ans+=mu.mp[0][j];
				ans%=mod;
			}
			return ans;
		}

};
pp sa;
char s[12];
int main()
{//m个字符串，求字符串长度为n并且符合题意的字符串中不包含这m个字符串
	while(~scanf("%d%d",&m,&n))
	{
		sa.init();
		rep(i,m){
			scanf("%s",s);
			sa.tree(s);
		}
		sa.build();
		int ans=sa.extract();
		printf("%d\n",ans);
	}
}



