#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int cmd_opt = 0;
    extern char* optarg;
    extern int optind, opterr, optopt;
    int pflag = 0, oflag = 0, cflag = 0;
    setenv("LD_PRELOAD", "./logger.so", 1);
    setenv("OUTPUT", "2", 1);
    if (argc == 1) {
        fprintf(stderr, "no command given.\n");
        exit(1);
    }

    while (1) {
        cmd_opt = getopt(argc, argv, "p::o::-::");
        if (cmd_opt == -1) {
            break;
        }

        if (cmd_opt == 'p') {
            printf("%s\n", argv[optind]);
            setenv("LD_PRELOAD", argv[optind], 1);
        } else if (cmd_opt == 'o') {
            setenv("OUTPUT", "3", 1);
        } else if (cmd_opt == '-') {
            cflag = 1;
        } else {
            fprintf(stderr, "usage: %s [-o file] [-p sopath] [--] cmd [cmd args ...]\n\
                    -p: set the path to logger .so, default = ./logger.so\n\
                    -o: print output to file, print to \"stderr\" if no file specified\n\
                    --: separate the arguments for logger and for the command\n",
                argv[0]);
            exit(1);
        }
    }
    execlp("ls", "ls -al", NULL);
    printf("optind = %d\n", optind);

    return 0;
}
