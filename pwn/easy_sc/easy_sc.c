#include <stdio.h>
#include <unistd.h>
void init(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}
int main(){
    init();
    int a;
    printf("Maybe some information u need: %p\n",&a);
    char s[0x100];
    read(0,s,0x200);
}