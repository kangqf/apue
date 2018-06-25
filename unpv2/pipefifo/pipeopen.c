#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define MAXLINE 4096

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buf[MAXLINE];

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
    int pfd1[2];// serve write client read
    int pfd2[2];// serve read client write
    pid_t pid;

    pipe(pfd1);
    pipe(pfd2);

    // child as serve
    if((pid = fork()) == 0)
    {
        close(pfd1[0]);
        close(pfd2[1]);

        serve(pfd2[0],pfd1[1]);

        exit(0);
    }

    // parent as client
    close(pfd1[1]);
    close(pfd2[0]);


    client(pfd1[0],pfd2[1]);

    waitpid(pid,NULL,0);
    exit(0);
}
