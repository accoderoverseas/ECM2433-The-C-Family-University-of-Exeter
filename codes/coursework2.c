#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
    char data;
    struct node *next;
} LinkNode;
LinkNode* initLinkList() {
    LinkNode *l = (LinkNode *)malloc(sizeof(LinkNode));
    l->next = NULL;
    return l;
}
void insert(LinkNode *l, char ch) {
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = ch;
    s->next = l->next;
    l->next = s;
}
void fileReverse(char *fileIn, char *fileOut) {
    FILE *fpIn = fopen(fileIn, "r");
    if (fpIn == NULL) {
        printf("File does not exist!\n");
        return;
    }

    LinkNode *l = initLinkList();
    char ch;
    while ((ch = fgetc(fpIn)) != EOF) {
        insert(l, ch);
    }
    fclose(fpIn);
    
    FILE *fpOut = fopen(fileOut, "w");
    LinkNode *p = l->next;
    while (p) {
        printf("%c", p->data);
        fprintf(fpOut, "%c", p->data);
        p = p->next;
    }
    printf("\n");
    fclose(fpOut);
}
int main(int argc, char *argv[]) {
    fileReverse(argv[1], argv[2]);
    return 0;
}
/*
Execution
gcc -ansi -c coursework2.c -o coursework2.o
gcc coursework2.o -o coursework2
./coursework2 coursework2In.txt coursework2Out.txt
*/