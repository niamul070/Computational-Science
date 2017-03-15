#include<iostream>
#include <math.h>
#include <fstream>
#include<string.h>
#include <cstdlib>
#include<sstream>
using namespace std;


class Node{
public:
	int id;
	double x;
	double y;
	double z;
};

double convertToDouble(std::string const& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
	  return -1;
	return x;
}


double areacalc(Node cordinate[],int a,int b,int c){
	double cross,x1,y1,x2,y2,x3,y3;
	double ab,ac;
	x1=cordinate[a-1].x;
	//cout<<"x1 "<<x1;
	y1=cordinate[a-1].y;
	x2=cordinate[b-1].x;
	//cout<<"x2 "<<x2;
	y2=cordinate[b-1].y;
	x3=cordinate[c-1].x;
	y3=cordinate[c-1].y;
	ab=(x2-x1)*(y3-y1);
	ac=(x3-x1)*(y2-y1);
	cross=(fabs(ab-ac)/2);
	//cout<<"cross "<<cross<<endl;

}

int main(){

Node cordinate[913];
double M[913][913];
double N[913];
double R[913];
double V2[913];
double value[913];
double P[913];
double x,y,z;
double area;
int count = 0;
int position,position_two;
int i =0;
int x1,y1,z1;
int index=0;
int field=0;
double total;
std::string buffer,str;
std::string a,b,c;

ofstream myfile;
myfile.open ("result.dat");
ifstream fin("grid0");
ifstream phi("phi0.1");

for (int k=0;k<913;k++){
	for (int l=0;l<913;l++){
		M[k][l]=0.0;
		//Ml[k][l]=0.0;
		//cout<<M[k][l]<<"  ";
	}
	 cout<<endl;
}


for (int p=0;p<913;p++){
		N[p]=0.0;
		R[p]=0.0;
}


while(!phi.eof()){
	
	getline(phi ,str, '\n');
    value[field]=convertToDouble(str);
   // cout<<field<<endl;
	field++;
	
	}


 while (!fin.eof()) {
 		
		  getline(fin, buffer, '\n');
		   count++;  
		  position = buffer.find(' ', 0 );		  
		  if (count>=5 and count <918)
		  {
		  		cordinate[i].id=i+1;
		  		//cout<<"index"<<cordinate[i].id<<"  ";
				x = convertToDouble (buffer.substr(0,position));
				cordinate[i].x=x;
				//cout<<"x"<<cordinate[i].x<<"  ";
				position_two = buffer.find(' ',position + 1);
	
				if (position_two!=-1)
				{
					  y = convertToDouble (buffer.substr(position+1,(position_two-position-1)));
					  
					  cordinate[i].y=y;
					   //cout<<"y"<<cordinate[i].y<<"  ";
					  z = convertToDouble (buffer.substr(position_two + 1,(buffer.length()-position_two-1)));
					  cordinate[i].z=z;
					 // cout<<"z"<<cordinate[i].z<<" \n";
					  i++;
				  }
				  
			}
			
			if (position!=-1 and count>921 and count<2604)
		  {
				a = buffer.substr(0,position);
				x1=atoi(a.c_str());
				//connect[x];
				//cout<<"index:  "<<cordinate[x1-1].id<<"  "<<"x1: "<<x1<<"x1-1.x" <<cordinate[x1-1].x<<endl;
				position_two = buffer.find(' ',position + 1);
	
				if (position_two !=-1)
				{
					 b = buffer.substr(position+1,(position_two-position-1));
					 y1=atoi(b.c_str());
					 // node n =connect[y1];
					// cout<<" index: "<<cordinate[y1-1].id<<"  "<<y1<<"y1-1.x  "<<cordinate[y1-1].x<<endl;
					  c = buffer.substr(position_two + 1,(buffer.length()-position_two-1));
					  z1=atoi(c.c_str());
					// cout<<"index: "<<cordinate[z1-1].id<<"  "<<z1<<"z1-1.x:  "<<cordinate[z1-1].x<<endl;
					  index=index+3;
				  }
				 // cout<<x1<<endl;
				 area=areacalc(cordinate,x1,y1,z1);
				 
				  M[x1-1][x1-1]=M[x1-1][x1-1]+(2.0*(area/12.0));
				  M[x1-1][y1-1]=M[x1-1][y1-1]+(1.0*(area/12.0));
				  M[x1-1][z1-1]=M[x1-1][z1-1]+(1.0*(area/12.0));
				  
				  M[y1-1][x1-1]=M[y1-1][x1-1]+(1.0*(area/12.0));
				  M[y1-1][y1-1]=M[y1-1][y1-1]+(2.0*(area/12.0));
				  M[y1-1][z1-1]=M[y1-1][z1-1]+(1.0*(area/12.0));
				  
				  M[z1-1][x1-1]=M[z1-1][x1-1]+(1.0*(area/12.0));
				  M[z1-1][y1-1]=M[z1-1][y1-1]+(1.0*(area/12.0));
				  M[z1-1][z1-1]=M[z1-1][z1-1]+(2.0*(area/12.0));
				  
				  
				   N[x1-1]=N[x1-1]+0.1667*((((-(cordinate[z1-1].y-cordinate[x1-1].y)+(cordinate[y1-1].y-cordinate[x1-1].y)))*value[x1-1])+((cordinate[z1-1].y-cordinate[x1-1].y)*value[y1-1])-((cordinate[y1-1].y-cordinate[x1-1].y)*value[z1-1]));
				  N[y1-1]=N[y1-1]+0.1667*((((-(cordinate[z1-1].y-cordinate[x1-1].y)+(cordinate[y1-1].y-cordinate[x1-1].y)))*value[x1-1])+((cordinate[z1-1].y-cordinate[x1-1].y)*value[y1-1])-((cordinate[y1-1].y-cordinate[x1-1].y)*value[z1-1]));
				  N[z1-1]=N[z1-1]+0.1667*((((-(cordinate[z1-1].y-cordinate[x1-1].y)+(cordinate[y1-1].y-cordinate[x1-1].y)))*value[x1-1])+((cordinate[z1-1].y-cordinate[x1-1].y)*value[y1-1])-((cordinate[y1-1].y-cordinate[x1-1].y)*value[z1-1]));
				  
				  R[x1-1]=R[x1-1]+0.1667*(((((cordinate[z1-1].x-cordinate[x1-1].x)-(cordinate[y1-1].x-cordinate[x1-1].x)))*value[x1-1])-((cordinate[z1-1].x-cordinate[x1-1].x)*value[y1-1])+((cordinate[y1-1].x-cordinate[x1-1].x)*value[z1-1]));
				  R[y1-1]=R[y1-1]+0.1667*(((((cordinate[z1-1].x-cordinate[x1-1].x)-(cordinate[y1-1].x-cordinate[x1-1].x)))*value[x1-1])-((cordinate[z1-1].x-cordinate[x1-1].x)*value[y1-1])+((cordinate[y1-1].x-cordinate[x1-1].x)*value[z1-1]));
				  R[z1-1]=0.1667*(((((cordinate[z1-1].x-cordinate[x1-1].x)-(cordinate[y1-1].x-cordinate[x1-1].x)))*value[x1-1])-((cordinate[z1-1].x-cordinate[x1-1].x)*value[y1-1])+((cordinate[y1-1].x-cordinate[x1-1].x)*value[z1-1]));
				 
				
				//cout<<"area of triangle is "<<area<<endl;  
			}
		
			
}																				//end while
	

for (int k=0;k<913;k++){
		for (int l=0;l<913;l++){
			//cout<<M[k][l]<<"  ";
		}
		//cout<<endl;
	}


	for (int k=0;k<913;k++){
		total=0.0;
		for (int l=0;l<913;l++){
			total=total+M[k][l];
			
			if(k!=l)
				M[k][l]=0.0;
		}
		M[k][k]=total;
		//cout<<endl;
	}
	

for (int k=0;k<913;k++){
		for (int l=0;l<913;l++){
			if(k==l)
				M[k][k]=1/M[k][k];
			//N[k]=N[k]+N[k]*M[l][k];
			//cout<<M[k][l]<<"  ";
		}
		//cout<<endl;
	}


for (int k=0;k<913;k++){
		N[k]=M[k][k]*N[k];
		R[k]=M[k][k]*R[k];
		V2[k]=N[k]*N[k]+R[k]*R[k];
//	myfile<<cordinate[k].x<<"    "<<cordinate[k].y<<"    "<<N[k]<<"    "<<R[k]<<"  "<<endl;
	//	myfile<<pow(V2[k],0.5)<<endl;
	}	
//myfile<<"pressure"<<endl;
for(int k=0;k<913;k++){
	V2[k]=0.5*V2[k];
	myfile<<V2[k]<<endl;
}
myfile.close();
return 0;
}


