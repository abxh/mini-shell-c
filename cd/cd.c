#include <errno.h>  // errno
#include <stdio.h>  // printf
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // strerror
#include <unistd.h> // getcwd

// cannot change shell pwd - so does not do anything purposeful than being a proof-of-concept:
// https://stackoverflow.com/questions/42340588/why-isnt-chdir-working

// see alternatives to environ:
// https://stackoverflow.com/a/2085385

extern char** environ;

int main(int argc, char* argv[]) {

    char* home_path = NULL;
    for (char** env = environ; *env != 0; env++) {
        if (strncmp("HOME", *env, sizeof("HOME") - 1) == 0) {
            home_path = strchr(*env, '=') + 1;
            break;
        }
    }

    char* cd_path = NULL;
    if (argc > 2) {
        fprintf(stderr, "Only one parameter at most should be provided.\n");
        return EXIT_FAILURE;
    } else if (argc == 1) {
        cd_path = home_path;
    } else if (argc == 2) {
        cd_path = argv[1];
    }

    if (chdir(cd_path) == -1) {
        fprintf(stderr, "%s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

#ifdef DEBUG
    printf("home directory: %s\n", home_path);
    printf("cd to: %s\n", cd_path);
#endif

    return EXIT_SUCCESS;
}
