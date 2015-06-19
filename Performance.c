//Evluating the performance of 80MHz system when compared to that of 40MHz, for increasing number of busy 20MHz channels
//Given total channels Nt = 20, Nb -> busy channels
#include <stdio.h>
#include <math.h>
#include "rngs.h"  
 
 
#define START         0.0              /* initial time                   */
#define STOP      2000000.0              /* terminal (close the door) time */
 
int Equilikely(int a, int b)        
/* ------------------------------------------------
* generate an Equilikely random variate, use a < b
* ------------------------------------------------
*/
{
 return (a + (int) ((b - a + 1) * Random()));
}
int main()
{
int a20[20]={0};//20 MHz channel
int a40[10]={0};//40 MHz channel
int a80[5]={0}; //80 MHz channel
int i,j,k; ​​//index variable
int Nt = 20; ​//Total channels
int Nb ;​​//Total Busy channels
int x, thru40, thru40sum=0, thru40avg, thru80, thru80sum=0, thru80avg, BW40, BW80;
 
SelectStream(2);
PlantSeeds(987654321);
 
printf("\nEnter total number of busy channels out of 20 : ");
scanf("%d",&Nb);
 
i=0;
while(i<STOP)
{
for(j=1;j<=Nt;j++)
​a20[j] =0;
//Allocation of busy channels of 20MHz
for(j=1;j<=Nb;j++)
{
​x = Equilikely(1,20);
​//printf("\n x = %d",x);
​if(a20[x]!=1)
​​a20[x]=1;
​else
​​j--;
}
/*for(j=1;j<=Nt;j++)
{
​printf("\n array a : %d",a20[j]);
}*/
//for 40MHz checking possible Allocations
thru40 = 0;
for(j=1;j<20;j++)
​{
​​if((a20[j]==0)&&(a20[j+1]==0))
​​​{
​​​thru40++;
​​​//printf("\n%d",j);
​​​j++;
​​​}
​​else if(a20[j+1]==1)
​​​{
​​​j++;
​​​}
​}
thru40sum +=thru40;
 
//for 80MHz checking possible Allocations
thru80=0;
for(j=1;j<Nt;j++)
{
​if((a20[j]==0)&&(a20[j+1]==0)&&(a20[j+2]==0)&&(a20[j+3]==0))
​​{
​​thru80++;
​​//printf("\n%d",j);
​​j=j+3;
​​}
​​else if(a20[j+1]==1)
​​{
​​j++;
​​}
​​else if(a20[j+2]==1)
​​{
​​j=j+2;
​​}
​​else if(a20[j+3]==1)
​​{
​​j=j+3;
​​}
}
thru80sum +=thru80;
i++;
}
 
thru40avg=thru40sum/STOP;
thru80avg=thru80sum/STOP;
 
BW40 = thru40avg * 40 / 10;
BW80 = thru80avg * 80 / 5;
 
printf("\nEffective Throughput of 40MHz is : %d",thru40avg);
printf("\nEffective Throughput of 80MHz is : %d\n",thru80avg);
printf("\nEffective Bandwidth of 40MHz is : %d",BW40);
printf("\nEffective Bandwidth of 80MHz is : %d\n",BW80);
 
return 0;
}
