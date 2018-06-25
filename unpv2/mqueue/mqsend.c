#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    int len;
    int prio;
    char *ptr;
    char *pathname = "temp.8888";
    mqd_t mqd;

    if(argc != 3)
        exit(0);

    len = atoi(argv[1]);
    prio = atoi(argv[2]);

    ptr = calloc(len,sizeof(char));

    mqd = mq_open(pathname,O_WRONLY);

    mq_send(mqd,ptr,len,prio);

    exit(0);
}
