/*
 * Name: Muralikrishnan
 * Surname: Prasanth
 * Student ID: 241ADB090
 * Lab 5 - Task 2: Save and load structured records
 */
#include <stdio.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int age;
    float gpa;
} Student;

/* Saves one record as a single text line: "name age gpa". 0 = ok, -1 = error */
int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) return -1;

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return -1;

    int rc = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    if (fclose(fp) != 0 || rc < 0) return -1;
    return 0;
}

/* Loads one record. Succeeds only if all 3 fields were read. 0 = ok, -1 = error */
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) return -1;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return -1;

    Student tmp;
    /* %49s leaves room for '\0' so a long name cannot overflow name[50] */
    int n = fscanf(fp, "%49s %d %f", tmp.name, &tmp.age, &tmp.gpa);
    fclose(fp);
    if (n != 3) return -1;

    *out = tmp;
    return 0;
}

int main(void) {
    Student s = {0};
    Student loaded = {0};
    strcpy(s.name, "Alice");
    s.age = 21;
    s.gpa = 3.75f;

    printf("Saving student to file...\n");
    if (save_student(&s, "student.txt") != 0) {
        fprintf(stderr, "Error: could not save student.\n");
        return 1;
    }

    printf("Loading student from file...\n");
    if (load_student("student.txt", &loaded) != 0) {
        fprintf(stderr, "Error: could not load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    return 0;
}