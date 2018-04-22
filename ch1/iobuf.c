#include "../apue/apue.h"

int main()
{
    int c;

    while((c = getc(stdin) != EOF))
    {
        if(putc(c,stdout) == EOF)
            err_sys("write error");
    }
    if(ferror(stdin))
        err_sys("input error");

    exit(0);
}
