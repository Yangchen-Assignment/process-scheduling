#include<stdlib.h>
#include<stdio.h>

typedef struct pcb
{
    int pid;
    int req_time;
    int total_time;
    char state;
    struct pcb* next;
}pcb, *Process;

typedef struct queue
{
    Process head;
    Process tail;
} Qu;

void init(Qu* Q, int num)
{
    Q->head=(Process)malloc(sizeof(pcb));
    Q->head->next=NULL;
    Q->head->pid=num;
    Q->tail=Q->head;
}
void addproc(Qu *Q, int pid, int time)
{
    Process tmp=(Process)malloc(sizeof(pcb));
    tmp->pid=pid;
    tmp->req_time=time;
    tmp->total_time=0;
    tmp->state='W';
    Q->tail->next=tmp;
    Q->tail=tmp;
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
    printf("***************************************************\n");
    printf("进程标识符  进程所需运行时间 进程已运行时间 进程状态\n");
    for(int i=0;i<num;i++)
    {
        printf("%d\t\t%d  \t\t%d  \t\t%c\n",p->pid,p->req_time,p->total_time,p->state);
        p=p->next;
    }
    printf("***************************************************\n");
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
        int pid, time; 
        printf("输入第%d进程的进程PID、所需运行时间（以空格分隔）\n",i+1);
        scanf("%d%d",&pid,&time);
        addproc(&Q, pid, time);
    }
    int cnt=Q.head->pid;
    while(cnt)
    {
        Process p=Q.head->next;
        for(int i=0; i<cnt; i++)
        {
            if(p->req_time>p->total_time)
            {
                //prinf("当前%d进程正在运行",p->pid);
                p->total_time++;
                p->state='R';
                //printf("当前所有进程状态")+display
                display(&Q);
                p->state='W';
                if(p->req_time==p->total_time)
                {
                    printf("进程%d终止\n",p->pid);
                    killproc(&Q, p->pid);
                }
            }
            p=p->next;
        }
        cnt=Q.head->pid;
    }
    printf("所有进程结束");
}
/*
2
123 5
565 2
*/
/*
3
123 5 20
565 2 21
735 8 26
*/