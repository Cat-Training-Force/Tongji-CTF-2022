#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>
#include <inttypes.h>
void init(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}
int main(){
    init();
    int fd=open("/dev/random",O_RDONLY);
    uint64_t r,r1;
    char name[64];
    memset(name,0,64);
    read(fd,&r,8);
    read(0,name,64-1);
    printf("hello, ");
    printf(name);
    scanf("%lu",&r1);
    if(r==r1){
        printf(", u r right, here is your shell\n");
        system("/bin/sh");
    }else{
        printf("no no no");
        exit(0);
    }
}