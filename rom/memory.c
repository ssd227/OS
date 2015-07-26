//
//  main.c
//  memory
//
//  Created by ssd227 on 15-7-24.
//  Copyright (c) 2015年 ssd227. All rights reserved.
//
#include<stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Node
{
    int start;
    int big;
    int end;
    struct Node *next;
    
}Node;

//*** global variable  *****
Node* used_head;
Node* unused_head;

//*** fun delcration   *****
void initial();
void join_first();
void join_best();
int creater_random(int a,int b);
void mk_claen();

void work_comp02();
void show();
void insert(Node* T,Node* one);
void connected();
void test();

// START AT HERE/////////////////////////////
//*** main  ***************
int main(int argc, const char * argv[]) {

    initial();
    printf("\n");
    printf("请选择内存分配算法\n\n");
    printf("1:首次适应算法\n");
    printf("2:最佳适应算法\n");
    //function pointer;
    void (*join)();
    
    char input_1;
    input_1=getchar();
    //putchar(input_1);
    
    switch (input_1) {
        case '1':
            join=join_first;
            printf("case 1");
            break;
            
        case '2':
            join=join_best;
            printf("case 2\n");
            break;
            
        default:
            printf("what you input is wrong\n");
            return 1;
            break;
    }

    
    //the core operation
    while(1){
        printf("\n-----------------------------\n");
        printf("1:作业进入内存\n");
        printf("2:随机作业完成\n");
        printf("3:显示物理内存情况\n");
        printf("4:碎片拼接\n");
        printf("5 测试\n");
        printf("请输入:\t");
        getchar();
        
        char input_2;
        input_2=getchar();
        //putchar(input_2);
        
        switch (input_2) {
            case '1':
                join();
                break;
                
            case '2':
                work_comp02();
                break;
                
            case '3':
                show();
                break;
                
            case '4':
                connected();
                break;
                
            case '5':
                test();
                break;
                
            default:
                printf("what you input is wrong\n");
                break;
        }
        
    }
    
    
    return 0;
}

//alternative choice of good result ///////////////////
void test(){
    printf("\nUSED\n");
    Node* p=used_head;
    while (p->next) {
        p=p->next;
        printf("s:%3d \t b:%3d \t e:%3d\n",p->start,p->big,p->end);
    }
    printf("\nUNUSED\n");
    p=unused_head;
    while (p->next) {
        p=p->next;
        printf("s:%3d \t b:%3d \t e:%3d\n",p->start,p->big,p->end);
    }
}

//
void initial(){
    
    used_head=(Node*)malloc(sizeof(Node));
    unused_head=(Node*)malloc(sizeof(Node));
    
    unused_head->start=-20;
    unused_head->end=-10;
    unused_head->next=NULL;
    used_head->next=NULL;
    
    
    //in the begining ,the used is null and the unused is 1-100
    Node* p=(Node*)malloc(sizeof(Node));
    p->start=1;
    p->end=100;
    p->big=100;
    p->next=NULL;
    unused_head->next=p;
    
}

//首次适应函数   //////////////////////
void join_first(){
    //this is the new memory we need for our new process
    Node* new_one=(Node*)malloc(sizeof(Node));
    new_one->big=creater_random(1, 20);
    new_one->next=NULL;
  
    Node* temp=unused_head;
    int suc_fl=0;
    while(temp->next){
        temp=temp->next; //转移到下一个节点
        
        //successful
        if(temp->big>=new_one->big){
            new_one->start=temp->start;
            new_one->end=new_one->start+new_one->big-1;
            
            temp->start+=new_one->big;
            temp->big-=new_one->big;
            
            //将newone 插入到已使用链中 used_head
            insert(used_head,new_one);
          
            printf("内存分配成功\n");
            suc_fl=1;
            mk_claen();
            break;
        }
    }
    if(suc_fl==0){
        printf("内存不足，分配不成功\n");
    }
}


//最佳适应函数  //////////////////////
void join_best(){
    //this is the new memory we need for our new process
    Node* new_one=(Node*)malloc(sizeof(Node));
    new_one->big=creater_random(1, 20);
    new_one->next=NULL;
    
    Node* tp=unused_head;
    int min=10000;
    Node* temp=NULL; //指向最优分配节点
    
    while(tp->next){
        tp=tp->next; //转移到下一个节点
        int remine=tp->big-new_one->big;
        if(remine>=0 && remine<min){
            min=remine;
            temp=tp;
        }
    }
    if(temp){
        new_one->start=temp->start;
        new_one->end=new_one->start+new_one->big-1;
        
        temp->start+=new_one->big;
        temp->big-=new_one->big;
        
        //将newone 插入到已使用链中 used_head
        insert(used_head,new_one);
        
        printf("内存分配成功\n");
        mk_claen();
    }
    else{
        printf("内存不足，分配不成功\n");
    }
}


