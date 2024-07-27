#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "msString.h"
msString msSetString(char *s) {
    msString res = (msString) s;
    return res;
}
char *msGetString(msString s) {
    return s;
}
void msCopy(msString *s1, msString s2) {
    *s1 = s2;
}
void msConcatenate(msString *s1, msString s2) {
    int i;
    int length1 = msLength(*s1), length2 = msLength(s2);
    char *str1 = msGetString(*s1), *str2 = msGetString(s2);
    char *str = (char *)malloc((length1 + length2) * sizeof(char));
    for (i = 0; i < length1; i++) {
        str[i] = str1[i];
    }
    for (i = length1; i < length1 + length2; i++) {
        str[i] = str2[i - length1];
    }
    str[length1 + length2] = '\0';
    msString s3 = msSetString(str);
    *s1 = s3;
    // Avoid memory leak
    free(str);
}
long int msLength(msString s) {
    char *str = msGetString(s);
    long int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
int msCompare(msString s1, msString s2) {
    int i;
    char *str1 = msGetString(s1), *str2 = msGetString(s2);
    int length1 = msLength(s1), length2 = msLength(s2);
    int commonLength = length1 > length2 ? length2 : length1;
    for (i = 0; i < commonLength; i++) {
        if (str1[i] != str2[i]) {
            return 1;
        }
    }
    return length1 != length2;
}
int msCompareString(msString s1, char *s2) {
    int i;
    int *ans = (int *)malloc(256 * sizeof(int));
    char *str1 = msGetString(s1);
    int res = 0;
    for (i = 0; i < 256; i++) {
        ans[i] = 0;
    }
    for (i = 0; i < msLength(s1); i++) {
        ans[str1[i]]++;
    }
    for (i = 0; i < strlen(s2); i++) {
        ans[s2[i]]--;
    }
    for (i = 0; i < 256; i++) {
        if (ans[i] != 0) {
            res = 1;
            break;
        }
    }
    // Avoid memory leak
    free(ans);
    return res;
}
void msError(char *s) {
    printf("%s\n", s);
    exit(1);
}
int main() {
    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World!");
    msString mscopy = NULL;

    printf("String |%s| is %ld characters long (%p).\n", msGetString(ms), msLength(ms), ms);
    msCopy(&mscopy, ms);
    printf("Copied string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);

    printf("Compare ms with mscopy: %d\n", msCompare(ms, mscopy));
    printf("Compare ms with ms2: %d\n", msCompare(ms, ms2));
    printf("Compare ms with Hello: %d\n", msCompareString(ms, "Hello"));
    printf("Compare ms with HelloX: %d\n", msCompareString(ms, "HelloX"));
    printf("Compare ms with Hella: %d\n", msCompareString(ms, "Hella"));

    msConcatenate(&mscopy, ms2);
    printf("Concatenated string |%s| is %ld characters long (%p).\n", msGetString(mscopy), msLength(mscopy), mscopy);
    return 0;
}
/*
Execution
gcc -ansi -c coursework3.c -o coursework3.o
gcc coursework3.o -o coursework3
./coursework3
*/