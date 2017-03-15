#include<iostream>
#include <math.h>
#include <fstream>
#include<string.h>
#include <cstdlib>
#include<sstream>
#include <vector>
using namespace std;



class Node{
public:
	int id;
	double x;
	double y;
	double z;
	
};

struct Cell{
	int cell_id;
	double area;
	int type;
};

static Node cordinate[17266];
vector <Cell> triangle;
static double connectivity[103245];
int neighbor[34415*3];
double node_n[34415*3];


double convertToDouble(std::string const& s)
{
	std::istringstream i(s);
	double x;
	if (!(i >> x))
	  return -1;
	return x;
}


double areacalc(Node cordinate[],int a,int b,int c){
	double cross,x1,y1,z1,x2,y2,z2,x3,y3,z3=0.0;
	double ab,ac,bc,s=0.0;
	x1=cordinate[a-1].x;
	y1=cordinate[a-1].y;
	z1=cordinate[a-1].z;
	x2=cordinate[b-1].x;
	y2=cordinate[b-1].y;
	z2=cordinate[b-1].z;
	x3=cordinate[c-1].x;
	y3=cordinate[c-1].y;
	z3=cordinate[c-1].z;
	ab=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
	ac=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3));
	bc=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2));
	s=(ab+ac+bc)/2.0;
	cross=sqrt(s*(s-ab)*(s-bc)*(s-ac));
return cross;
}

int growth( ){
int new_type[34415];
int old_type[34415];
int n1,n2,n3=0;
int temp,id=0;
double prob,probc,can_area,area,sur_area,na1,na2,na3,ca1,ca2,ca3=0.0;
ofstream myfile;
//ofstream myfile2;
//myfile2.open("area");
for(int k=0;k<34415;k++) { new_type[k]=1;old_type[k]=1;}
new_type[1]=2;
new_type[50]=2;
new_type[34414]=2;
new_type[34410]=2;

for(int time=0;time<200;time++){
				
		for(int ik=0;ik<34415;ik++){
			n1=neighbor[ik*3];
			n2=neighbor[ik*3+1];
			n3=neighbor[ik*3+2];
						
			if(n1 !=-1)
				na1=triangle[n1-1].area;
			else na1=0.0;
			
			if(n2 !=-1)
				na2=triangle[n2-1].area;
			else na2=0.0;
			
			if(n3 !=-1)
				na3=triangle[n3-1].area;
			else na3=0.0;
	
			sur_area=na1+na2+na3;
	
			if(n1 != -1 and triangle[n1-1].type==2)
				ca1=triangle[n1-1].area;
			else ca1=0.0;

			if(n2 !=-1 and triangle[n2-1].type==2)
				ca2=triangle[n2-1].area;
		    else ca2=0.0;

			if(n3 !=-1 and triangle[n3-1].type==2)
				ca3=triangle[n3-1].area;
			else ca3=0.0;

			can_area=ca1+ca2+ca3;
			prob = (double)rand() / (double)RAND_MAX ;
	
			if(triangle[ik].type==1){
				probc=0.05*(can_area/(triangle.at(ik).area+sur_area));
							
				if(prob<probc){
					new_type[ik]=2;
					
				}		
			}
			
			 if(triangle[ik].type==2 and  triangle[n1-1] .type != 1 and  triangle[n2-1].type !=1 and  triangle[n3-1].type !=1 and n1 !=-1 and n2 !=-1 and n3 != -1){
				probc=0.05;
							
				if(prob<probc){
					new_type[ik]=3;
					
				}		
			}
			
			 if(triangle[ik].type==3){
				probc=0.05;
							
				if(prob<probc){
					new_type[ik]=4;
				
				}		
			}
		
		
		can_area=0.0;
		sur_area=0.0;
		prob=0.0;
		probc=0.0;
		
			
		
	
	} //end element loop
		
	for(int nn=0;nn<34415;nn++){	
				
				if(triangle[nn].type!=new_type[nn]) cout<<triangle[nn].type<<" "<<nn<<" "<<time<<endl;
				triangle[nn].type=new_type[nn];
			}
			
			std::ostringstream fileNameStream;
			if(time%50==0)
				{	fileNameStream <<"cell_c"<< time << ".dat";
					std::string fileName = fileNameStream.str();
				    myfile.open(fileName.c_str());				
					for(int np=0;np<34415*3;np+=3){		
						
						myfile<<node_n[np]<<"   "<<node_n[np+1]<<"  "<<node_n[np+2]<<"   "<<triangle[np/3].type<<endl;
						//myfile<<triangle.at(np).type<<endl;
					}
				
			myfile.close();			
	       }
//myfile2.close();
}	// end time loop

return 0;
}

