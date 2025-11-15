#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct dirent *de;
    DIR *dr = opendir(".");
    
    if (dr == NULL) {
        printf("Could not open directory\\n");
        return 0;
    }
    
    while ((de = readdir(dr)) != NULL) {
        struct stat st;
        stat(de->d_name, &st);
        printf("Name: %s\\t Size: %ld bytes\\t Modified: %s",
            de->d_name, st.st_size, ctime(&st.st_mtime));
    }
    
    closedir(dr);
    return 0;
}
