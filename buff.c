
/*
 * C Program to Remove given Word from a String
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// onclick=' '
void removeSubstr (char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';

        // match+len[0] == ' or "
        char* leftover = match+len;
        char apos = leftover[0];
        // printf("%c\n", apos);
        
        // find the next occurence of ' or "
        char *ret;
        ret = strchr(leftover+1, apos);
        // ret + 1 the rest of the string we want
        // puts(ret+1);

        int offset = strlen(leftover) - strlen(ret) + 1;
        strcat(string, match+len+offset);
    }

}
 
int main()
{
    char * buffer = 0;
    long length;
    FILE * f = fopen("buff.html", "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
        fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer) {
        puts(buffer);
        puts("NEW:");
        removeSubstr(buffer, "onclick=");
        removeSubstr(buffer, "onmouseup=");
        puts(buffer);
        // start to process your data / extract strings here...
    }

    // remember to free

    return 0;
}



