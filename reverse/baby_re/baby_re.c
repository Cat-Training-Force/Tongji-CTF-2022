
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/ptrace.h>

uint8_t code[]={51, 214, 81, 13, 164, 12, 177, 164, 180, 29, 71, 5, 214, 65, 1, 246, 7, 156, 171, 78, 136, 115, 166, 134, 185, 116, 110, 165, 247, 187, 179, 115, 28, 244, 38, 132, 220, 131, 125, 153, 158, 241, 73, 185, 89, 141, 160, 27, 171, 188, 54, 191, 122, 1, 248, 194, 28, 147, 114, 72, 94, 188, 113, 126, 67, 180, 143, 255, 185, 131, 125, 185, 252, 148, 58, 205, 119, 13, 116, 54, 192, 145, 196, 162, 57, 12, 179, 4, 4, 220, 59, 29, 21, 200, 253, 115, 52, 145, 196, 178, 9, 12, 181, 17, 248, 220, 177, 136, 86, 128, 117, 230, 75, 217, 198, 178, 1, 131, 125, 173, 252, 148, 58, 205, 89, 141, 156, 54, 192, 217, 79, 28, 147, 207, 125, 165, 253, 209, 214, 70, 219, 56, 181, 214, 196, 80, 141, 124, 180, 164, 181, 77, 254, 31, 111, 61, 21, 141, 152, 55, 16, 232, 142, 126, 59, 207, 125, 177, 61, 124, 63, 68, 95, 67, 49, 234, 193, 17, 126, 39, 240, 1, 204, 202, 185, 96, 251, 45, 154, 65, 182, 189, 133, 1, 194, 251, 243, 207, 109, 181, 119, 209, 214, 204, 78, 249, 181, 191, 10, 82, 10, 3, 48, 172, 61, 200, 61, 31, 127, 25, 159, 0, 69, 230, 193, 156, 191, 116, 180, 172, 57, 194, 129, 124, 37, 187, 6, 128, 255, 99, 8, 145, 196, 178, 9, 12, 57, 131, 119, 209, 206, 68, 156, 128, 255, 115, 56, 145, 194, 167, 245, 12, 179, 4, 52, 220, 59, 15, 21, 141, 132, 191, 194, 145, 204, 178, 9, 76, 112, 202, 185, 108, 114, 246, 219, 8, 123, 180, 237, 38, 176, 8, 97, 212, 101, 130};
uint32_t key[4];
// fake_flag{May_be_another_try_lol}
uint8_t enc[256]={0xe0,0x79,0x40,0x7d,0xd2,0x11,0x82,0x63,0x0b,0x76,0xaf,0xa3,0x70,0x22,0x12,0x87,0x9d,0xb1,0xcf,0x9d,0x4e,0xfc,0x12,0x62,0xb4,0x79,0x0c,0xd4,0x68,0xc0,0xf8,0xae,0xb7};
void null_f0();
void hash(uint32_t state[4],uint8_t *data,size_t len){
    memset(state,0,16);
    if(len<16){
        memcpy(state,data,len);
        return;
    }
    char e=0;
    state[0]=*(uint64_t*)&data[4];
    state[1]=*(uint64_t*)&data[8];
    state[2]=*(uint64_t*)&data[12];
    state[3]=*(uint64_t*)&data[0];
    if(len%16!=0)len-=16;
    for(size_t i=16;i<len;i+=16){
        if(e){
            state[0]^=*(uint32_t*)&data[i];
            state[1]^=*(uint32_t*)&data[i+4];
            state[2]^=*(uint32_t*)&data[i+8];
            state[3]^=*(uint32_t*)&data[i+12];
        }else{
            state[0]+=*(uint32_t*)&data[i];
            state[1]+=*(uint32_t*)&data[i+4];
            state[2]+=*(uint32_t*)&data[i+8];
            state[3]+=*(uint32_t*)&data[i+12];
        }
        uint32_t tmp=state[0];
        state[0]=state[1];
        state[1]=state[2];
        state[2]=state[3];
        state[3]=tmp;
        e=!e;
    }
}
void set_key(){
    uint8_t *cs=(uint8_t*)hash,*ce=(uint8_t*)null_f0;
    hash(key,cs,ce-cs);
}
uint8_t* decrypt_code(){
    size_t len=sizeof(key),clen=sizeof(code);
    uint8_t *c=(uint8_t*)mmap(NULL,clen*2,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if(c==NULL){
        fprintf(stderr,"MMAP failed: %d\n",errno);
        exit(1);
    }
    uint8_t *k=(uint8_t*)key;
    for(size_t i=0;i<clen;i++){
        c[i]=code[i]^k[i%16];
    }
    return c;
}
int check(char *s,size_t len){
    return !memcmp(s,enc,len);
}
int main(){
    set_key();
    puts("Input: ");
    char s[256];
    memset(s,0,256);
    read(0,s,255);
    size_t len=strlen(s);
    s[len--]='\0';
    char s1[256];
    strcpy(s1,s);
    void (*encrypt)(char *,size_t)=(void(*)(char*,size_t))decrypt_code();
    encrypt(s,len);
    if(check(s,len)){
        fprintf(stdout,"Your flag is: %s\n",s1);
    }else{
        fprintf(stdout,"Try Again!!!\n");
    }
    fflush(stdout);
}
__attribute__((constructor)) void a(){
    __asm__ __volatile__(
        "jz NEXT1\n"
        "jnz NEXT1\n"
        ".byte 0xff\n"
        "NEXT1:"
    );
    // tjctf{34Bf9acCdD8e412871Ae3ceCE-8A0Ca33}
    if(-1==ptrace(PTRACE_TRACEME)){
        exit(-1);
    }
    uint8_t tmp[]={0x33,0x65,0xa4,0xfc,0x94,0xc7,0x1c,0x80,0xdc,0x4b,0xcf,0x59,0xc2,0x56,0x23,0xf3,0xab,0xef,0x88,0x67,0xd8,0x68,0xc0,0xdd,0x61,0xd3,0xc9,0x8a,0x62,0x7d,0xdd,0x8f,0x61,0x8a,0x34,0x51,0x87,0xf1,0x89,0x5d};
    memmove(enc, tmp, sizeof(tmp));
}
void null_f0(){

}