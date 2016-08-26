#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define CHROMO 20
#define GENE 4
#define CROSS 3
#define MUTATE 0
#define MAX 30
//a+2b+3c+4d=30
int CHROM[CHROMO][GENE];
int FIT[CHROMO];
int PARENT[2][4];
int GENERATION = 0;
int min1=0, min2=1, max1=0, max2=1;
void init_POPU();
void POPULATE();
int EVALUATE();
void calc_FIT();
void DISCARD();
void new_GEN();
int FUNC(int,int,int,int);
void CROSSOVER(int,int,int);
void CROSSOVER_(int,int);
void MUTATE_(int);

void main()
{
clrscr();
init_POPU();
while(GENERATION<30)
	{
	cout<<"GEN:"<<GENERATION+1<<endl;
	calc_FIT();
	new_GEN();
	//DISCARD();
	//POPULATE();
	GENERATION++;
	}
//cout<<FIT[0]<<" "<<FIT[1]<<" "<<FIT[2]<<" "<<FIT[3];
getch();
}
void init_VALUES()
{
for(int i=0; i<CHROMO; i++)
	for(int j=0; j<GENE; j++)
		CHROM[i][j] = 0;
for(i=0; i<GENE; i++)
	FIT[i] = 0;
}
void init_POPU()
{
srand(time(0));
for(int i=0; i<CHROMO; i++)
{
	for(int j=0; j<GENE; j++)
	{
		CHROM[i][j] = rand() % MAX;
		//cout<<CHROM[i][j]<<" ";
	}
//cout<<endl;
}
}
void calc_FIT()
{
for(int i=0; i<CHROMO; i++)
	{
	int tot = FUNC(CHROM[i][0],CHROM[i][1],CHROM[i][2],CHROM[i][3]);
	FIT[i] = abs(30-tot);
	cout<<CHROM[i][0]<<" "<<CHROM[i][1]<<" "<<CHROM[i][2]<<" "<<CHROM[i][3]<<"-"<<FIT[i]<<endl;
	}
}
int FUNC(int a, int b, int c, int d)
{
return(a+(2*b)+(3*c)+(4*d));//=30
}
void new_GEN()
{
DISCARD();

getch();
clrscr();
POPULATE();
}
void POPULATE()
{
if((CHROM[min1][0]+(30-FUNC(CHROM[min1][0],CHROM[min1][1],CHROM[min1][2],CHROM[min1][3])))>0)
	{
	CHROM[min1][0]+=(30-FUNC(CHROM[min1][0],CHROM[min1][1],CHROM[min1][2],CHROM[min1][3]));
	}
if((CHROM[min2][0]+(30-FUNC(CHROM[min2][0],CHROM[min2][1],CHROM[min2][2],CHROM[min2][3])))>0)
	{
	CHROM[min2][0]+=(30-FUNC(CHROM[min2][0],CHROM[min2][1],CHROM[min2][2],CHROM[min2][3]));
	}
CROSSOVER_(max1,max2);
}
int EVALUATE()
{
for(int i=0; i<CHROMO; i++)
	if(FUNC(CHROM[i][0],CHROM[i][1],CHROM[i][2],CHROM[i][3])==30)
		{
		cout<<endl<<"Solution:"<<CHROM[i][0]<<" "<<CHROM[i][1]<<" "<<CHROM[i][2]<<" "<<CHROM[i][3];
		return 1;
		}
return 0;
}
void DISCARD()
{
static int min1_=0, min2_=0;
max1=0; max2=0;
for(int i=0; i<CHROMO; i++)
	{if(FIT[i]!=0){min1=i; break;}}
for(i=min1+1; i<CHROMO; i++)
	{if(FIT[i]!=0){min2=i; break;}}
for(i=0; i<CHROMO; i++)
	{
	if(FIT[i]!=0)
	{
	if(FIT[i]<FIT[min1]) {min2=min1; min1=i;}
	if(FIT[i]>FIT[min1]&&FIT[i]<FIT[min2]) min2=i;
	}
	}
cout<<endl<<"Parents:"<<min1<<" "<<min2<<endl<<"\t"<<min1_<<" "<<min2_;;
if((min1_==min1)&&(min2_==min2))
	{
	MUTATE_(max1);
	MUTATE_(max2);
	}
for(i=1; i<CHROMO; i++)
	{
	if(FIT[i]>FIT[max1]) {max2=max1; max1=i;}
	if(FIT[i]<FIT[max1]&&FIT[i]>FIT[max2]) max2=i;
	}
cout<<endl<<"Child:"<<max1<<" "<<max2;
for(i=0; i<GENE; i++)
	{
	PARENT[0][i] = CHROM[min1][i];
	PARENT[1][i] = CHROM[min2][i];
	}
/*
getch();
clrscr();
*/
min1_=min1; min2_=min2;
}
void CROSSOVER(int ch1, int ch2, int index)
{
for(int i=0; i<GENE; i++)
	{
	if(i>=index)
		{
		static int temp = CHROM[ch1][i];
		CHROM[ch1][i] = CHROM[ch2][i];
		CHROM[ch2][i] = temp;
		}
	}
}
void CROSSOVER_(int ch1, int ch2)
{
CHROM[ch1][2] = PARENT[0][2];
CHROM[ch1][3] = PARENT[0][3];
CHROM[ch2][2] = PARENT[1][2];
CHROM[ch2][3] = PARENT[1][3];
}
void MUTATE_(int ch)
{
srand(time(0));
for(int j=0; j<GENE; j++)
	CHROM[ch][j] = rand()%MAX;
}
