#include <stdlib.h>
#include <stdio.h>
typedef struct pcb
{
    int pid;
    int prio_num;
    int req_time;
    int total_time;
    char state;
    struct pcb* next;
}pcb, *Process;

typedef struct queue
{
    Process head;
    //Process tail;
} Qu;

void init(Qu* Q, int num)
{
    Q->head=(Process)malloc(sizeof(pcb));
    Q->head->next=NULL;
    Q->head->pid=num;
    //Q->tail=Q->head;
}
void insrtproc(Qu *Q, Process q)
{
    Process p=Q->head;
    while(p->next&&q->prio_num<p->next->prio_num)
    {
        p=p->next;
    }
    q->next=p->next;
    p->next=q;
}
void addproc(Qu *Q, int pid, int time, int prio)
{
    Process tmp=(Process)malloc(sizeof(pcb));
    tmp->pid=pid;
    tmp->req_time=time;
    tmp->prio_num=prio;
    tmp->total_time=0;
    tmp->state='W';
    insrtproc(Q, tmp);
}
void killproc(Qu *Q, int pid)
{
    Process p=Q->head;
    while(p->next->pid!=pid)
    {
        p=p->next;
    }
    Process tmp=p->next;
    p->next=p->next->next;
    free(tmp);
    Q->head->pid--;
}
void display(Qu *Q)
{
    Process p=Q->head->next;
    int num=Q->head->pid;
    //printf("********************创建的进程**********************\n");
    printf("**************************************************************\n");
    printf("进程标识符  进程优先级  进程所需运行时间 进程已运行时间 进程状态\n");
    for(int i=0;i<num;i++)
    {
        printf("%d\t\t%d  \t\t%d  \t\t%d\t   %c\n",p->pid,p->prio_num,p->req_time,p->total_time,p->state);
        p=p->next;
    }
    printf("**************************************************************\n");
}

int main()
{
    Qu Q;
    int num;
    printf("输入进程数量:");
    scanf("%d", &num);
    init(&Q, num);
    for(int i=0; i<num; i++)
    {
        int pid, time, prio; 
        printf("输入第%d进程的进程PID、所需运行时间 优先级（以空格分隔）\n",i+1);
        scanf("%d%d%d",&pid,&time,&prio);
        addproc(&Q, pid, time, prio);
    }
    int cnt=Q.head->pid;
    while(cnt)
    {
        Process p=Q.head->next;
        //Q.head->next=p->next;
        if(p->req_time>p->total_time)
        {
            p->state='R';
            p->total_time++;
            
            
            if(p->req_time==p->total_time)
            {
                p->state='E';
                display(&Q);
                printf("进程%d终止\n",p->pid);
                killproc(&Q, p->pid);
            }
            else//else if(进程还没有终止)
            {
                display(&Q);
                p->prio_num--;
                if(p->next&&p->prio_num<=p->next->prio_num)
                {
                    Q.head->next=p->next;
                    p->state='W';
                    insrtproc(&Q, p);
                }
            } 
        }
        cnt=Q.head->pid;
    }
}
/*
3
123 3 23
565 2 21
735 6 25
*/