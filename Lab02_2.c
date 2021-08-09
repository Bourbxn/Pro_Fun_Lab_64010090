#include<stdio.h>
int main(){
  int num1,num2,lsthrm[1000],sizelst=0;
  int horomo=2,sumhrm=1;
  printf("Enter first number : ");
  scanf("%d", &num1);
  printf("Enter second number : ");
  scanf("%d", &num2);
  int mainnum1=num1, mainnum2=num2;
  while(horomo<=mainnum1 || horomo<=mainnum2){
    if(num1%horomo==0 && num2%horomo==0){
      lsthrm[sizelst++]=horomo;
      num1/=horomo;
      num2/=horomo;
    }
    else{horomo++;}
  }
  for(int i=0;i<sizelst;i++)sumhrm*=lsthrm[i];
  printf("Greatest common divisor = ");
  if(mainnum1<=0 || mainnum2<=0)printf("ERROR");
  else{ printf("%d", sumhrm);}
  return 0;
}
