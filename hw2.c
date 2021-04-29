#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


FILE* fopen(const char* pathname, const char* mode)
{
    FILE* (*f)(const char*, const char*);
    char msg[256] = "[logger] fopen(\" ";
    *(FILE**)(&f) = dlsym(RTLD_NEXT, "fopen");
    strcat(msg, pathname);
    strcat(msg, "\", ");
    strcat(msg, mode);
    strcat(msg, "\") = 0x");
    char buf[64] = { '\0' };
    sprintf(buf, "%x", &f);
    strcat(msg, buf);
    strcat(msg, "\n");
    write(2, msg, strlen(msg));

    return f(pathname, mode);
}


int creat(const char* pathname, mode_t mode)
{
    int (*c)(const char*, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "creat");
    char msg[256] = "[logger] creat(\" ";
    strcat(msg, pathname);
    strcat(msg, "\", ");
    char buf[64] = { '\0' };
    sprintf(buf, "%u", mode);
    strcat(msg, buf);
    strcat(msg, "\") = ");
    write(2, msg, strlen(msg));
    return c(pathname, mode);
}


int chmod(const char* pathname, mode_t mode)
{
    int(c)(const char*, mode_t);
    *(int*)(&c) = dlsym(RTLD_NEXT, "chmod");
    char msg[256] = "[logger] chmod(\" ";
    strcat(msg, pathname);
    strcat(msg, "\", ");
    char buf[64] = { '\0' };
    sprintf(buf, "%u", mode);
    strcat(msg, buf);
    strcat(msg, "\") = ");
    write(2, msg, strlen(msg));
    return c(pathname, mode);
}


int chown(const char* pathname, uid_t owner, gid_t group)
{
    int(c)(const char*, uid_t, gid_t);
    *(int*)(&c) = dlsym(RTLD_NEXT, "chown");
    char msg[256] = "[logger] chown(\" ";
    strcat(msg, pathname);
    strcat(msg, "\", ");
    char buf[64] = { '\0' };
    sprintf(buf, "%u", uid_t);
    strcat(msg, buf);
    strcat(msg, ", ");
    memset(buf, 0, 64);
    sprintf(buf, "%u", gid_t);
    strcat(msg, buf);
    strcat(msg, "\") = ");
    write(2, msg, strlen(msg));
    return c(pathname, owner, group);
}


int rename(const char *oldpath, const char *newpath)
{
    int(c)(const char*, const char*);
    *(int*)(&c) = dlsym(RTLD_NEXT, "rename");
    char msg[256] = "[logger] rename(\" ";
    strcat(msg, oldpath);
    strcat(msg, "\", \"");
    strcat(msg, newpath);
    strcat(msg, "\") = ");

    write(2, msg, strlen(msg));
    return c(oldpath, newpath);
}


int open(const char * pathname, int flags)
{
    int(c)(const char*, int);
    *(int*)(&c) = dlsym(RTLD_NEXT, "open");
    char msg[256] = "[logger] open(\" ";
    strcat(msg, pathname);
    strcat(msg, "\", ");
    char temp[10]={'\0'};
    sprintf(temp, "%d", flags);
    strcat(msg, temp);
    strcat(msg, " ) = ");

    write(2, msg, strlen(msg));
    return c(pathname, flags);
}
