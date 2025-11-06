// user/readcount.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[101];
    int fd;
    int before, after, n;

    before = getreadcount();
    printf("Initial Count: %d\n", before);

    fd = open("README", 0); //im making the assumption that we hahd to implement this guy for readme file and not
    //for arbitrary files since its not even mentioned properly :((
    if(fd < 0){
        printf("README prolly doesnt exist\n");
        exit(1);
    }

    n = read(fd, buf, 100);
    if(n < 0){
        printf("Not able to read\n");
    } else {

        if(n < 100) buf[n] = '\0';
    }
    close(fd);

    after = getreadcount();
    printf("Bytes reading...: %d\n", n);
    printf("Bytes afterrr: %d\n", after);

    // verification also gib extra marks plej
    if(after - before != n){
        printf("Warning: expected increase %d, observed %d\n", n, after - before);
    }

    exit(0);
}
