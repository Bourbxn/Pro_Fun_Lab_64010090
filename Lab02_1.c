#include<stdio.h>
int main(){
  int num,lst[1000],sizenum=0;
  int fac = 2;
  printf("Enter number : ");
  scanf("%d", &num);
  if(num==1)lst[sizenum++]=1;
  else if(num<=0){fac=num+1;}
  int mainnum=num+1;
  while(fac!=mainnum){
    if(num%fac==0){
      lst[sizenum++]=fac;
      num/=fac;
    }
    else{fac+=1;}
  }
  printf("Factoring Result : ");
  if(num<=0)printf("ERROR");
  else{
    for(int i=0;i<sizenum;i++){
      if(i==sizenum-1)printf("%d",lst[i]);
      else{printf("%d x ", lst[i]);}
    }
  }
  return 0;
}
