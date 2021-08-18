#include "stdio.h"
int main(){
  int num,sum;
  scanf("%d", &num);
  while(num/10!=0){
    sum=0;
    while(num!=0){
      sum+=num%10;
      num/=10;
    }
    num=sum;
  }
  printf("%d", sum);
  return 0;
}
