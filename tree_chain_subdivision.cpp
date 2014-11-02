#define N 20000
class pp{
	public:
		struct node{
			int y,v,pre;
		};
		node a[N*2+10];
		int ans;
		int pre[N+10];
		int point[N+10];
		int top[N+10];
		int son[N+10],fat[N+10];
		int dep[N+10];
		int valuep[N+10],value[N+10];//point to edge
		int len,len2;
		int sign;//sign operation
		void addedge(int x,int y,int v)
		{
			a[len].y=y;
			a[len].pre=pre[x];
			a[len].v=v;
			pre[x]=len++;
		}
		void init()
		{
			len=0;
			len2=0;
			 valuep[1]=0;
			fat[1]=1;top[1]=1;
			memset(pre,-1,sizeof(pre));
			memset(son,-1,sizeof(son));
		}
		void dfs1(int s,int fa)//find max len son
		{
			int Max=-1,x;
			for(int i=pre[s]; i!=-1; i=a[i].pre)
			{
				int y=a[i].y;
				if(y==fa) continue;
				fat[y]=s;
				dfs1(y,s);
				if(point[y]>Max)//reuse
				{
					Max=point[y];
					x=i;//rember array sign
				}
			}
			if(Max==-1){
				son[s]=-1;
				point[s]=1;
			}
			else{
				son[s]=x;
				point[s]=Max+1;
			}
		}
		void dfs2(int s,int fa,int h)
			//find the position of every node
		{
			point[s]=len2++; dep[s]=h;
			if(son[s]!=-1){
				top[a[son[s]].y]=top[s];
				value[len2]=son[s];
				valuep[a[son[s]].y]=len2;
				dfs2(a[son[s]].y,s,h+1);
			}
			for(int i=pre[s]; i!=-1; i=a[i].pre)
			{
				int y=a[i].y;
				if(y==a[son[s]].y || y==fa) continue;
				top[y]=y;
				value[len2]=i;
				valuep[y]=len2;
				dfs2(y,s,h+1);
			}
		}
		struct node2{//sign just for pu,not for Max and Min
			int l,r,Max,sign,Min;
		};
		node2 b[N*4];
		void build(int s,int l,int r)
		{
			b[s].l=l; b[s].r=r;
			b[s].sign=1;
			if(l==r)
			{
				b[s].Max=a[value[l]].v;
				b[s].Min=a[value[l]].v;
				return ;
			}
			int mid=(l+r)>>1;
			build(s*2,l,mid);
			build(2*s+1,mid+1,r);
			b[s].Max=max(b[2*s].Max,b[2*s+1].Max);
			b[s].Min=min(b[2*s].Min,b[2*s+1].Min);
		}
		void exchange(int s)
		{
			int temp=b[s].Max;
			b[s].Max=-b[s].Min;
			b[s].Min=-temp;
		}
		void pu(int s){
			if(b[s].sign==-1){
			b[2*s].sign*=b[s].sign;
			b[2*s+1].sign*=b[s].sign;
			exchange(2*s);
			exchange(2*s+1);
			}
			b[s].sign=1;
		}
		void fresh(int s,int l,int r,int v)
		{
			if(b[s].l>=l && b[s].r<=r)
			{
				if(sign==1)
				{
					b[s].Max=v,b[s].sign=1;
					b[s].Min=b[s].Max; 
				}
				else if(sign==-1)//exchanged
				{
					b[s].sign=-b[s].sign;
					exchange(s);
				}
				else
					    ans=max(ans,b[s].Max);
				return ;
			}
			pu(s);
			int mid=(b[s].l+b[s].r)>>1;
			if(r<=mid)
				fresh(2*s,l,r,v);
			else if(l>mid)
				fresh(2*s+1,l,r,v);
			else{
				fresh(2*s,l,r,v),
				fresh(2*s+1,l,r,v);
			}
			b[s].Max=max(b[2*s].Max,b[2*s+1].Max);
			b[s].Min=min(b[2*s].Min,b[2*s+1].Min);
		}
		//all change will have segment one ,but it is
		//not the point
		void ope(int l,int r,int v)
		{
			int topl=top[l],topr=top[r];
			while(top[l]!=top[r])
			{
				if(dep[topl]<dep[topr]){
					swap(topl,topr);
					swap(l,r);
				}	   
				fresh(1,valuep[topl],valuep[l],v);//del firsh node
				l=fat[topl];
				topl=top[l];
			}
			if(dep[l]>dep[r])
				swap(l,r);
			if(l!=r)
			fresh(1,valuep[l]+1,valuep[r],v);
		}
		int query(int l,int r)
		{
			ans=INT_MIN;
			ope(l,r,-1);
			return ans;
		}
};
pp sa;

int n;
int main()
{
	int test;
	scanf("%d",&test);
	int x,y,v;
	char s[10];
	int l,r,sign;
	while(test--)
	{
		scanf("%d",&n);
		sa.init();
		rep(i,n-1)
			scanf("%d%d%d",&x,&y,&v),
			sa.addedge(x,y,v),
			sa.addedge(y,x,v);
		sa.dfs1(1,-1);
		sa.dfs2(1,-1,1);
		sa.build(1,1,n-1);
		while(scanf("%s",s) && s[0]!='D')
		{
			scanf("%d%d",&l,&r);
			if(s[0]=='Q'){//ask ,l and r is node
				sa.sign=0;
				printf("%d\n",sa.query(l,r));
				continue;
			}
			else if(s[0]=='N') //node l and r's edge negative
			{
				v=-1;
				sa.sign=-1;
			}
			else{
				sa.sign=1;//the lth edge is be set v
				v=r;
				l--;
				r=sa.a[l*2+1].y;
				l=sa.a[l*2].y;
			}
			sa.ope(l,r,v);
		}	
	}
}


