#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char fd_path[64];
    snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd", pid);

    DIR *dir = opendir(fd_path);
    if (!dir) {
        perror("Error opening fd directory");
        fprintf(stderr, "Hint: The process %d might not exist or you lack permission.\n", pid);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    char link_path[PATH_MAX];
    char target_path[PATH_MAX];
    ssize_t len;
    int count = 0;

    printf("=== Open Files for PID %d ===\n", pid);

    while ((entry = readdir(dir)) != NULL) {
        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))
            continue;

        snprintf(link_path, sizeof(link_path), "%s/%s", fd_path, entry->d_name);

        len = readlink(link_path, target_path, sizeof(target_path) - 1);
        if (len == -1) {
            fprintf(stderr, "FD %s: [Permission denied or invalid link]\n", entry->d_name);
            continue;
        }

        target_path[len] = '\0';
        printf("FD %s -> %s\n", entry->d_name, target_path);
        count++;
    }

    closedir(dir);

    printf("==============================\n");
    printf("Total open files: %d\n", count);
    return 0;
}
