#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char filename[100];
    char text[200];
    struct stat st;

    printf("Enter file name: ");
    scanf("%s", filename);

    stat(filename, &st);
    printf("File size before: %ld bytes\n", st.st_size);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    printf("Enter text to append: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    fputs(text, fp);
    fclose(fp);

    return 0;
}
