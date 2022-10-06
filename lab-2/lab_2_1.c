#include "stdio.h"
int main(){
  int num,lst[1000],sizenum=0,fac=2;
  printf("Enter number : ");
  scanf("%d", &num);
  while(fac<=num){
    if(num%fac==0){
      lst[sizenum++]=fac;
      num/=fac;
    }
    else{fac+=1;}
  }
  printf("Factoring Result : ");
  for(int i=0;i<sizenum;i++){
      if(i==sizenum-1)printf("%d",lst[i]);
      else{
        printf("%d x ", lst[i]);
      }
  }
  return 0;
}
