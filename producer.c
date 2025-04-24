#include<stdio.h>
int main(){
int buffer[10],bufsize=10,in,out,produce,consume,choice=0;
in=0,out=0,bufsize=10;
while(choice!=3){
printf("\n1.produce\t2.consume\t3.exit");
printf("\nEnter your choice:");
scanf("%d",&choice);
switch(choice){
case 1:
if((in+1)%bufsize==out)
printf("\nBuffer is full");
else{
printf("Enter the value:");
scanf("%d",&produce);
buffer[in]=produce;
in=(in+1)%bufsize;}
break;
case 2:
if(in==out)
printf("\nBuffer is empty");
else{
consume=buffer[out];
printf("\n The consumed value ia %d",consume);
out=(out+1)%bufsize;
}
break;
case 3:
printf("\nExiting program...");
break;
default:
printf("\nInvalid choice. Please try again.");
break;
}}
return 0;}
