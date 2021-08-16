#include<stdio.h>
int main(){
  int num;
  printf("Enter number : ");
  scanf("%d", &num);
  if(num<=1)printf("ERROR");
  else{
    for(int i=1;i<=num;i++){
      for(int j=1;j<=num;j++){
        if(j==1 || j==num)printf("*");
        else if((i==1 || i==num) && (j!=1 || j!=num))printf("*");
        else if((i!=0 || i!=num) && (j!=1 || j!=num))printf(" ");
      }
      printf("\n");
    }
  }
  return 0;
}
