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
int available[M]={0,1,1};
int request[M];
int p;
int claim[N][M]={{3,2,2},{6,1,3},{3,1,4},{4,2,2}};
int alloc[N][M]={{2,0,1},{5,1,1},{2,1,1},{0,0,2}};
int need[N][M];

//********************
void input();
int safe();

//********************
int main(){

  for(int i=0;i<3;i++)
    printf("%d ",available[i]);

  printf("\n");
  for(int i=0;i<4;i++){
    for(int j=0;j<3;j++){
      printf("%d ",alloc[i][j]);
      //printf("%d ",claim[i][j]);
    }
    printf("\n");
  }
  printf("\nis safe : %d",safe());

  return 0;
}//End Main


//****judge the current state
int safe(){
  int currentavail[M];
  memcpy(&currentavail[0],&available[0],sizeof(int)*M);

  // for(int i=0;i<3;i++)
  //  printf("%d ",currentavail[i]);

  int ProcessIsDown[N]={1,1,1,1}; 
  int possible =1;
  while (possible){
    int flag_found=0;
    int pk=-1;
    for(int i=0;i<N;i++){
      if(ProcessIsDown[i]){
	int flag=1;
	for(int j=0;j<M;j++){
	  if((claim[i][j]-alloc[i][j])>currentavail[j]){
	    flag=0;
	    
	    printf("for i=%d j=%d  flag=%d \n",i,j,flag);
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
	printf("cur_avail[%d]=%d  ",j,currentavail[j]);
      }
      printf("\n");
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

  if(is_null==0)
    return 1;
  else
    return 0;
  //return is_null==0? 1:0;
  
}//End :fun safe


//****scanf the nessary data
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
      resource[j]-=alloc[i][j];
    }
  }

  
  
}
  
  
  
