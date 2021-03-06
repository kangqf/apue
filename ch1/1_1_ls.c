#include "../apue/apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2)
        err_quit("Usage: kls dirname");
    if((dp = opendir(argv[1])) == NULL)
        err_sys("Can't open %s",argv[1]);
    while((dirp = readdir(dp)) != NULL)
        printf("%s\n",dirp->d_name);
    exit(0);
}
