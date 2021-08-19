#include "stdio.h"
int main(){
  int num1,num2,fac=2,sumfac=1;;
  printf("Enter first number : ");
  scanf("%d", &num1);
  printf("Enter second number : ");
  scanf("%d", &num2);
  while(fac<=num1 || fac<=num2){
    if(num1%fac==0 && num2%fac==0){
      sumfac*=fac;
      num1/=fac;
      num2/=fac;
    }
    else{fac++;}
  }
  printf("Greatest common divisor = %d",sumfac);
  return 0;
}
