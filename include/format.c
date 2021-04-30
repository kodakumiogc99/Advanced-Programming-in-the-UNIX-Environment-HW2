#define _GNU_SOURCE

#include <ctype.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
FILE* output = NULL;

void show(const char* format, ...)
{
    char str[0xFFF] = { '\0' };
    sprintf(str, "[logger] %s", format);
    if (output == NULL) {
        char* env = getenv("OUTPUT");
        if (env == NULL) {
            output = stderr;
        } else {
            FILE* (*f)(const char*, const char*);
            *(FILE**)(&f) = dlsym(RTLD_NEXT, "fopen");
            output = f(env, "w");
        }
    }
    va_list args;
    va_start(args, format);
    vfprintf(output, str, args);
    va_end(args);
}

void check_buffer(const char* buf, char str[], size_t count)
{
    /* printf("check_buffer: "); */
    /* for (int i = 0; i < 32; i++) { */
        /* printf("%d%c", str[i], (i == 31 ? '\n' : ' ')); */
    /* } */
    /* printf("check_buffer: "); */
    /* for (int i = 0; i < 32 && i < strlen(buf); i++) { */
        /* printf("%d%c", buf[i], (i == 31 ? '\n' : ' ')); */
    /* } */

    for (int i = 0; i < 32 && i < strlen(buf) && i < count; i++)
    {
        if (isprint(buf[i])) {
            str[i] = buf[i];
        }
        else {
            str[i] = '.';
        }
    }

    /* printf("str: %s\n", str); */
}

char* resolved_path(const char* pathname)
{
    char* r_path = NULL;
    char* exist;
    exist = realpath(pathname, NULL);
    if (exist == NULL)
        r_path = (char*)pathname;
    else
        r_path = exist;
    return r_path;
}

void FILE_to_path(FILE* stream, char* name)
{
    char lnk[0xFFF] = { '\0' };

    sprintf(lnk, "/proc/self/fd/%d", fileno(stream));
    ssize_t s = readlink(lnk, name, 0xFFF);
}

void int_to_path(int fd, char* name)
{
    char lnk[0xFFF] = { '\0' };

    sprintf(lnk, "/proc/self/fd/%d", fd);
    ssize_t s = readlink(lnk, name, 0xFFF);
}