//随机作业完成函数 version 2   ////////////////////
void work_comp02(){
    Node* tp=used_head;
    int relise_flag=0;
    Node* reli_p=NULL;
    
    if(tp->next==NULL){
        printf("没有作业可以完成并回收\n\n");
        mk_claen();
    }
    else{
        //随机找到一个作业，从使用链中剪出
        while (relise_flag==0) {
            if(creater_random(0, 100)<30){
                if(tp->next==NULL){
                    ;
                }
                else{
                    reli_p=tp->next;
                    tp->next=reli_p->next;
                    relise_flag=1;
                }
            }
            if (tp->next==NULL) {
                tp=used_head;
            }else{
                tp=tp->next;
            }
        }
        //将剪出作业插入未使用链
        insert(unused_head,reli_p);
        //合并整理未使用链
        mk_claen();
        printf("作业内存回收完毕\n");
    }
       mk_claen();
}

//打印内存分配情况 1-100  *-*-*已分配 0-0-0未分配 /////////////////
void show(){
    Node* tp=unused_head;
    if (tp->next->start>1) {
        for(int i=1;i<tp->next->start;i++){
            printf("%d\t: *-*-*\n",i);
        }
    }
    while(tp->next){
        tp=tp->next;
        printf("-------------\n");
        for (int i=tp->start; i<=tp->end; i++) {
            printf("%d\t: 0-0-0\n",i);
        }
        if (tp->next){
            printf("-------------\n");
            for(int i=tp->end+1;i<tp->next->start;i++){
                 printf("%d\t: *-*-*\n",i);
             }
        }
    }//end while
   
    if(tp->end<100){
         printf("-------------\n");
        for (int i=tp->end+1; i<=100; i++) {
            printf("%d\t: *-*-*\n",i);
        }
    }
    
}//end fun show()

//random number creater a-b
int creater_random(int a,int b){
    
    srand((int)time(NULL));     //每次执行种子不同，生成不同的随机数
    
    return a+rand()%(b-a+1);
}

//队列插入元素
void insert(Node* T,Node* one){
    
    Node* temp_used=T;
    int insert_flag=0;
    
    while(temp_used->next){
        if(one->start < (temp_used->next->start) ){
            one->next=temp_used->next;
            temp_used->next=one;
            insert_flag=1;
            break;
        }
        temp_used=temp_used->next;
    }
    if(insert_flag==0){  //上述插入不成功，就放队列最后
        temp_used->next=one;
    }
}

//对未分配链 unuse_head做合并清理的工作
void mk_claen(){
    Node* tp=unused_head;
    while(tp->next){
        
        //清理
        if(tp->next->big==0){
            Node* fre_p=tp->next;
            tp->next=fre_p->next;
            free(fre_p);
        }
        if(tp->next==NULL){
    
        }else{
           tp=tp->next;
        }
        
    }
    tp=unused_head;
    while(tp->next){
        //合并
        if( (tp->end+1)==tp->next->start){
            Node* fre_p=tp->next;
            tp->big+=fre_p->big;
            tp->end=fre_p->end;
            tp->next=fre_p->next;
            free(fre_p);
        }
        if(tp->next==NULL){
            
        }else{
            tp=tp->next;
        }
    }
}

//碎片拼接，整合剩余空间  //////////////////
void connected(){
    //紧凑已使用队列
    Node* tp=used_head->next;
    int content=0;
    
    if(tp==NULL){
        printf("使用队列为空,无需碎片拼接\n");
    }
    else{
        tp->start=1;
        tp->end=tp->big;
        content+=tp->big;
        
        while(tp->next){
            tp->next->start=tp->end+1;
            tp=tp->next;                //tp point to the current Node
            tp->end=tp->start+tp->big-1;
            content+=tp->big;
        }
        
        Node* temp=(Node*)malloc(sizeof(Node));
        temp->start=tp->end+1;
        temp->big=100-content;
        temp->end=temp->start+temp->big-1;
        temp->next=NULL;
        
        //归并未使用队列,free all current Node,and add a new one
        tp=unused_head;
        while(tp->next){
            Node* fre_p=tp->next;
            tp->next=fre_p->next;
            free(fre_p);
        }
        unused_head->next=temp;
        
        printf("碎片拼接成功\n");
    }
   
}

