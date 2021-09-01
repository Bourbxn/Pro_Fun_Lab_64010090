#include "stdio.h"
int Plus_digit(int num){
  int sum=0;
  while(num!=0){
    sum+=num%10;
    num/=10;
  }
  num=sum;
  if(num>9)Plus_digit(num);
  else return num;
}

int main(){
  int inpt;
  scanf("%d", &inpt);
  printf("%d", Plus_digit(inpt));
}
