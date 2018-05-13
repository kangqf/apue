#include "../apue/apue.h"

int main()
{
    printf("uid: %d \n", getuid());
    printf("gid: %d \n", getgid());
    
    exit(0);
}
