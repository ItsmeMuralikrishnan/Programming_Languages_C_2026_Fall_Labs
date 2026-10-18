/*
 * Name: Muralikrishnan
 * Surname: Prasanth
 * Student ID: 241ADB090
 * Lab 5 - Bonus Task 4: Binary file version
 */
#include <stdio.h>

typedef struct Student {
    char name[50];
    int age;
    float gpa;
} Student;

/* Writes the whole struct as raw bytes. 0 = ok, -1 = error */
int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) return -1;

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return -1;

    size_t written = fwrite(s, sizeof(Student), 1, fp);
    if (fclose(fp) != 0 || written != 1) return -1;
    return 0;
}

/* Reads the whole struct back. 0 = ok, -1 = error */
int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) return -1;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return -1;

    size_t got = fread(out, sizeof(Student), 1, fp);
    fclose(fp);
    return (got == 1) ? 0 : -1;
}

/* File size in bytes via fseek/ftell, -1 on error */
long file_size(const char *filename) {
    if (filename == NULL) return -1;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return -1;

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }
    long size = ftell(fp);
    fclose(fp);
    return size;
}

/* Same text format as Task 2: "name age gpa" */
static int save_student_text(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return -1;

    int rc = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    if (fclose(fp) != 0 || rc < 0) return -1;
    return 0;
}

int main(void) {
    /* Zero-initialise so unused name bytes don't write leftover memory */
    Student s = {0};
    Student loaded = {0};
    snprintf(s.name, sizeof s.name, "%s", "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student in binary format...\n");
    if (save_student_binary(&s, "student.bin") != 0) {
        fprintf(stderr, "Error: could not save binary file.\n");
        return 1;
    }
    if (save_student_text(&s, "student.txt") != 0) {
        fprintf(stderr, "Error: could not save text file.\n");
        return 1;
    }

    printf("Loading student from binary file...\n");
    if (load_student_binary("student.bin", &loaded) != 0) {
        fprintf(stderr, "Error: could not load binary file.\n");
        return 1;
    }
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    printf("Text file size: %ld bytes\n", file_size("student.txt"));
    printf("Binary file size: %ld bytes\n", file_size("student.bin"));
    return 0;
}