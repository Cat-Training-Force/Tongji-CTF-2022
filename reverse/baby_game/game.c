#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

char maze[]="-++++++-++++++++-+++++----+++-++---++++-++++---+++-++----+++-+-+---++-++-+++-+---++++-++-----+----+++-++++++++-++-----++++++++-*";

int check(char *s){
    size_t len=strlen(s);
    if(len!=40)return 0;
    int x=0;
    for(size_t i=0;i<len;i++){
        switch(s[i]){
            case 'd':
            if(x/16==7)return 0;
            x+=16;
            break;
            case 'l':
            if(x%16==0)return 0;
            x-=1;
            break;
            case 'r':
            if(x%16==15)return 0;
            x+=1;
            break;
            case 'u':
            if(x/16==0)return 0;
            x-=16;
            default:return 0;
        }
        if(maze[x]=='+')return 0;
        if(maze[x]=='*')return 1;
    }
    return 0;
}
int main(){
    puts("Please Input:");
    char input[1024];
    scanf("%s",input);
    if(check(input)){
        printf("So Good!,Your flag is tjctf{%s}\n",input);
    }else{
        puts("Maybe Another Choice");
    }
}