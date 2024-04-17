#include <errno.h>  // errno
#include <stdio.h>  // printf, fprintf, stderr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // strerror
#include <unistd.h> // getcwd

int main(void) {
    char buf[1024] = {0};

    if (getcwd(buf, sizeof(buf)) == NULL) {
        fprintf(stderr, "%s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%s\n", buf);
    return EXIT_SUCCESS;
}
