#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){
    int ch;
    size_t i = 0;
    if(!linep || !n || !fp){
        errno = EINVAL;
        return -1;
    }
    if(*linep == NULL){
        if(NULL==(*linep = malloc(*n=128))){
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(i + 1 >= *n){
            char *temp = realloc(*linep, *n + 128);
            if(!temp){
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        (*linep)[i++] = ch;
        if(ch == delim)
            break;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : i;
}
ssize_t getline(char **linep, size_t *n, FILE *fp){
    return getdelim(linep, n, '\n', fp);
}

void reverse(char *s)
{
    int k = strlen(s) - 1, i = strlen(s) - 1;
    char rev[256];
    strcpy(rev, s);
    for (; --i >= 0;)
        rev[k - i - 1] = s[i];
    strcpy(s, rev);
}

int main()
{
    char *p;
    if (freopen("file.txt", "r", stdin) == NULL)
    {
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }
    int k = 0;
    size_t size = 256;
    while (getline(&p, &size, stdin) != -1)
    {
        k++;
        if (k % 2 == 0)
            reverse(p);
        printf("%s", p);
    }
    fclose(stdin);
}
