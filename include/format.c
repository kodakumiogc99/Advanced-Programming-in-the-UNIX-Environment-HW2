#define _GNU_SOURCE

#include <dlfcn.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>

void show(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char str[0xFFF] = "[logger] ";
    strcat(str, format);
    int (*f)();
    *(int**)(&f) = dlsym(RTLD_NEXT, "fprintf");
    f(stderr, str, args);
    va_end(args);
}

void check_buffer(const void* buf, char* str)
{
    int len;
    if( strlen(buf) > 32 )
        len = 32;
    else
        len = strlen(buf) + 1;
    memcpy(str, buf, len);
    for (int i = 0; i < len; i++)
        if (isprint(str[i]) == 0)
            str[i] = '.';
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

