#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    creat("/home/gura/hw2/tmp/aaaa", 0600);
    chmod("/home/gura/hw2/tmp/aaaa", 0666);
    chown("/home/gura/hw2/tmp/aaaa", 65534, 65534);
    rename("/home/gura/hw2/tmp/aaaa", "/home/gura/hw2/tmp/bbbb");
    int fd = open("/home/gura/hw2/tmp/bbbb", 01101, 0666);
    write(fd, "cccc", 5);
    close(fd);
    int fd2 = open("/home/gura/hw2/tmp/bbbb", 00, 00);
    char tmp[0xFFF] = { '\0' };
    read(fd2, tmp, 100);
    close(fd2);
    FILE* f = tmpfile();
    fwrite("cccc", 1, 5, f);
    fclose(f);
    char ptr[0xFFF];
    FILE* n = fopen("/home/gura/hw2/tmp/bbbb", "r");
    fread(ptr, 1, 100, n);
    fclose(n);
    remove("/home/gura/hw2/tmp/bbbb");
    write(1, "sample done.\n", 14);
    return 0;
}
