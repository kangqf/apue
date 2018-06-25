#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 4096
#define FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH 

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buf[MAXLINE];

    printf("come into client\n");

    fgets(buf,MAXLINE,stdin);
    len = strlen(buf);
    if(buf[len-1] == '\n')
        len--;
    write(writefd,buf,len);
    while( (n = read(readfd,buf,MAXLINE)) > 0 )
    {
        write(STDOUT_FILENO,buf,n);
    }
}

void serve(int readfd, int writefd)
{
    ssize_t n;
    int fd;
    char buf[MAXLINE];
    
    printf("come into serve\n");
    
    if((n = read(readfd,buf,MAXLINE)) == 0 )
    {
        printf("read content error \n");
    }
    buf[n] = '\0';
    if((fd = open(buf,O_RDONLY)) < 0)
    {
        snprintf(buf+n, sizeof(buf)-n, "Can't open file %s \n", strerror(errno));
        n = strlen(buf);
        write(writefd,buf,n);
    }
    else
    {
        while((n = read(fd,buf,MAXLINE)) > 0)
            write(writefd,buf,n);

        close(fd);
    }
}

int main()
{
    pid_t pid;
    int readfd,writefd;

    if( (mkfifo(FIFO1,FILE_MODE) < 0) && (errno != EEXIST) )
    {
        printf("error mkfifo \n");
        exit(0);
    }
    
    if( (mkfifo(FIFO2,FILE_MODE) < 0) && (errno != EEXIST) )
    {
        printf("error mkfifo \n");
        unlink(FIFO1);
        exit(0);
    }
    

    // child as serve
    if((pid = fork()) == 0)
    {
        readfd = open(FIFO1,O_RDONLY,0);
        writefd = open(FIFO2,O_WRONLY,0);
        serve(readfd,writefd);

        exit(0);
    }

    // 注意这里打开的顺序，以防止死锁的发生，如果父子进程都是以读先打开，就会造成两者皆被阻塞在open中，以等待一个写的打开，而造成死锁
    writefd = open(FIFO1,O_WRONLY,0);
    readfd = open(FIFO2,O_RDONLY,0);

    client(readfd,writefd);

    waitpid(pid,NULL,0);


    close(readfd);
    close(writefd);

    unlink(FIFO1);
    unlink(FIFO2);

    exit(0);
}
