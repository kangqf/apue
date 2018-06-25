#include <mqueue.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_MODE S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH

int main()
{
    int flag;
    mqd_t mqd;
    struct mq_attr attr;

    flag = O_RDWR | O_CREAT;
    flag |= O_EXCL;

    char *pathname = "temp.8888";

    mqd = mq_open(pathname,flag,FILE_MODE,NULL);

    
    mq_getattr(mqd,&attr);
    printf("max msgs = %ld , max bytes = %ld , current on index = %ld \n", attr.mq_maxmsg,attr.mq_msgsize, attr.mq_curmsgs);


    mq_close(mqd);
}
