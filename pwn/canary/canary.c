#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void init() {
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
}
void fun() {
    char a[8];
    puts("");
    read(0, a, 32);
}
void hidden() {
    system("/bin/sh");
}
int main() {
    int a=0x33323130;
    printf("Don't tell others ^_^ %u %hu\n", *(uint32_t*)(((uint8_t*)&a) + 16), *(uint16_t*)(((uint8_t*)&a) + 20));
    init();
    size_t cnt = 0;
    while (1) {
        int pid = fork();
        if (pid < 0) {
            break;
        }
        if (pid) {
            cnt++;
            wait(0);
            if (cnt >= 1000) {
                printf("Failed\n");
                exit(0);
            }
        } else {
            puts("hello~");
            fflush(stdout);
            fun();
            puts("Maybe Success");
            fflush(stdout);
            exit(0);
        }
        cnt++;
        if(cnt>1000){
            exit(0);
        }
    }
}