#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOTE_NUM 20
#define MAX_NOTE_LEN 512
typedef struct {
    char *content;
    size_t len;
} Note;

Note ns[MAX_NOTE_NUM];
int add() {
    printf("Please input id: ");
    size_t id;
    scanf("%lu", &id);
    if (id < MAX_NOTE_NUM) {
        printf("Please input len: ");
        size_t len;
        scanf("%lu", &len);
        if (len < MAX_NOTE_LEN) {
            ns[id].content = malloc(len);
            ns[id].len = len;
            printf("Please input the content: ");
            read(0, ns[id].content, ns[id].len);
        }
    }
}
int delete () {
    printf("Please input id: ");
    size_t id;
    scanf("%lu", &id);
    if (id < MAX_NOTE_NUM) {
        if (ns[id].content) {
            free(ns[id].content);
        }
    }
}
int edit() {
    printf("Please input id: ");
    size_t id;
    scanf("%lu", &id);
    if (id < MAX_NOTE_NUM) {
        printf("Please input the content: ");
        read(0, ns[id].content, ns[id].len);
    }
}
int print() {
    printf("Please input id: ");
    size_t id;
    scanf("%lu", &id);
    if (id < MAX_NOTE_NUM) {
        write(1, ns[id].content, ns[id].len);
    }
}
void init() {
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    for (size_t i = 0; i < MAX_NOTE_NUM; i++) {
        ns[i].content = NULL;
        ns[i].len = 0;
    }
}
void p_menu() {
    printf("1. add\n2.delete\n3.edit\nother.exit\n");
}
int main() {
    init();
    while (1) {
        p_menu();
        size_t cmd;
        scanf("%lu", &cmd);
        switch (cmd)
        {
        case 1:
            add();
            break;
        case 2:
            delete();
            break;
        case 3:
            edit();
            break;
        case 4:
            print();
            break;
        default:
            exit(0);
            break;
        }
    }
}