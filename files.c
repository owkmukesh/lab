#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c\n", (mode & S_IXOTH) ? 'x' : '-');
}

void print_file_type(mode_t mode) {
    if (S_ISREG(mode))
        printf("File Type: Regular File\n");
    else if (S_ISDIR(mode))
        printf("File Type: Directory\n");
    else if (S_ISLNK(mode))
        printf("File Type: Symbolic Link\n");
    else if (S_ISFIFO(mode))
        printf("File Type: FIFO (named pipe)\n");
    else if (S_ISBLK(mode))
        printf("File Type: Block device\n");
    else if (S_ISSOCK(mode))
        printf("File Type: Socket\n");
    else
        printf("File Type: Unknown\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file/directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int success = 0;
    for (int i = 1; i < argc; i++) {
        struct stat file_stat;

        if (stat(argv[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }
        success = 1;

        printf("Information for '%s':\n", argv[i]);
        print_file_type(file_stat.st_mode);
        printf("Number of links: %ld\n", (long)file_stat.st_nlink);
        printf("Last Access Time: %s", ctime(&file_stat.st_atime));
        print_permissions(file_stat.st_mode);
    }

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
