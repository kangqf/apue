#include <mqueue.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    unsigned int prio;
    int n; 
    mqd_t mqd;
    struct mq_attr attr;
    void *buff;
    char *pathname = "temp.8888";


    mqd = mq_open(pathname, O_RDONLY);
    
    mq_getattr(mqd, &attr);
    buff = malloc(attr.mq_msgsize);
    
    n = mq_receive(mqd,buff,attr.mq_msgsize,&prio);


   printf("read %ld bytes, priority = %u \n", (long)n, prio); 
}
