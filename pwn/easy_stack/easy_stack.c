#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int null_func_0(){
    system("/bin/sh");
}
int main(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
    char name[40];
    read(0,name,0x40);
    printf("hello, %s!\n",name);
}