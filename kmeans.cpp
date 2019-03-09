#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#define SIZE 100
#define K 4
using namespace std;
struct point{
	double x;
	double y;
};
struct point points[SIZE];
struct point* k[K];
double m[K];
double n[K];
double dis[K];
int length(point* a){
	int c=0;
	for(int i=0;;i++){
		if(a[i].x>0&&a[i].y>0){
			c++;
		}
		else{
			break;
		}
	}
	return c;
}
double distance(struct point a,struct point b){
	double x=a.x-b.x;
	double y=a.y-b.y;
	return pow(x*x+y*y,0.5);
}
int isend(){
	int count=0;
	for(int i=0;i<K;i++){
		if(fabs(k[i][0].x-m[i])<1){
			count++;
		}
		if(fabs(k[i][0].y-n[i])<1){
			count++;
		}
	}
	if(count==2*K){
		return 1;
	}
	else{
		return 0;
	}
}
void kmeans(){
	int count=length(points);
	for(int i=0;i<count;i++){
		for(int j=0;j<K;j++){
			dis[j]=distance(points[i],k[j][0]);
		}
		double mindis=dis[0];
		int min=0;
		for(int a=1;a<K;a++){
			if(dis[a]<mindis){
				mindis=dis[a];
				min=a;
			}
		}
		int l=length(k[min]);
		k[min][l]=points[i];
	}
	for(int i=0;i<K;i++){
		int len=length(k[i]);
		double sumx=0,sumy=0;
		for(int j=1;j<len;j++){
			sumx+=k[i][j].x;
			sumy+=k[i][j].y;
		}
		m[i]=sumx/(len-1);
		n[i]=sumy/(len-1);
	}
	if(isend()==1){
		return;
	}
	else{
		for(int i=0;i<K;i++){
			k[i][0].x=m[i];
			k[i][0].y=n[i];
		}
		kmeans();
	}
}

int main(){
	FILE* fp;
	char str[10];
	int f=0,g=0;
	if((fp=fopen("E:\\sophomore\\大二下\\小创\\test.txt","r"))==NULL){
		cout<<"can't open file"<<endl;
	}
	while(!feof(fp)){
		if(fgets(str,10,fp)!=NULL){
			if(f%2==0){
				points[g].x=atof(str);
				f++;
			}
			else{
				points[g].y=atof(str);
				f++;
				g++;
			}
		}
	}
	srand((unsigned)time(NULL));
	for(int i=0;i<K;i++){
		k[i]=(point*)malloc(SIZE*sizeof(point));
		double r1=rand() /((double)(RAND_MAX)/SIZE);
		double r2=rand() /((double)(RAND_MAX)/SIZE);
		k[i][0].x=r1;
		k[i][0].y=r2;
	}
	kmeans();
	cout<<"初始化数据："<<endl;
	for(int i=0;i<length(points);i++){
		cout<<points[i].x<<","<<points[i].y<<endl;
	}
	cout<<"产生的聚点："<<endl;
	for(int i=0;i<K;i++){
		cout<<k[i][0].x<<","<<k[i][0].y<<endl;
	}
	for(int i=0;i<K;i++){
		free(k[i]);
	}
}
