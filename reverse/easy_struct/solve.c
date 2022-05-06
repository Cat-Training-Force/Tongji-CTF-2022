#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GraphEdge {
    struct GraphEdge *next;
    size_t index;
} GraphEdge;
typedef struct GraphNode{
    char data;
    char (*f)(char a,char b);
} GraphNode;
typedef struct Graph{
    GraphEdge *e;
    GraphNode *n;
    size_t len;
}Graph;
typedef char bool;
char rinc(char a, char b) {
    return a -1;
}
char radd(char a, char b) {
    return a - b;
}
char rsub(char a, char b) {
    return a + b;
}
char xor (char a, char b) {
    return a ^ b;
}
char rrol(char a, char b) {
    if (b <= 8) {
        return (a >> b) | (a << (8 - b));
    }
    return a;
}
void *fs[] = {rinc, radd, rsub, xor,rrol};

void init_graph(Graph *g){
    uint32_t seed = 0xdeadbeef;
    srand(seed);
    uint8_t target[]={240,118,73,167,112,95,54,100,160,172,107,49,90,200,3,80};
    size_t edge[][2]={
        {0,13},
        {13,7},
        {7,11},
        {11,12},
        {11,15},
        {11,14},
        {7,3},
        {3,4},
        {3,5},
        {3,1},
        {1,2},
        {2,6},
        {2,8},
        {6,9},
        {8,10}
    };
    size_t e_len=15;
    g->len=sizeof(target);
    g->e=malloc(sizeof(GraphEdge)*g->len);
    g->n=malloc(sizeof(GraphNode)*g->len);
    for(size_t i=0;i<g->len;i++){
        g->n[i].data=target[i];
        g->e[i].next=NULL;
        g->e[i].index=i;
        g->n[i].f=fs[rand()%(sizeof(fs)/sizeof(fs[0]))];
    }
    for(size_t i=0;i<e_len;i++){
        size_t s0=edge[i][0],s1=edge[i][1];
        GraphEdge *e1=malloc(sizeof(GraphEdge)),*e2=malloc(sizeof(GraphEdge));
        e1->index=s1;
        e2->index=s0;
        e1->next=g->e[s0].next;
        g->e[s0].next=e1->next;
        e2->next=g->e[s1].next;
        g->e[s1].next=e2;
    }
}

void d_first(Graph *g,size_t i, char *input, bool *checked, size_t *cnt,char *res) {
    GraphNode *gn=g->n;
    GraphEdge *ge=g->e,*c;
    checked[i]=1;
    char (*f)(char,char)=gn[i].f;
    res[i]=f(input[*cnt],input[(*cnt+1)%g->len]);
    printf("%p,",f);
    (*cnt)++;
    c=&ge[i];
    while(c!=NULL){
        if(!checked[c->index]){
            d_first(g,c->index,input,checked,cnt,res);
        }
        c=c->next;
    }
}
void depth_first(Graph *g, char *input,char *res) {
    size_t cnt=0;
    bool *checked=malloc(sizeof(bool)*g->len);
    GraphEdge *ge=g->e;
    for(size_t i=0;i<g->len;i++){
        if(!checked[i]){
            d_first(g,i,input,checked,&cnt,res);
        }
    }
    free(checked);
}
void destory_graph(Graph *g) {
    free(g->n);
    GraphEdge *ge=g->e,*p,*c;
    for(size_t i=0;i<g->len;i++){
        c=ge[i].next;
        while(c!=NULL){
            p=c;
            c=c->next;
            free(p);
        }
    }
    free(ge);
}
void gen(Graph *g,char *input,char *res){
    depth_first(g,input,res);
}
int main() {
    char s[]="euI7pi6cNRZ1YuSP";
    char t[17]={0};
    Graph g;
    init_graph(&g);
    gen(&g,s,t);
    printf("\n");
    for(size_t i=0;i<5;i++){
        printf("%p,",fs[i]);
    }
    puts("");
}