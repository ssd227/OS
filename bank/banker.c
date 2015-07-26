/*
* banker algorithm
* author :ssd227
* date: 2015.7.23
*/
#include<string.h>
#include<stdio.h>

#define N 4
#define M 3

//global variable
//*******************
int resource[M];
int available[M];
int request[M];
int p;
int claim[N][M];
int alloc[N][M];
int need[N][M];

//********************
void input();
int safe();

//********************
int main(){
  input();
  
  p--;
  int err_flag_1=0;
  for(int i=0;i<M;i++){
    if((alloc[p][i]+request[i])>claim[p][i]){
      err_flag_1=1;
      break;
    }
  }
  int err_flag_2=0;
  for(int i=0;i<M;i++){
    if(request[i]>available[i]){
      err_flag_2=1;
      break;
    }
  }


  /*  for(int i=0;i<3;i++)
    printf("%d ",available[i]);

  printf("\n");
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      // printf("%d ",alloc[i][j]);
      printf("%d ",claim[i][j]);
    }
    printf("\n");
  }
  // printf("\nis safe : %d",safe());
  */
  
  if(err_flag_1){
    printf("ERROR:What you need is more than what you claim.");
    printf("That is ridiculous!!\n");
    return 1;
  }
  else if(err_flag_2){
    printf("Your request is not enough now.\n");
    printf("Process %d is suspend\n",p+1);
    return 1;
  }
  else{    //pudate a new state
    for(int i=0;i<M;i++){
      alloc[p][i]+=request[i];
      available[i]-=request[i];
    }
  }

  //here is a big introduction /////////////////////
    printf("\nthe Available matrix :\n");
  for(int i=0;i<3;i++)
    printf("%d ",available[i]);
    
    printf("\n\nthe request matrix :\n");
    for(int i=0;i<3;i++)
        printf("%d ",request[i]);

  printf("\n\nthe Alloc matrix :\n");
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      printf("%d ",alloc[i][j]);
      //printf("%d ",claim[i][j]);
    }
    printf("\n");
  }
    
    printf("\n\nthe Claim matrix :\n");
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            printf("%d ",claim[i][j]);
        }
        printf("\n");
    }
  printf("\nis safe : %d\n",safe());
  //////////////////////////////////////////////////

  
  if(safe()){
    printf("\nThe request is allowed.\tThere is a new state.\n");
  }
  else{  //rollback
     for(int i=0;i<M;i++){
      alloc[p][i]-=request[i];
      available[i]+=request[i];
    }
    printf("\nROLLBACK:\tProcess %d is suspend\n",p+1);
  }

  return 0;
}//End Main


//  judge the current state  ////////////////
int safe(){
  int currentavail[M];
  memcpy(&currentavail[0],&available[0],sizeof(int)*M);
  
  int ProcessIsDown[N]={1,1,1,1}; 
  int possible =1;
  while (possible){
    int flag_found=0;
    int pk;
    for(int i=0;i<N;i++){
      if(ProcessIsDown[i]){
	int flag=1;
	for(int j=0;j<M;j++){
	  if((claim[i][j]-alloc[i][j])>currentavail[j]){
	    flag=0;
	    break;
	  }
	}
	if(flag==1){
	  flag_found=1;
	  pk=i;
	  ProcessIsDown[pk]=0;
	  break;
	}
      } 
    }//End : outer for
    if(flag_found){
      for(int j=0;j<M;j++){
	currentavail[j]+=alloc[pk][j];
      }
    }
    else{
      possible=0;
    }
  }//End :while
  
  int is_null=0;  //or is safe
  for(int i=0;i<N;i++){
    if(ProcessIsDown[i]){
      is_null++;
    }
  }

  return is_null==0? 1:0;
  
}//End :fun safe


//  scanf the nessary data //////////////////
void input(){
  
  for(int i=0;i<M;i++){
    scanf("%d",&resource[i]);
  }
  scanf("%d",&p);
  for(int i=0;i<M;i++){
    scanf("%d",&request[i]);
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      scanf("%d",&claim[i][j]);
      // printf("%d",claim[i][j]);
    }
    //printf("\n");
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      scanf("%d",&alloc[i][j]);
      //printf("%d",alloc[i][j]);
    }
    //printf("\n");
  }

  //compute the available
  for(int j=0;j<M;j++){
    available[j]=resource[j];
    for(int i=0;i<N;i++){
      available[j]-=alloc[i][j];
    }
  }

  
  
}
  
  
  
