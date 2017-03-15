#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#include<string.h>
#include<sstream>
using namespace std;

#define Npart  40
#define Nstage 50
#define Ntime 100
#define dt 0.25
#define vmax 4.00
#define h 4.00

double x[200];
double v[200];
double f[200];
int activate[100];
int fixd[100];



void init(double x[200], double v[200]){
	
	double k=0.0;
	for(int i=0;i<Npart;i++){		
		if(i<5){
			x[0]=6.5;
			x[1]=7.0;
			x[2]=7.5;
			x[3]=8.0;
			x[4]=8.5;
			x[i+Npart]=0.0;
			v[i]=0.0;
			v[i+Npart]=0.0;
			fixd[i]=i;
			activate[i]=i;
		}
		else{	
			x[i]=0.0;	
			fixd[i]=0.0;
			activate[i]=i;
			k=((double)rand()/(1*(double)RAND_MAX))*0.975;

			x[i+Npart]=k;
			v[i+Npart]=0.0;
			v[i]=vmax*k*k/(h*h);
		}
//		cout<<"x[i] is=  "<<x[i]<<"     y[i]"<<x[i+Npart]<<"     v[ i]=  " <<v[i]<<"    v[y]=   "<<v[i+Npart]<<endl;
	}
}


int output(double x[200], double v[200], double t){

return 0;
}

int checkactive(int i){
		for(int j=0;j<Npart;j++){
				if(activate[j]==j){
					return 1;
				}
		}
return 0;
}

int calcForces( ){
double f1[200],f2[200],f3[200];
double dx,dy,r,r2,alpha,mu,r1,r0;
int active;

alpha=600.00;
mu=0.00001;

r0=h/100;
r1=10*r0;

	for(int i=0;i<2*Npart;i++){
		f[i]=0.0;
		f1[i]=0.0;
		f2[i]=0.0;
		f3[i]=0.0;
	}

	for(int i=0;i<Npart;i++){
			for(int j=0;j<Npart;j++){
				if(j==i) continue;
				dx=x[i]-x[j];
				dy=x[i+Npart]-x[j+Npart];
				r2=dx*dx+dy*dy;
				r=sqrt(r2);
				active=checkactive(i);
				if (r<r1 and active==1 and fixd[i]==0.0) {
					f3[i]+=-1*10.01*(r-2*r0)*(dx/r);
					f3[i+Npart]+=-1*10.01*(r-2*r0)*(dy/r);
					activate[i]=i;
				}
				else {f3[i]+=0.0;f3[i+Npart]+=0.0;activate[i]=0.0;}


			}






			f1[i]=alpha*vmax*pow((x[i+Npart]/h),2);
			f2[i]=-1*mu*v[i];
			f2[i+Npart]=-1*mu*v[i+Npart];
			f[i]=f1[i]+f2[i]+f3[i];
			f[i+Npart]=f2[i+Npart]+f3[i+Npart];


			if(((sqrt((x[i]-6.5)*(x[i]-6.5)+x[i+Npart]*x[i+Npart])-2*r0)<0.001) or ((sqrt((x[i]-7.7)*(x[i]-7.7)+x[i+Npart]*x[i+Npart])-2*r0)<0.001)or ((sqrt((x[i]-8.3)*(x[i]-8.3)+x[i+Npart]*x[i+Npart])-2*r0)<0.001)){
//						if((r-2*r0)<0.001){
											fixd[i]=i;
											v[i]=0.0;
											v[i+Npart]=0.0;
											f[i]=0.0;
											f[i+Npart]=0.0;

										}

			}
	
return 0;
}


int main(){
double t=0.0;
double vi[200];
double xi[200];
double alp;
ofstream myfile;
init(x,v); //initialization



for (int k=0;k<251;k++){    //timeloop
		
	for(int i=0;i<2*Npart;i++){ //init stage temporary array
			xi[i]=x[i];
			vi[i]=v[i];
		}
			
cout<<"time loop "<<k<<endl;	
    
    std::ostringstream fileNameStream;
		if(k%10==0)
			{	fileNameStream <<"file"<< k << ".dat";
				std::string fileName = fileNameStream.str();
				myfile.open(fileName.c_str());
			}
		for(int i=0;i<Nstage;i++){
			alp=dt/(Nstage-1+i);
			calcForces( );
			for (int j=0;j<Npart;j++){

				 xi[j]=(x[j]+alp*v[j]);//cout<<"xi "<<xi[j]<<" v[j] "<<v[j]<<"  j "<<j<<endl;
				 if(xi[j]>10.00){xi[j]=0.00;xi[j+Npart]=((double)rand()/(5*(double)RAND_MAX));}
				 xi[j+Npart]=x[j+Npart]+alp*v[j+Npart];
				 if(xi[j+Npart]>h) {xi[j+Npart]=((double)rand()/(1*(double)RAND_MAX));vi[j+Npart]=-1*vi[j+Npart];}
				 if(xi[j+Npart]<0) {xi[j+Npart]=0.0;}
				 vi[j]=v[j]+alp*f[j];
				 vi[j+Npart]=v[j+Npart]+alp*f[j+Npart];
				 //cout<<"xi_y "<<xi[j+Npart]<<" vi[j+Npart] "<<vi[j+Npart]<<"  j "<<j<<endl;
			}
		}

		for (int i=0;i<Npart;i++){

			if(i<5 or fixd[i]==i){
				v[i]=0.0;
				v[i+Npart]=0.0;
				x[i]=x[i];
				x[i+Npart]=x[i+Npart];

//				cout<<"v is "<<v[i]<<" i"<<i<<endl;
			}

			else{
				x[i]=xi[i];
				v[i]=vi[i];
				x[i+Npart]=xi[i+Npart];
				v[i+Npart]=vi[i+Npart];
			}


//cout<<"x[i] is=  "<<x[i]<<"        y[i]"<<x[i+Npart]<<"        v[ x]=      " <<v[i]<<"       v[y]=   "<<v[i+Npart]<<endl;
		}

		t=t+dt;
		for(int i=0;i<Npart;i++){
//			cout<<"x[i] is=  "<<x[i]<<"        y[i]"<<x[i+Npart]<<"        v[ x]=      " <<v[i]<<"       v[y]=   "<<v[i+Npart]<<endl;
					}

		for(int p=0;p<Npart;p++){
			myfile<<x[p]<<"      "<<x[p+Npart]<<"  "<<v[p]<<"   "<<v[p+Npart]<<endl;
		}
		myfile.close();
	}
	
	output(x,v,t);

}
