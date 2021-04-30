#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int cmd_opt = 0;
    extern char* optarg;
    extern int optind, opterr, optopt;
    setenv("LD_PRELOAD", "./logger.so", 1);

    while (1) {
        cmd_opt = getopt(argc, argv, "p:o:");
        if (cmd_opt == -1) {
            break;
        }

        if (cmd_opt == 'p') {
            setenv("LD_PRELOAD", optarg, 1);
        } else if (cmd_opt == 'o') {
            setenv("OUTPUT", optarg, 1);
        } else {
            fprintf(stderr, "usage: %s [-o file] [-p sopath] [--] cmd [cmd args ...]\n\
                    -p: set the path to logger .so, default = ./logger.so\n\
                    -o: print output to file, print to \"stderr\" if no file specified\n\
                    --: separate the arguments for logger and for the command\n",
                argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if (optind >= argc) {
        fprintf(stderr, "no command given.\n");
        exit(EXIT_FAILURE);
    }
    execvp(argv[optind], (argv + optind));

    return 0;
}
