#define N 100010
#define M 22
int tree[M][N+1];
int aleft[M][N+1];
int c[N+10];
int n,m;

void build(int dep,int l,int r)
{
	if(l==r)
	{
		tree[dep+1][l]=tree[dep][l];
		return ;
	}
	int mid=(l+r)>>1;
	int x=c[mid];
	int cont=0;
	repf(i,l,r)
		if(tree[dep][i]<x)
			cont++;
	int newl=l,newr=mid+1;
	repf(i,l,r)
	{
		if(tree[dep][i]<x)
			tree[dep+1][newl++]=tree[dep][i];
		else if(tree[dep][i]==x && cont<mid)
			tree[dep+1][newl++]=x,cont++;
		else
			tree[dep+1][newr++]=tree[dep][i];
		aleft[dep][i]=aleft[dep][l-1]+newl-l;//全部是向左边的
	}
	build(dep+1,l,mid);
	build(dep+1,mid+1,r);
}
int find(int dep,int L,int R,int l,int r,int t)
{
	if(l==r)
		return tree[dep][l];
	int mid=(L+R)>>1;
	int Lf=aleft[dep][r]-aleft[dep][l-1];//left
	int Rf=(l-L)-(aleft[dep][l-1]-aleft[dep][L-1]);//right
	if(Lf>=t)
	{//cout<<"SDF"<<endl;
		//L-1+aleft[dep][l]-aleft[dep][L-1];//big error
		//the right and error is very different 
		//when aleft[dep][l]==aleft[dep][L-1];
		return find(dep+1,L,mid,aleft[dep][l-1]+L-aleft[dep][L-1],aleft[dep][r]+L-1-aleft[dep][L-1],t);
	}
	else
		return find(dep+1,mid+1,R,mid+Rf+1,mid+Rf+(r-l+1)-Lf,t-Lf);
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		repf(i,1,n)
			scanf("%d",&tree[0][i]),
			c[i]=tree[0][i];
		sort(c+1,c+n+1);
		build(0,1,n);
		int x,y,r;
		while(m--){
			scanf("%d%d%d",&x,&y,&r);
			printf("%d\n",find(0,1,n,x,y,r));
		}
	}
}


