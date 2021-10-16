#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct queue
{
    int pid;
    int req_time;//进程所需运行时间
    int run_time;//进程运行时间
    char state;//进程状态
    struct queue *next;
}Qu,* Q;
int main()
{
    Q q,p,head,m,k,e;
    int t,d,n,x;
    char f;
    printf("请输入进程数：");
    scanf("%d",&n);
    while(n<=0)
    {
        printf("进程数为整数，请继续输入：");
        scanf("%d",&n);
    }
    d=n;
    //输入头节点信息
    printf("请输入进程标识符：");
    scanf("%d",&x);
    printf("请输入进程所需运行时间：");
    scanf("%d",&t);
    p=(Q)malloc(sizeof(Qu));
    head=p;
    p->pid=x;
    p->req_time=t;
    p->run_time=0;
    p->state='R';
    p->next=NULL;
    getchar();
    d--;
    while(d>0)
    {        
        //输入节点信息
        printf("请输入进程标识符：");
        scanf("%d",&x);
        printf("请输入进程所需运行时间：");
        scanf("%d",&t);
        q=(Q)malloc(sizeof(Qu));
        q->pid=x;
        q->req_time=t;
        q->run_time=0;
        q->state='R';
        p->next=q;
        p=q;
        getchar();
        d--;
        p->next=head;
        q=head;
    }
    k=head;
    e=head;
    printf("********************创建的进程**********************\n");
    printf("进程标识符  进程所需运行时间 进程已运行时间 进程状态\n");
    do{
        printf("%d\t\t%d  \t\t%d  \t\t%c\n",q->pid,q->req_time,q->run_time,q->state);
        q=q->next;
    }while(q!=head);
    printf("***************************************************\n");
    do{
        if(e->run_time<e->req_time)
        {
                e->run_time++;
                if(e->run_time==e->req_time)
                {
                        e->state='E';
                        q=e;
                        printf("***************************************************\n");
                        printf("进程%d运行完成！\n",e->pid);
                        printf("进程标识符  进程所需运行时间 进程已运行时间 进程状态\n");
                        do{
                                printf("%d\t\t%d  \t\t%d  \t\t%c\n",q->pid,q->req_time,q->run_time,q->state);
                                q=q->next;
                        }while(q!=e);
                        printf("***************************************************\n");
                        e=e->next;
                        q=e;
                        p->next=k;
                }
                else
                {
                        printf("***************************************************\n");
                        printf("进程%d正在运行！\n",q->pid);
                        printf("进程标识符  进程所需运行时间 进程已运行时间 进程状态\n");
                        do{
                                printf("%d\t\t%d  \t\t%d  \t\t%c\n",q->pid,q->req_time,q->run_time,q->state);
                                q=q->next;
                        }while(q!=e);
                        printf("***************************************************\n");
                        e=e->next;
                        q=e;
                        p=p->next;
                }
                if(q->state=='E')
                {
                        printf("所有进程已经运行完！\n");
                }
                else
                {
                        printf("是否加入新的进程？(y/n):");
                        scanf("%c",&f);
                        getchar();
                        if(f=='y' || f=='Y')
                        {
                                printf("请输入进程数：");
                                scanf("%d",&n);
                                while(n<=0)
                                {
                                        printf("进程数为整数，请继续输入：");
                                        scanf("%d",&n);
                                }
                                d=n;
                                //输入头节点信息
                                printf("请输入进程标识符：");
                                scanf("%d",&x);
                                printf("请输入进程所需运行时间：");
                                scanf("%d",&t);
                                m=(Q)malloc(sizeof(Qu));
                                m->pid=x;
                                m->req_time=t;
                                m->run_time=0;
                                m->state='R';
                                m->next=NULL;
                                if(q->next->state=='E')
                                {
                                        p=m;
                                        e=m;
                                        p->next=e;
                                        q=e;
                                }
                                else
                                {
                                        p->next=m;
                                        m->next=e;
                                        p=m;
                                }
                        }
                } /**/   
        }
    }while(q->state!='E');
    return 0;
}