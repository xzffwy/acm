#define N 110
#define Er1(x,y) ((midl>=x)&&(midr>=y))//x1,y1
#define Er2(x,y) ((x>midl) && (midr>=y))//x2,y1
#define Er3(x,y) ((midl>=x) && (y>midr))//x1,y2
#define Er4(x,y) ((x>midl) && (y>midr))//x2,y2
#define E(s,l1,r1,l2,r2) (a[s].x1>=l1 && a[s].y1>=r1 && a[s].x2<=l2 && a[s].y2<=r2)
#define area(s) ((a[s].y2-a[s].y1+1)*(a[s].x2-a[s].x1+1))

struct node{
	int x1,y1,x2,y2,sign,sum;
};
node a[N*1600];

int n=100;
bool cross(int s,int l1,int r1,int l2,int r2)
{
     int x1=max(a[s].x1,l1);
	 int y1=max(a[s].y1,r1);
	 int x2=min(a[s].x2,l2);
	 int y2=min(a[s].y2,r2);
	 if(x1>x2 || y1>y2)
		 return false;
	 return true;
}

void build(int s,int l1,int r1,int l2,int r2)
{
	a[s].x1=l1; a[s].y1=r1;
	a[s].x2=l2; a[s].y2=r2;
	a[s].sum=0;
	a[s].sign=0;
	if(l2==l1 && r1==r2)
		return ;
	int midl=(l1+l2)>>1;
	int midr=(r1+r2)>>1;
	if(Er1(l1,r1))
		build(4*s,l1,r1,midl,midr);
	if(Er2(l2,r1))
		build(4*s+1,midl+1,r1,l2,midr);	
	if(Er3(l1,r2))
		build(4*s+2,l1,midr+1,midl,r2);
	if(Er4(l2,r2))
		build(4*s+3,midl+1,midr+1,l2,r2);
}
void pu(int s)
{
	if(a[s].sign==-1)
		a[4*s].sum=area(4*s),
			a[4*s+1].sum=area(4*s+1),
			a[4*s+2].sum=area(4*s+2),
			a[4*s+3].sum=area(4*s+3);
	else
		a[4*s].sum=a[4*s+1].sum=a[4*s+2].sum
			=a[4*s+3].sum=0;
	a[4*s].sign=a[4*s+1].sign=a[4*s+2].sign
		=a[4*s+3].sign=a[s].sign;
	a[s].sign=0;
	a[s].sum=0;

}
void fresh(int s,int l1,int r1,int l2,int r2,int sign)
{
	if(E(s,l1,r1,l2,r2))
	{
		a[s].sign=sign;
		if(sign==-1)
			a[s].sum=area(s);
		else 
			a[s].sum=0;
		return ;
	}
	if(a[s].sign!=0)
		pu(s);
	int midl=(a[s].x1+a[s].x2)>>1;
	int midr=(a[s].y2+a[s].y1)>>1;
	a[s].sum=0;
	if(Er1(a[s].x1,a[s].y1)){
		if(cross(4*s,l1,r1,l2,r2))
			fresh(4*s,l1,r1,l2,r2,sign);
		a[s].sum+=a[4*s].sum;
	}
	if(Er2(a[s].x2,a[s].y1)){
		if(cross(4*s+1,l1,r1,l2,r2))
			fresh(4*s+1,l1,r1,l2,r2,sign);
		a[s].sum+=a[4*s+1].sum;
	}
	if(Er3(a[s].x1,a[s].y2)){
		if(cross(4*s+2,l1,r1,l2,r2))
			fresh(4*s+2,l1,r1,l2,r2,sign);
		a[s].sum+=a[4*s+2].sum;
	}
	if(Er4(a[s].x2,a[s].y2)){
		if(cross(4*s+3,l1,r1,l2,r2))
			fresh(4*s+3,l1,r1,l2,r2,sign);
		a[s].sum+=a[4*s+3].sum;
	}
}
int find(int s,int l1,int r1,int l2,int r2)
{
	if(E(s,l1,r1,l2,r2))
		return a[s].sum;
	if(a[s].sign!=0)
		pu(s);
	int midl=(a[s].x1+a[s].x2)>>1;
	int midr=(a[s].y1+a[s].y2)>>1;
	a[s].sum=0;
	int t=0;
	if(Er1(a[s].x1,a[s].y1)){
		if(cross(4*s,l1,r1,l2,r2))
			t+=find(4*s,l1,r1,l2,r2);
		a[s].sum+=a[4*s].sum;
	}
	if(Er2(a[s].x2,a[s].y1)){
		if(cross(4*s+1,l1,r1,l2,r2))
			t+=find(4*s+1,l1,r1,l2,r2);
		a[s].sum+=a[4*s+1].sum;
	}
	if(Er3(a[s].x1,a[s].y2)){
		if(cross(4*s+2,l1,r1,l2,r2))
			t+=find(4*s+2,l1,r1,l2,r2);
		a[s].sum+=a[4*s+2].sum;
	}
	if(Er4(a[s].x2,a[s].y2)){
		if(cross(4*s+3,l1,r1,l2,r2))
			t+=find(4*s+3,l1,r1,l2,r2);
		a[s].sum+=a[4*s+3].sum;
	}
	return t;
}
int main()
{
	int test;
	scanf("%d",&test);
	char s[10];
	int x1,y1,x2,y2;
	int sign;
	build(1,1,1,n,n);
	while(test--)
	{
		scanf("%s%d%d%d",s,&x1,&y1,&x2);
		y2=y1+x2-1;
		x2=x1+x2-1;
		if(s[0]=='T'){
			int t=find(1,x1,y1,x2,y2);
			cout<<t<<endl;
			continue;
		}
		else if(s[0]=='B')
			sign=-1;
		else
			sign=1;
		fresh(1,x1,y1,x2,y2,sign);
	}
}

