
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
uint8_t code[]={0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x30, 0x48, 0x89, 0x7d, 0xe8, 0x48, 0x89, 0x75, 0xe0, 0x48, 0x89, 0x55, 0xd8, 0x48, 0x8b, 0x45, 0xe8, 0xba, 0x10, 0x0, 0x0, 0x0, 0xbe, 0x0, 0x0, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xe8, 0x59, 0xfe, 0xff, 0xff, 0x48, 0x83, 0x7d, 0xd8, 0xf, 0x77, 0x1c, 0x48, 0x8b, 0x55, 0xd8, 0x48, 0x8b, 0x4d, 0xe0, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x89, 0xce, 0x48, 0x89, 0xc7, 0xe8, 0x7b, 0xfe, 0xff, 0xff, 0xe9, 0x1, 0x2, 0x0, 0x0, 0xc6, 0x45, 0xf3, 0x0, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x83, 0xc0, 0x4, 0x48, 0x8b, 0x0, 0x89, 0xc2, 0x48, 0x8b, 0x45, 0xe8, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x83, 0xc0, 0x8, 0x48, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x4, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x83, 0xc0, 0xc, 0x48, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x8, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0xc, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xd8, 0x83, 0xe0, 0xf, 0x48, 0x85, 0xc0, 0x74, 0x5, 0x48, 0x83, 0x6d, 0xd8, 0x10, 0x48, 0xc7, 0x45, 0xf8, 0x10, 0x0, 0x0, 0x0, 0xe9, 0x83, 0x1, 0x0, 0x0, 0x80, 0x7d, 0xf3, 0x0, 0xf, 0x84, 0x95, 0x0, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x10, 0x48, 0x8b, 0x4d, 0xe0, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x1, 0xc8, 0x8b, 0x0, 0x31, 0xc2, 0x48, 0x8b, 0x45, 0xe8, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x4, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0x4, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x4, 0x31, 0xca, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x8, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0x8, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x8, 0x31, 0xca, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0xc, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0xc, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0xc, 0x31, 0xca, 0x89, 0x10, 0xe9, 0x90, 0x0, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x10, 0x48, 0x8b, 0x4d, 0xe0, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x1, 0xc8, 0x8b, 0x0, 0x1, 0xc2, 0x48, 0x8b, 0x45, 0xe8, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x4, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0x4, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x4, 0x1, 0xca, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x8, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0x8, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0x8, 0x1, 0xca, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0xc, 0x8b, 0x8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x50, 0xc, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x1, 0xd0, 0x8b, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x83, 0xc0, 0xc, 0x1, 0xca, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x0, 0x89, 0x45, 0xf4, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x50, 0x4, 0x48, 0x8b, 0x45, 0xe8, 0x89, 0x10, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x8d, 0x50, 0x4, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x40, 0x8, 0x89, 0x2, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x8d, 0x50, 0x8, 0x48, 0x8b, 0x45, 0xe8, 0x8b, 0x40, 0xc, 0x89, 0x2, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x8d, 0x50, 0xc, 0x8b, 0x45, 0xf4, 0x89, 0x2, 0x80, 0x7d, 0xf3, 0x0, 0xf, 0x94, 0xc0, 0x88, 0x45, 0xf3, 0x48, 0x83, 0x45, 0xf8, 0x10, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x3b, 0x45, 0xd8, 0xf, 0x82, 0x6f, 0xfe, 0xff, 0xff, 0xc9, 0xc3, 0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x10, 0x48, 0x8d, 0x5, 0x99, 0xfd, 0xff, 0xff, 0x48, 0x89, 0x45, 0xf0, 0x48, 0x8d, 0x5, 0x72, 0x3, 0x0, 0x0, 0x48, 0x89, 0x45, 0xf8, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x2b, 0x45, 0xf0, 0x48, 0x89, 0xc2, 0x48, 0x8b, 0x45, 0xf0, 0x48, 0x89, 0xc6, 0x48, 0x8d, 0x3d, 0xf8, 0x2c, 0x0, 0x0, 0xe8, 0x6c, 0xfd, 0xff, 0xff, 0x90, 0xc9, 0xc3, 0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x30, 0x48, 0xc7, 0x45, 0xe0, 0x10, 0x0, 0x0, 0x0, 0x48, 0xc7, 0x45, 0xe8, 0x28, 0x1, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xe8, 0x48, 0x1, 0xc0, 0x41, 0xb9, 0x0, 0x0, 0x0, 0x0, 0x41, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xb9, 0x22, 0x0, 0x0, 0x0, 0xba, 0x7, 0x0, 0x0, 0x0, 0x48, 0x89, 0xc6, 0xbf, 0x0, 0x0, 0x0, 0x0, 0xe8, 0x9a, 0xfb, 0xff, 0xff, 0x48, 0x89, 0x45, 0xf0, 0x48, 0x83, 0x7d, 0xf0, 0x0, 0x75, 0x2c, 0xe8, 0x3a, 0xfb, 0xff, 0xff, 0x8b, 0x10, 0x48, 0x8b, 0x5, 0x81, 0x2c, 0x0, 0x0, 0x48, 0x8d, 0x35, 0xfe, 0x9, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xb8, 0x0, 0x0, 0x0, 0x0, 0xe8, 0xad, 0xfb, 0xff, 0xff, 0xbf, 0x1, 0x0, 0x0, 0x0, 0xe8, 0xe3, 0xfb, 0xff, 0xff, 0x48, 0x8d, 0x5, 0x6c, 0x2c, 0x0, 0x0, 0x48, 0x89, 0x45, 0xf8, 0x48, 0xc7, 0x45, 0xd8, 0x0, 0x0, 0x0, 0x0, 0xeb, 0x3b, 0x48, 0x8d, 0x15, 0xe7, 0x29, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xd8, 0x48, 0x1, 0xd0, 0xf, 0xb6, 0x30, 0x48, 0x8b, 0x45, 0xd8, 0x83, 0xe0, 0xf, 0x48, 0x89, 0xc2, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x1, 0xd0, 0xf, 0xb6, 0x8, 0x48, 0x8b, 0x55, 0xf0, 0x48, 0x8b, 0x45, 0xd8, 0x48, 0x1, 0xd0, 0x31, 0xce, 0x89, 0xf2, 0x88, 0x10, 0x48, 0x83, 0x45, 0xd8, 0x1, 0x48, 0x8b, 0x45, 0xd8, 0x48, 0x3b, 0x45, 0xe8, 0x72, 0xbb, 0x48, 0x8b, 0x45, 0xf0, 0xc9, 0xc3, 0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x10, 0x48, 0x89, 0x7d, 0xf8, 0x48, 0x89, 0x75, 0xf0, 0x48, 0x8b, 0x55, 0xf0, 0x48, 0x8b, 0x45, 0xf8, 0x48, 0x8d, 0x35, 0xc0, 0x2a, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xe8, 0x8, 0xfb, 0xff, 0xff, 0x85, 0xc0, 0xf, 0x94, 0xc0, 0xf, 0xb6, 0xc0, 0xc9, 0xc3, 0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x81, 0xec, 0x20, 0x2, 0x0, 0x0, 0x64, 0x48, 0x8b, 0x4, 0x25, 0x28, 0x0, 0x0, 0x0, 0x48, 0x89, 0x45, 0xf8, 0x31, 0xc0, 0xb8, 0x0, 0x0, 0x0, 0x0, 0xe8, 0x83, 0xfe, 0xff, 0xff, 0x48, 0x8d, 0x3d, 0x34, 0x9, 0x0, 0x0, 0xe8, 0x6a, 0xfa, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfd, 0xff, 0xff, 0xba, 0x0, 0x1, 0x0, 0x0, 0xbe, 0x0, 0x0, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xe8, 0x91, 0xfa, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfd, 0xff, 0xff, 0xba, 0xff, 0x0, 0x0, 0x0, 0x48, 0x89, 0xc6, 0xbf, 0x0, 0x0, 0x0, 0x0, 0xe8, 0x88, 0xfa, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfd, 0xff, 0xff, 0x48, 0x89, 0xc7, 0xe8, 0x39, 0xfa, 0xff, 0xff, 0x48, 0x89, 0x85, 0xe0, 0xfd, 0xff, 0xff, 0x48, 0x8b, 0x85, 0xe0, 0xfd, 0xff, 0xff, 0x48, 0x8d, 0x50, 0xff, 0x48, 0x89, 0x95, 0xe0, 0xfd, 0xff, 0xff, 0xc6, 0x84, 0x5, 0xf0, 0xfd, 0xff, 0xff, 0x0, 0x48, 0x8d, 0x95, 0xf0, 0xfd, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfe, 0xff, 0xff, 0x48, 0x89, 0xd6, 0x48, 0x89, 0xc7, 0xe8, 0xdf, 0xf9, 0xff, 0xff, 0xb8, 0x0, 0x0, 0x0, 0x0, 0xe8, 0x35, 0xfe, 0xff, 0xff, 0x48, 0x89, 0x85, 0xe8, 0xfd, 0xff, 0xff, 0x48, 0x8b, 0x95, 0xe0, 0xfd, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfd, 0xff, 0xff, 0x48, 0x8b, 0x8d, 0xe8, 0xfd, 0xff, 0xff, 0x48, 0x89, 0xd6, 0x48, 0x89, 0xc7, 0xff, 0xd1, 0x48, 0x8b, 0x95, 0xe0, 0xfd, 0xff, 0xff, 0x48, 0x8d, 0x85, 0xf0, 0xfd, 0xff, 0xff, 0x48, 0x89, 0xd6, 0x48, 0x89, 0xc7, 0xe8, 0xd5, 0xfe, 0xff, 0xff, 0x85, 0xc0, 0x74, 0x24, 0x48, 0x8b, 0x5, 0xad, 0x2a, 0x0, 0x0, 0x48, 0x8d, 0x95, 0xf0, 0xfe, 0xff, 0xff, 0x48, 0x8d, 0x35, 0x5c, 0x8, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xb8, 0x0, 0x0, 0x0, 0x0, 0xe8, 0xf2, 0xf9, 0xff, 0xff, 0xeb, 0x20, 0x48, 0x8b, 0x5, 0x89, 0x2a, 0x0, 0x0, 0x48, 0x89, 0xc1, 0xba, 0xd, 0x0, 0x0, 0x0, 0xbe, 0x1, 0x0, 0x0, 0x0, 0x48, 0x8d, 0x3d, 0x44, 0x8, 0x0, 0x0, 0xe8, 0x20, 0xfa, 0xff, 0xff, 0x48, 0x8b, 0x5, 0x69, 0x2a, 0x0, 0x0, 0x48, 0x89, 0xc7, 0xe8, 0xe1, 0xf9, 0xff, 0xff, 0xb8, 0x0, 0x0, 0x0, 0x0, 0x48, 0x8b, 0x4d, 0xf8, 0x64, 0x48, 0x33, 0xc, 0x25, 0x28, 0x0, 0x0, 0x0, 0x74, 0x5, 0xe8, 0x58, 0xf9, 0xff, 0xff, 0xc9, 0xc3, 0xf3, 0xf, 0x1e, 0xfa, 0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x30, 0x64, 0x48, 0x8b, 0x4, 0x25, 0x28, 0x0, 0x0, 0x0, 0x48, 0x89, 0x45, 0xf8, 0x31, 0xc0, 0x74, 0x3, 0x75, 0x1, 0xff, 0xbf, 0x0, 0x0, 0x0, 0x0, 0xb8, 0x0, 0x0, 0x0, 0x0, 0xe8, 0xa7, 0xf9, 0xff, 0xff, 0x48, 0x83, 0xf8, 0xff, 0x75, 0xa, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xe8, 0xa7, 0xf9, 0xff, 0xff, 0x48, 0xb8, 0x33, 0x65, 0xa4, 0xfc, 0x94, 0xc7, 0x1c, 0x80, 0x48, 0xba, 0xdc, 0x4b, 0xcf, 0x59, 0xc2, 0x56, 0x23, 0xf3, 0x48, 0x89, 0x45, 0xd0, 0x48, 0x89, 0x55, 0xd8, 0x48, 0xb8, 0xab, 0xef, 0x88, 0x67, 0xd8, 0x68, 0xc0, 0xdd, 0x48, 0xba, 0x61, 0xd3, 0xc9, 0x8a, 0x62, 0x7d, 0xdd, 0x8f, 0x48, 0x89, 0x45, 0xe0, 0x48, 0x89, 0x55, 0xe8, 0x48, 0xb8, 0x61, 0x8a, 0x34, 0x51, 0x87, 0xf1, 0x89, 0x5d, 0x48, 0x89, 0x45, 0xf0, 0x48, 0x8b, 0x45, 0xd0, 0x48, 0x8b, 0x55, 0xd8, 0x48, 0x89, 0x5, 0xb2, 0x28, 0x0, 0x0, 0x48, 0x89, 0x15, 0xb3, 0x28, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xe0, 0x48, 0x8b, 0x55, 0xe8, 0x48, 0x89, 0x5, 0xac, 0x28, 0x0, 0x0, 0x48, 0x89, 0x15, 0xad, 0x28, 0x0, 0x0, 0x48, 0x8b, 0x45, 0xf0, 0x48, 0x89, 0x5, 0xaa, 0x28, 0x0, 0x0, 0x90, 0x48, 0x8b, 0x45, 0xf8, 0x64, 0x48, 0x33, 0x4, 0x25, 0x28, 0x0, 0x0, 0x0, 0x74, 0x5, 0xe8, 0x85, 0xf8, 0xff, 0xff, 0xc9, 0xc3};
int main(){
    uint32_t key[4];
    hash(key,code,sizeof(code));
    for(size_t i=0;i<16;i++){
        printf("0x%hhx,",*((uint8_t*)key+i));
    }
    printf("\n");
}