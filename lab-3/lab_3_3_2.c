#include "stdio.h"
int main(){
  int num;
  scanf("%d", &num);
  for(int i=1;i<=2*num-1;i++){
    for(int j=1;j<=2*num-1;j++){
      if((i>=1 && i<=num-1) && (j<=i || j>=2*num-i))printf("*");
      else if((i>=1 && i<=num-1) && (j>i && j<2*num-1-j-1))printf(" ");
      else if(i==num)printf("*");
      else if((i>num) && (j<=num*2-1-i+1 || j>=i))printf("*");
      else printf(" ");
    }
    printf("\n");
  }
}