int find_neighbor(int neighbor[34415*3],double connectivity[103245]){
int count1=0;
double node1,node2,node3=0.0;
ofstream myfile1;
//myfile1.open("neb1");
for(int in=0;in<103245;in+=3){
	node1=connectivity[in];
	node2=connectivity[in+1];
	node3=connectivity[in+2];
	
	count1=in;
	for(int ik=0;ik<103245;ik+=3){
		if(ik==in) continue;
		if((node1==connectivity[ik] and node2==connectivity[ik+1]) or (node1==connectivity[ik]  and node2==connectivity[ik+2]) or (node1==connectivity[ik+1] and node2==connectivity[ik]) or (node1==connectivity[ik+1] and node2==connectivity[ik+2]) or (node1==connectivity[ik+2] and node2==connectivity[ik]) or (node1==connectivity[ik+2] and node2==connectivity[ik+1])){
			neighbor[in]=ik/3+1;
		//	count1++;
		}
		
		if((node1==connectivity[ik] and node3==connectivity[ik+1]) or (node1==connectivity[ik]  and node3==connectivity[ik+2]) or (node1==connectivity[ik+1] and node3==connectivity[ik]) or (node1==connectivity[ik+1] and node3==connectivity[ik+2]) or (node1==connectivity[ik+2] and node3==connectivity[ik]) or (node1==connectivity[ik+2] and node3==connectivity[ik+1])){
			neighbor[in+1]=ik/3+1;
		//	count1++;
		}
		
		 if((node3==connectivity[ik] and node2==connectivity[ik+1]) or (node3==connectivity[ik]  and node2==connectivity[ik+2]) or (node3==connectivity[ik+1] and node2==connectivity[ik]) or (node3==connectivity[ik+1] and node2==connectivity[ik+2]) or (node3==connectivity[ik+2] and node2==connectivity[ik]) or (node3==connectivity[ik+2] and node2==connectivity[ik+1])){
			neighbor[in+2]=ik/3+1;
		//	count1++;
		}
		
		count1++;
		
		//cout<<count1<<endl;
	}
//myfile1<<neighbor[in]<<"  "<<neighbor[in+1]<<"  "<<neighbor[in+2]<<endl;
}
myfile1.close();
return 0;
}

int node_calc(Node cordinate[],int a,int b,int c,int elem){
	double cross,x1,y1,z1,x2,y2,z2,x3,y3,z3;
	double xn,yn,zn;
	x1=cordinate[a-1].x;
	y1=cordinate[a-1].y;
	z1=cordinate[a-1].z;
	x2=cordinate[b-1].x;
	y2=cordinate[b-1].y;
	z2=cordinate[b-1].z;
	x3=cordinate[c-1].x;
	y3=cordinate[c-1].y;
	z3=cordinate[c-1].z;
	
	xn=(x1+x2+x3)/3.0;
	yn=(y1+y2+y3)/3.0;
	zn=(z1+z2+z3)/3.0;
	node_n[(elem)*3]=xn;
	node_n[(elem)*3+1]=yn;
	node_n[(elem)*3+2]=zn;

return 0;
}

int main(){
double x,y,z;
double area;
int count= 0;
int count1=0;
int position,position_two;
int elem=0;
int x1,y1,z1;
int index=0;
int field,size=0;
int ii=0;
double total;
double sur_area;
double node1,node2,node3;
std::string buffer,str;
std::string a,b,c;
ifstream fin("face");



 while (!fin.eof()) { // this is point
 		
		  getline(fin, buffer, '\n');
		   count++;  
		  position = buffer.find(' ', 0 );		  
		  if (count>=5 and count <17271)
		  {
		  		cordinate[ii].id=ii+1;

				x = convertToDouble (buffer.substr(0,position));
				cordinate[ii].x=x;

				position_two = buffer.find(' ',position + 1);
	
				if (position_two!=-1)
				{
					  y = convertToDouble (buffer.substr(position+1,(position_two-position-1)));
					  
					  cordinate[ii].y=y;
					  z = convertToDouble (buffer.substr(position_two + 1,(buffer.length()-position_two-1)));
					  cordinate[ii].z=z;
					   ii++;
				  }
				  
			}
			
			if (position!=-1 and count>17274 and count<51690)
		  {
				a = buffer.substr(0,position);
				x1=atoi(a.c_str());
				connectivity[index]=x1;
				position_two = buffer.find(' ',position + 1);
	
				if (position_two !=-1)
				{
					 b = buffer.substr(position+1,(position_two-position-1));
					 y1=atoi(b.c_str());
					 connectivity[index+1]=y1;
					  c = buffer.substr(position_two + 1,(buffer.length()-position_two-1));
					  z1=atoi(c.c_str());
					  connectivity[index+2]=z1;
					  index=index+3;
				  }
				 area=areacalc(cordinate,x1,y1,z1);				
				Cell c;
				c.cell_id=elem+1;
				c.area=area;
				c.type=1;
				triangle.push_back(c);
				node_calc(cordinate,x1,y1,z1,elem);				
				elem++;	
				
			}
		
			
}																				//end while
	
find_neighbor(neighbor,connectivity);



triangle.at(1).type=2;
triangle.at(50).type=2;
triangle.at(34414).type=2;
triangle.at(34410).type=2;


			
size=growth( );
return 0;
}


