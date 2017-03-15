#include<iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main(){
int t=0;
double stop=0.0;
double T[100][100];
double Tnew[100][100];
double error[100][100];
double maximum=0.0;
int location;
double vmax=0.0;
double v=0.0;
double k=0.0005;
double deltat=0.25;//0.25 v=0.1 and it<40000
double Lx=5;
double Ly=5;
double grid=100;
double yv=0.6*grid;
double deltax=Lx/grid;
double deltay=Ly/grid;
double a=1/deltax;

ofstream myfile;
myfile.open ("test.dat");

/*set initial condition */
for (int i=0;i<100;i++){
	for(int j=0;j<100;j++){
		T[i][j]=40.0;
		Tnew[i][j]=40.0;
		
		}
   }


/*set niddle temp*/
for (int i=45;i<=55;i++){
	for(int j=10;j<=25;j++){
		T[i][j]=80.0;
	  }
  }

for (t=0;t<=400000;t++){
	maximum=error[0][0];
	/*calculation for convergence */
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if(maximum<error[i][j])
				maximum=error[i][j];
		}
	}
    
	if(maximum<0.00001 && t>1){
	//cout<<"max is "<<T[i][j]<<endl;
	break;
	}
	else{
			/*loop through inner nodes */
			
		for(int i=1;i<=99;i++){
			for(int j=1;j<=99;j++){
							
				if(j>0.5*grid && j< 0.7*grid){
					v=vmax*(1-(pow((j-yv),2)/pow(a,2)));
				
				}
				else v=0.0;
				
				if(j>=10 && j<=25 && i>=45 && i<=55){
							T[i][j]=80.0;	
							Tnew[i][j]=80.0;					
				}
				else{
				Tnew[i][j]=T[i][j]+((k*deltat*(T[i+1][j]-2*T[i][j]+T[i-1][j]))/(deltax*deltax))+((k*deltat*(T[i][j+1]-2*T[i][j]+T[i][j-1]))/(deltay*deltay))-((v*deltat*(T[i][j]-T[i-1][j]))/(deltax))-((v*deltat*(T[i][j]-T[i][j-1]))/(deltay));
				
				}
								
			}	
		}
		
		/*calculate error to check convergence */
		for(int i=0;i<100;i++){
					for(int j=0;j<100;j++){
							error[i][j]=fabs(Tnew[i][j]-T[i][j])/T[i][j];
										
								
													
					}	
				}
		for(int j=60;j<80;j++){
			Tnew[99][j]=Tnew[98][j];
		}
	
	/*loop to update the T of old timestep*/
		for(int i=1;i<100;i++){
			for(int j=1;j<100;j++){
				T[i][j]=Tnew[i][j];
							
				}	
		}
		
		/*update values for boundary nodes in i=grid and j from 0 to 99*/
		
		
  	}																					//end else
} 																	//end t loop


for(int i=0;i<100;i++){
			for(int j=0;j<100;j++){
				if (j==0)
					myfile<<endl;
				else{
					myfile <<Tnew[i][j]<<"     ";
					
					}
				}	
	}																									

myfile.close();

return 0;
}


