#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
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
    *(FILE**)(&f) = dlsym(RTLD_NEXT, "fopen");

    FILE* reval = f(pathname, mode);

    fprintf(stderr, "[logger] fopen(\"%s\", \"%s\") = %p\n", pathname, mode, reval);

    return reval;
}

int creat(const char* pathname, mode_t mode)
{
    int (*c)(const char*, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "creat");

    int reval = c(pathname, mode);

    fprintf(stderr, "[logger] creat(\"%s\", %d) = %d\n", pathname, mode, reval);

    return reval;
}

int chmod(const char* pathname, mode_t mode)
{
    int(*c)(const char*, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "chmod");

    int reval = c(pathname, mode);

    fprintf(stderr, "[logger] chmod(\"%s\", %d) = %d\n", pathname, mode, reval);

    return c(pathname, mode);
}

int chown(const char* pathname, uid_t owner, gid_t group)
{
    int(*c)(const char*, uid_t, gid_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "chown");

    int reval = c(pathname, owner, group);

    fprintf(stderr, "[logger] chown(\"%s\", %d, %d,) = %d\n", pathname, owner, group, reval);
    return reval;
}


int rename(const char* oldpath, const char* newpath)
{
    int(*c)(const char*, const char*);
    *(int**)(&c) = dlsym(RTLD_NEXT, "rename");

    int reval = c(oldpath, newpath);

    fprintf(stderr, "[logger] rename(\"%s\", \"%s\") = %d\n", oldpath, newpath, reval);

    return reval;
}


int open(const char* pathname, int flags, mode_t mode)
{
    int(*c)(const char*, int, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "open");

    int reval = c(pathname, flags, mode);

    fprintf(stderr, "[logger] open(\"%s\", %d, %d) = %d\n", pathname, flags, mode, reval);

    return reval;
}

ssize_t write(int fd, const void *buf, size_t count)
{
    ssize_t(*c)(int, const void*, size_t);
    *(ssize_t**)(&c) = dlsym(RTLD_NEXT, "write");

    ssize_t reval = c(fd, buf, count);

    fprintf(stderr, "[logger] write(%d, \"%p\", %ld) = %lu\n", fd, buf, count, reval);

    return reval;
}

int close(int fd)
{
    int(*c)(int);
    *(int**)(&c) = dlsym(RTLD_NEXT, "close");

    int reval = c(fd);

    fprintf(stderr, "[logger] close(%d) = %d\n", fd, reval);

    return reval;
}

ssize_t read(int fd, void *buf, size_t count)
{
    ssize_t(*c)(int, void*, size_t);
    *(ssize_t**)(&c) = dlsym(RTLD_NEXT, "read");

    ssize_t reval = c(fd, buf, count);

    fprintf(stderr, "[logger] read(%d, \"%p\", %ld) = %ld\n", fd, buf, count, reval);

    return reval;
}

FILE *tmpfile(void)
{
    FILE*(*f)();
    *(FILE**)(&f) = dlsym(RTLD_NEXT, "tmpfile");

    FILE *reval = f();

    fprintf(stderr, "[logger] tmpfile() = %p\n", reval);

    return reval;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t(*c)();
    *(size_t**)(&c) = dlsym(RTLD_NEXT, "fread");

    size_t reval = c(ptr, size, nmemb, stream);

    fprintf(stderr, "[logger] fread(\"%p\", %ld, %ld, \"%p\") = %ld\n", ptr, size, nmemb, stream, reval);

    return reval;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t(*c)();
    *(size_t**)(&c) = dlsym(RTLD_NEXT, "fwrite");

    size_t reval = c(ptr, size, nmemb, stream);

    fprintf(stderr, "[logger] fwrite(\"%p\", %ld, %ld, \"%p\") = %ld\n", ptr, size, nmemb, stream, reval);

    return reval;
}

int fclose(FILE *stream)
{
    int(*c)();
    *(int**)(&c) = dlsym(RTLD_NEXT, "fclose");

    int reval = c(stream);

    fprintf(stderr, "[logger] fclose(\"%p\") = %d\n", stream, reval);

    return reval;
}

int remove(const char *pathname)
{
    int(*c)();
    *(int**)(&c) = dlsym(RTLD_NEXT, "remove");

    int reval = c(pathname);

    fprintf(stderr, "[logger] remove(\"%s\") = %d\n", pathname, reval);

    return reval;
}
