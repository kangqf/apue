#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 4096

int main()
{
    FILE *fp;
    char buf[MAXLINE], command[MAXLINE];
    size_t n;

    fgets(buf,MAXLINE,stdin);
    n = strlen(buf);
    if(buf[n-1] == '\n')
        n--;
    
    snprintf(command,sizeof(command),"%s",buf);

    fp = popen(command,"r");

    while(fgets(buf,MAXLINE,fp) != NULL)
        fputs(buf,stdout);

    pclose(fp);

    exit(0);


}
