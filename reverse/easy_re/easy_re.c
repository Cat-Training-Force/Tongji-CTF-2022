#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <inttypes.h>

uint8_t key[]={15, 91, 153, 255, 186, 185, 174, 24, 241, 125, 34, 156, 33, 100, 171, 16, 131, 230, 93, 170, 87, 194, 51, 156, 39, 5, 79, 253, 117};
char res[]={105, 55, 248, 152, 193, 157, 218, 89, 131, 9, 125, 206, 18, 18, 152, 98, 240, 215, 51, 237, 8, 160, 74, 195, 127, 74, 29, 220, 8};
void encrypt(char *s,size_t len){
    for(size_t i=0;i<len;i++){
        s[i]^=key[i];
    }
}
int main(){
    puts("Please Input the Flag:");
    char flag[1024];
    scanf("%s",flag);
    size_t len=strlen(flag);
    encrypt(flag,strlen(flag));
    if(memcmp(flag,res,len)){
        puts("Wrong");
    }else{
        puts("Right!!!");
    }
}