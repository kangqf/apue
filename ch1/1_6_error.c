#include "../apue/apue.h"
#include <errno.h>

int main()
{
    printf("errno: %d \n", errno);
    printf("strerror(EACCES): %s \n", strerror(EACCES));
    errno = ENOENT;
    perror("ENOENT -> perror: ");
    exit(0);
}
