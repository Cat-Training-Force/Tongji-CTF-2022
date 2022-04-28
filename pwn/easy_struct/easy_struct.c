#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
void init(){
    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);
}
typedef struct User{
    char name[16];
    void *intro;
    int64_t info;
} User;
int main(){
init();
    User *u=malloc(sizeof(User));
    printf("Please input %s name\n","your");
    read(0,u,sizeof(User));
    void (*f)(char*,int64_t)=u->intro;
    f(u->name,u->info);
    printf("Please input %s user\n","another");
    read(0,u,sizeof(User));
    f=u->intro;
    f(u->name,u->info);
}
