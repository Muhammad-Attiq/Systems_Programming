#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

void createFile() {
    char name[50], text[200];
    printf("Enter file name: ");
    scanf("%s", name);
    FILE *fp = fopen(name, "w");
    getchar();
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    fputs(text, fp);
    fclose(fp);
    printf("File created successfully.\n");
}

void readFile() {
    char name[50], ch;
    printf("Enter file name: ");
    scanf("%s", name);
    FILE *fp = fopen(name, "r");
    if (!fp) {
        printf("File not found!\n");
        return;
    }
    printf("\nFile contents:\n");
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
    printf("\n");
}

void copyFile() {
    char src[50], dest[50], ch;
    printf("Enter source file: ");
    scanf("%s", src);
    printf("Enter destination file: ");
    scanf("%s", dest);
    FILE *fs = fopen(src, "r");
    FILE *fd = fopen(dest, "w");
    if (!fs || !fd) {
        printf("Error opening file.\n");
        return;
    }
    while ((ch = fgetc(fs)) != EOF)
        fputc(ch, fd);
    fclose(fs);
    fclose(fd);
    printf("File copied successfully.\n");
}

void fileInfo() {
    char name[50];
    struct stat st;
    printf("Enter file name: ");
    scanf("%s", name);
    if (stat(name, &st) == 0) {
        printf("File: %s\n", name);
        printf("Size: %ld bytes\n", st.st_size);
        printf("Last modified: %s", ctime(&st.st_mtime));
    } else {
        printf("File not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n==== File Utility Menu ====\n");
        printf("1. Create and Write File\n");
        printf("2. Read File\n");
        printf("3. Copy File\n");
        printf("4. Display File Info\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createFile(); break;
            case 2: readFile(); break;
            case 3: copyFile(); break;
            case 4: fileInfo(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
