#include "stdio.h"
int main(){
  char sentc[10000];
  scanf("%s", &sentc);
  int i=0;
  while(sentc[++i]!='\0');
  for(int j=0;j<i;j++){
    if(sentc[j]>=48 && sentc[j]<=57){
      if(sentc[j+1]<48 || sentc[j+1]>57){     //Bug && >> ||
        int times=sentc[j]-48;
        for(int k=0;k<times;k++)printf("%c", sentc[j+1]);
        j++;
      }
      else{
        int check=1,times=0,pow10=1;
        while(1){
          if(sentc[j+check]>=48 && sentc[j+check]<=57)check++;
          else{break;}
        }
        for(int k=0;k<check-1;k++)pow10*=10;
        for(int k=j;k<j+check;k++){
          times+=(sentc[k]-48)*pow10;     //Bug sentc[j] >> sentc[k]
          pow10/=10;
        }
        for(int k=0;k<times;k++)printf("%c", sentc[j+check]);
        j+=check;
      }
    }
    else{
      printf("%c", sentc[j]);
    }
  }
}
