#define _GNU_SOURCE
#include <ctype.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/stat.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "include/format.h"

/******************************************************************
 * Argument
 * filename string -> real absolute path (realpath)
 * descriptor or FILE* -> absolute path of the corresponding file
 * (readlink)
 * mode or flag, print out in octal.
 * integer, print out in decimal.
 * regular character buffer, print out up to 32 byte.
 * convert unprintable char to '.'
 * Return Value
 * integer, decimal
 * pointer, %p
 * string, "%s"
 ******************************************************************/

FILE* fopen(const char* pathname, const char* mode)
{
    FILE* (*f)(const char*, const char*);
    *(FILE**)(&f) = dlsym(RTLD_NEXT, "fopen");

    char* r_path = resolved_path(pathname);

    FILE* reval = f(r_path, mode);

    show("fopen(\"%s\", \"%s\") = %p\n", r_path, mode, reval);

    return reval;
}

int creat(const char* pathname, mode_t mode)
{
    int (*c)(const char*, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "creat");

    char* r_path = resolved_path(pathname);

    int reval = c(r_path, mode);

    show("creat(\"%s\", %o) = %d\n", r_path, mode, reval);

    return reval;
}

int chmod(const char* pathname, mode_t mode)
{
    int (*c)(const char*, mode_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "chmod");

    char* r_path = resolved_path(pathname);

    int reval = c(r_path, mode);

    show("chmod(\"%s\", %o) = %d\n", r_path, mode, reval);
    return reval;
}

int chown(const char* pathname, uid_t owner, gid_t group)
{
    int (*c)(const char*, uid_t, gid_t);
    *(int**)(&c) = dlsym(RTLD_NEXT, "chown");

    char* r_path = resolved_path(pathname);

    int reval = c(r_path, owner, group);

    show("chown(\"%s\", %d, %d) = %d\n", r_path, owner, group, reval);
    return reval;
}

int rename(const char* oldpath, const char* newpath)
{
    int (*c)(const char*, const char*);
    *(int**)(&c) = dlsym(RTLD_NEXT, "rename");

    char* r_oldpath = resolved_path(oldpath);
    char* r_newpath = resolved_path(newpath);

    int reval = c(r_oldpath, r_newpath);

    show("rename(\"%s\", \"%s\") = %d\n", r_oldpath, r_newpath, reval);

    return reval;
}

int open(const char* pathname, int flags, ...)
{
    mode_t mode = 0;
    if (__OPEN_NEEDS_MODE(flags)) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }
    int (*c)(const char*, int, ...);
    *(int**)(&c) = dlsym(RTLD_NEXT, "open");

    char* r_path = resolved_path(pathname);

    int reval = c(r_path, flags, mode);

    show("open(\"%s\", %o, %o) = %d\n", r_path, flags, mode, reval);

    return reval;
}

ssize_t write(int fd, const void* buf, size_t count)
{
    ssize_t (*c)(int, const void*, size_t);
    *(ssize_t**)(&c) = dlsym(RTLD_NEXT, "write");

    char name[0xFFF] = { '\0' };
    fd_path(fd, name);

    char str[32] = { '\0' };
    check_buffer(buf,str);

    ssize_t reval = c(fd, buf, count);

    show("write(\"%s\", \"%s\", %ld) = %lu\n", name, (const char*)str, count, reval);

    return reval;
}

int close(int fd)
{
    int (*c)(int);
    *(int**)(&c) = dlsym(RTLD_NEXT, "close");

    char name[0xFFF] = { '\0' };
    fd_path(fd, name);

    int reval = c(fd);

    show("close(\"%s\") = %d\n", name, reval);

    return reval;
}

ssize_t read(int fd, void* buf, size_t count)
{
    ssize_t (*c)(int, void*, size_t);
    *(ssize_t**)(&c) = dlsym(RTLD_NEXT, "read");

    ssize_t reval = c(fd, buf, count);

    char name[0xFFF] = {'\0'};
    fd_path(fd, name);

    char str[32] = {'\0'};
    check_buffer(buf, str);

    show("read(%s, \"%s\", %ld) = %ld\n", name, str, count, reval);

    return reval;
}

FILE* tmpfile(void)
{
    FILE* (*f)();
    *(FILE**)(&f) = dlsym(RTLD_NEXT, "tmpfile");

    FILE* reval = f();

    show("tmpfile() = %p\n", reval);

    return reval;
}

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t (*c)();
    *(size_t**)(&c) = dlsym(RTLD_NEXT, "fread");

    size_t reval = c(ptr, size, nmemb, stream);

    char name[0xFFF] = {'\0'};
    fd_path(stream, name);
    char str[32] = { '\0' };
    check_buffer((const void*)ptr, str);

    int (*f)();
    *(int**)(&f) = dlsym(RTLD_NEXT, "fprintf");

    show("fread(\"%s\", %ld, %ld, \"%s\") = %ld\n", str, size, nmemb, name, reval);

    return reval;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t (*c)();
    *(size_t**)(&c) = dlsym(RTLD_NEXT, "fwrite");

    size_t reval = c(ptr, size, nmemb, stream);

    char name[0xFFF] = {'\0'};
    fd_path(stream, name);
    char str[32] = { '\0' };
    check_buffer(ptr, str);

    int (*f)();
    *(int**)(&f) = dlsym(RTLD_NEXT, "fprintf");

    show("fwrite(\"%s\", %ld, %ld, \"%s\") = %ld\n", str, size, nmemb, name, reval);

    return reval;
}

int fclose(FILE* stream)
{
    int (*c)();
    *(int**)(&c) = dlsym(RTLD_NEXT, "fclose");

    char name[0xFFF] = { '\0' };
    fd_path(stream, name);

    int reval = c(stream);

    show("fclose(\"%s\") = %d\n", name, reval);

    return reval;
}

int remove(const char* pathname)
{
    int (*c)();
    *(int**)(&c) = dlsym(RTLD_NEXT, "remove");

    char *r_path = resolved_path(pathname);

    int reval = c(r_path);

    show("remove(\"%s\") = %d\n", r_path, reval);

    return reval;
}
