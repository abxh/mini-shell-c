#include <errno.h>  // errno
#include <stdio.h>  // printf
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // strerror
#include <unistd.h> // getcwd

int main(void) {
    size_t n = 4096;
    char* buf = malloc(n);

    if (!getcwd(buf, n)) {
        printf("%s.\n", strerror(errno));
        
        free(buf);
        return EXIT_FAILURE;
    }

    printf("%s\n", buf);

    free(buf);
    return EXIT_SUCCESS;
}
