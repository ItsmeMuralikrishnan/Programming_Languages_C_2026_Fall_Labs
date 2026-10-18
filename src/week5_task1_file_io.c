/*
 * Name: Muralikrishnan
 * Surname: Prasanth
 * Student ID: 241ADB090
 * Lab 5 - Task 1: Read and write data from files
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    /* Optional bonus: file name from command line, default data.txt */
    const char *filename = (argc > 1) ? argv[1] : "data.txt";

    printf("Writing lines to %s...\n", filename);

    /* Open for writing; always check for NULL */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fclose(fp); /* close so the data is flushed to disk */

    /* Reopen the same file for reading */
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    printf("Reading contents:\n");
    char line[256];
    int count = 0;
    while (fgets(line, sizeof line, fp) != NULL) {
        fputs(line, stdout); /* line already ends with '\n' */
        count++;
    }
    fclose(fp);

    printf("Lines read: %d\n", count);
    return 0;
}