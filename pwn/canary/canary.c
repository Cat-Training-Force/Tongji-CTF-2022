#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdio.h>
#include <wait.h>

void init(){
    setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
}
void fun(){
    char a[8];
    puts("");
    read(0,a,32);
}
void hidden(){
    system("/bin/sh");
}
int main(){
    init();
    while(1){
        int pid=fork();
        if(pid<0){
            break;
        }
        if(pid){
            wait(0);
        }else{
            puts("hello~");
            fflush(stdout);
            fun();
            puts("Maybe Success");
            fflush(stdout);
        }
    }
}