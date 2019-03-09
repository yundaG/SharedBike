#include<iostream>
#include<string>
#include<cmath>
#define MAXNUM 1000 
#define PI 3.14
#define SIZE 200  //地图 
#define UNITX 20  //每格
#define UNITY 6.5
using namespace std;
struct arch{
	double lx;
	double ly;
	double area;
	int kind;
	int popu;
	string name;
}; 
struct arscore{
	int x,y;
	double score;
};
struct arch building[MAXNUM];
struct arscore pscore[SIZE*SIZE];
double score[SIZE][SIZE]={0};
int topn;
double distance(double a,double b,double c,double d){//地图 
	double x=a-c;
	x*=UNITX;
	double y=b-d;
	y*=UNITY;
	return pow(x*x+y*y,0.5);
}
void score0(double lx,double ly,double area,int popu){//小区评分 
	double r=pow(area/UNITX/UNITY,0.5);
	double x1=lx-r/2;
	double x2=lx+r/2;
	double y1=ly-r/2;
	double y2=ly+r/2;
	int m1=(int)(lx-30+0.5); 
	int m2=(int)(lx+30+0.5);
	int n1=(int)(ly-90+0.5);
	int n2=(int)(ly+90+0.5);
	double k=2*log(popu),d;
	for(int i=max(m1,0);i<=m2;i++){
		for(int j=max(n1,0);j<=n2;j++){
			if(i>=x1&&i<=x2&&j>=y1&&j<=y2){
				continue;
			}
			d=distance(i,j,lx,ly);
			score[i][j]+=k/d;
		}
	}
}
void score1(double lx,double ly,double area,double popu){//学校评分 
	double r=pow(area/UNITX/UNITY,0.5);
	double x1=lx-r/2;
	double x2=lx+r/2;
	double y1=ly-r/2;
	double y2=ly+r/2;
	int m1=(int)(lx-50+0.5);//半径 
	int m2=(int)(lx+50+0.5);
	int n1=(int)(ly-150+0.5);
	int n2=(int)(ly+150+0.5);
	double k=log(popu),d;
	for(int i=max(m1,0);i<=m2;i++){
		for(int j=max(n1,0);j<=n2;j++){
			if(i>=x1&&i<=x2&&j>=y1&&j<=y2){
				continue;
			}
			d=distance(i,j,lx,ly);
			score[i][j]+=k/d;
		}
	}
}
int isin(int x,int y){
	int flag=0;
	for(int i=0;i<topn;i++){
		if(pscore[i].x==x&&pscore[i].y==y){
			flag=1;
			break;
		}
	}
	return flag;
}
void bestway(double sx,double sy,double dx,double dy){
	double mindis=distance(sx,sy,dx,dy)/2;
	double md1,md2;
	md1=mindis;
	md2=mindis;
	int x1=-1,y1=-1,x2=-1,y2=-1;
	int m1=(int)(sx-30+0.5);
	int m2=(int)(sx+30+0.5);
	int n1=(int)(sy-90+0.5);
	int n2=(int)(sy+90+0.5);
	for(int i=m1;i<=m2;i++){
		for(int j=n1;j<=n2;j++){
			if(isin(i,j)==0){
				continue;
			}
			if(distance(i,j,sx,sy)<md1){
				md1=distance(i,j,sx,sy);
				x1=i;
				y1=j;
			}
		}
	}
	int p1=(int)(dx-30+0.5);
	int p2=(int)(dx+30+0.5);
	int q1=(int)(dy-90+0.5);
	int q2=(int)(dy+90+0.5);
	for(int i=p1;i<=p2;i++){
		for(int j=q1;j<=q2;j++){
			if(isin(i,j)==0){
				continue;
			}
			if(distance(i,j,dx,dy)<md2){
				md2=distance(i,j,dx,dy);
				x2=i;
				y2=j;
			}
		}
	}
	if(x1==-1||x2==-1){
		cout<<"建议步行"<<endl;
	}
	else{
		cout<<"步行"<<md1<<"m至("<<x1<<","<<y1<<")取车；"<<endl;
		cout<<"骑行"<<distance(x1,y1,x2,y2)<<"m至("<<x2<<","<<y2<<")放车；"<<endl;
		cout<<"步行"<<md2<<"m至目的地。"<<endl; 
	}
}
int main(){
	string a;
	double lx,ly,area;
	int kind,popu;
	int popusum=0;
	int count=0;
	cout<<"请输入建筑，#号结束："<<endl;
	cin>>a;
	while(a!="#"){
		cout<<"请输入横坐标"<<endl;
		cin>>lx;
		cout<<"请输入纵坐标"<<endl;
		cin>>ly;
		cout<<"请输入建筑种类（0代表小区，1代表学校）"<<endl;
		cin>>kind;
		cout<<"请输入建筑面积"<<endl;
		cin>>area;
		cout<<"请输入人口数"<<endl;
		cin>>popu;
		building[count].kind=kind;
		building[count].lx=lx;
		building[count].ly=ly;
		building[count].name=a;
		building[count].popu=popu;
		building[count].area=area;
		popusum+=popu;
		count++;
		cout<<"请输入建筑，#号结束："<<endl;
		cin>>a;
	}
	for(int i=0;i<count;i++){
		if (building[i].kind==0){//小区 
			score0(building[i].lx,building[i].ly,building[i].area,building[i].popu);
		}
		else if(building[i].kind==1){//学校 
			score1(building[i].lx,building[i].ly,building[i].area,building[i].popu);			
		}
	}
	int n=0;
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			pscore[n].x=i;
			pscore[n].y=j;
			pscore[n].score=score[i][j];
			n++;
		}
	}
	int k;
	struct arscore t;
	for(int i=0;i<n;i++){
		k=i;
		for(int j=i+1;j<n;j++){
			if(pscore[k].score<pscore[j].score){
				t=pscore[k];
				pscore[k]=pscore[j];
				pscore[j]=t;
			}
		}
	}
	topn=popusum/1000;
	double scoresum=0;
	for(int i=0;i<topn;i++){
		scoresum+=pscore[i].score;
	}
	double numpers=popusum/10/scoresum;
	cout<<"围栏状况如下："<<endl;
	for(int i=0;i<topn;i++){
		cout<<"("<<pscore[i].x<<ends<<pscore[i].y<<")"<<ends;
		cout<<"车辆数目："<<ends;
		cout<<(int)(pscore[i].score*numpers+1)<<endl;
	}
	return 0;
}
