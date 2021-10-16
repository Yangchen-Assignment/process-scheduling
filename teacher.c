#include <stdio.h>
#include <stdlib.h>

typedef struct pcb
{
    int pid;
    char state;
    int total_time;
    int cputime;
    struct pcb* next;
}* proc;

int proc_num;
proc head, tail;

int init_pcb()
{
    int i;
    proc p,tmp;
    printf("please input the numer of process:\n");
    scanf("%d", &proc_num);
    printf("there are %d process, please input pcb info:\n", proc_num);
    
    p=(proc)malloc(sizeof(struct pcb));
    printf("process id:");
    scanf("%d",&p->pid);
    printf("cputime require:");
    scanf("%d", &p->total_time);
    p->state='R';
    p->cputime=0;
    head=p;
    for(i=proc_num;i>1;i--)
    {
        tmp=p;
        p=(proc)malloc(sizeof(struct pcb));
        printf("process id:");
        scanf("%d",&p->pid);
        printf("cputime required:");
        scanf("%d", &p->total_time);
        p->state='R';
        p->cputime=0;
        tmp->next=p;
    }
    tail=p;
    p->next=head;
    return 0;
}

void display()
{
    int i;
    proc p=head;
    printf("pid\tcpu_time\treq_time\n");
    for(i=0;i<proc_num;i++)
    {
        printf("%d\t%d\t%d\n",p->pid,p->cputime,p->total_time);
        p=p->next;
    }
}

void schd()
{
    int round=1, i;
    proc tmp=tail;
    proc p=head;

    while(p->total_time>p->cputime)
    {
        printf("\nRound %d, Process %d is running\n", round, p->pid);
        p->cputime++;
        display();
        if(p->total_time==p->cputime)
        {
            p->state='E';
            proc_num--;
            tmp->next=p->next;
            if(p==head)
            {
                head=p->next;
            }
            printf("process %d is finished\np",p->pid);
        }
        else
        {
            tmp=p;
        }
        p=p->next;
        round++;
    }
}

int main()
{
    init_pcb();
    display();
    schd();
    return 0;
}