#include <dirent.h>       // opendir
#include <errno.h>        // errno
#include <linux/limits.h> // NAME_MAX
#include <stdio.h>        // printf, fprintf, stderr
#include <stdlib.h>       // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>       // strerror
#include <sys/stat.h>     // stat
#include <time.h>
#include <unistd.h> // getcwd

// better explained in:
// https://stackoverflow.com/questions/64815056/opening-files-in-a-directory-with-opendir-and-readdir-in-c
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
// https://pubs.opengroup.org/onlinepubs/009696799/functions/stat.html

// dirent struct:
// https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/dirent.h#Member_types
// struct dirent {
//     ino_t d_ino;   // file serial number
//     char d_name[]; // name of entry (will not exceed a size of NAME_MAX)
//
//     // may contain the following members, depending on the platform:
//     off_t d_off;                 // file offset
//     unsigned short int d_reclen; // length of the dirent record
//     unsigned short int d_namlen; // length of name
//     unsigned int d_type;         // type of file
// };

// qsort:
// https://en.cppreference.com/w/c/algorithm/qsort

// stat struct (at least contains):
// https://en.wikibooks.org/wiki/C_Programming/POSIX_Reference/sys/stat.h/stat#stat()_functions_and_stat_structure
// struct stat {
//      dev_t       st_dev;     /* ID of device containing file */
//      ino_t       st_ino;     /* inode number */
//      mode_t      st_mode;    /* protection */
//      nlink_t     st_nlink;   /* number of hard links */
//      uid_t       st_uid;     /* user ID of owner */
//      gid_t       st_gid;     /* group ID of owner */
//      dev_t       st_rdev;    /* device ID (if special file) */
//      off_t       st_size;    /* total size, in bytes */
//      time_t      st_atime;   /* time of last access */
//      time_t      st_mtime;   /* time of last modification */
//      time_t      st_ctime;   /* time of last status change */
//      blksize_t   st_blksize; /* blocksize for filesystem I/O */
//      blkcnt_t    st_blocks;  /* number of blocks allocated */
// };

int dirname_cmp(const void* name1, const void* name2) {
    char* name1_as_char_p = (char*)name1;
    char* name2_as_char_p = (char*)name2;
    size_t name1_len = strlen(name1_as_char_p);
    size_t name2_len = strlen(name2_as_char_p);

    if (name1_len != name2_len) {
        return (name1_len < name2_len) ? -1 : 1;
    }

    return strcmp(name1, name2);
}

int main(void) {
    DIR* dir_p = opendir(".");
    if (dir_p == NULL) {
        fprintf(stderr, "%s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    struct dirent* dirent_p = NULL;
    size_t count = 0;
    size_t capacity = 2;
    char(*str_p)[NAME_MAX] = malloc(capacity * sizeof(char*) * NAME_MAX);
    while ((dirent_p = readdir(dir_p)) != NULL) {
        strncpy(str_p[count], dirent_p->d_name, NAME_MAX);
        count++;
        if (count >= capacity / 2) {
            capacity *= 2;
            char(*tmp_p)[NAME_MAX] = reallocarray(str_p, capacity, sizeof(char*) * NAME_MAX);
            if (tmp_p == NULL) {
                fprintf(stderr, "Failed to allocate memory.\n");
                free(str_p);
                return EXIT_FAILURE;
            }
            str_p = tmp_p;
        }
    }

    qsort(str_p, count, sizeof(*str_p), dirname_cmp);

    int pad = strlen(str_p[count - 1]);

    struct stat sb;
    for (size_t i = 0; i < count; i++) {
        stat(str_p[i], &sb);
        if (stat(str_p[i], &sb) == -1) {
            fprintf(stderr, "%s.\n", strerror(errno));
            free(str_p);
            closedir(dir_p);
            return EXIT_FAILURE;
        }
        printf("%*s : size=%lu bytes, inode=%lu, date=%lu sec, perms=", pad, str_p[i], sb.st_size, sb.st_ino, sb.st_mtim.tv_sec);

        // Convert permissions to string:
        // https://stackoverflow.com/a/10323127
        printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
        printf((sb.st_mode & S_IRUSR) ? "r" : "-");
        printf((sb.st_mode & S_IWUSR) ? "w" : "-");
        printf((sb.st_mode & S_IXUSR) ? "x" : "-");
        printf((sb.st_mode & S_IRGRP) ? "r" : "-");
        printf((sb.st_mode & S_IWGRP) ? "w" : "-");
        printf((sb.st_mode & S_IXGRP) ? "x" : "-");
        printf((sb.st_mode & S_IROTH) ? "r" : "-");
        printf((sb.st_mode & S_IWOTH) ? "w" : "-");
        printf((sb.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
    }

    free(str_p);
    if (closedir(dir_p) == -1) {
        fprintf(stderr, "%s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
