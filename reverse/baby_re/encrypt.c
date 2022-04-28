#include <inttypes.h>
#include <string.h>

void encrypt(uint8_t* v, size_t len) {
    uint32_t delta = 0x9e3779b9;
    uint32_t k0 = 1936287828u,k1=762538285u,k2=1953719650u,k3=2036689709u;
    if(len%8!=0)len-=8;
    for (size_t j = 0; j < len; j += 8) {
        uint32_t v0 = *(uint32_t*)&v[j], v1 = *(uint32_t*)&v[j+4], sum = 0, i;
        for (i = 0; i < 32; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
        *(uint32_t*)&v[j] = v0;
        *(uint32_t*)&v[j+4] = v1;
    }
}
int main(){
    char s[]="tjctf{34Bf9acCdD8e412871Ae3ceCE-8A0Ca33}";
    encrypt(s,strlen(s));
    for(size_t i=0;i<strlen(s);i++){
        printf("0x%hhx,",s[i]);
    }
    printf("\n");
}