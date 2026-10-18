/*
 * Name: Muralikrishnan
 * Surname: Prasanth
 * Student ID: 241ADB090
 * Lab 5 - Task 3: Student management system with file persistence
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

int  load_students(Student arr[], int max);
int  save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);

/* Safe line input: strips the newline, discards overlong rest. Returns 0 on EOF. */
static int read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) return 0;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else {
        int c; /* line was longer than the buffer: drop the remainder */
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    if (len > 0 && buf[len - 1] == '\r') buf[len - 1] = '\0';
    return 1;
}

/* Loads records from students.txt. Missing/empty file -> 0. Never exceeds max. */
int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) return 0; /* first run: not an error */

    int count = 0;
    char line[256];
    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        Student tmp;
        /* sscanf fails on blank/malformed lines, which are then skipped */
        if (sscanf(line, "%49[^,],%d,%f", tmp.name, &tmp.id, &tmp.gpa) == 3) {
            arr[count++] = tmp;
        }
    }
    fclose(fp);
    return count;
}

/* Overwrites students.txt with all records. 0 = ok, -1 = error */
int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) return -1;

    int ok = 1;
    for (int i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) ok = 0;
    }
    if (fclose(fp) != 0) ok = 0;
    return ok ? 0 : -1;
}

/* Prompts for a student, validates every field, then appends it */
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name[128], id_str[64], gpa_str[64];

    printf("Enter name: ");
    int ok = read_line(name, sizeof name);
    printf("Enter ID: ");
    ok = read_line(id_str, sizeof id_str) && ok;
    printf("Enter GPA: ");
    ok = read_line(gpa_str, sizeof gpa_str) && ok;

    if (!ok || name[0] == '\0' || strchr(name, ',') != NULL || strlen(name) >= NAME_LEN) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    /* ID must be fully numeric */
    char *end;
    long id = strtol(id_str, &end, 10);
    if (id_str[0] == '\0' || *end != '\0' || id < 0 || id > 2147483647L) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    /* GPA must be fully numeric and within 0.0 - 4.0 (also rejects NaN) */
    double gpa = strtod(gpa_str, &end);
    if (gpa_str[0] == '\0' || *end != '\0' || !(gpa >= 0.0 && gpa <= 4.0)) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id;
    arr[*count].gpa = (float)gpa;
    (*count)++;
    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    char line[64];
    for (;;) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        /* End of input behaves like option 3 */
        if (!read_line(line, sizeof line) || strcmp(line, "3") == 0) {
            break;
        }
        if (strcmp(line, "1") == 0) {
            list_students(students, count);
        } else if (strcmp(line, "2") == 0) {
            add_student(students, &count);
        } else {
            printf("Invalid option.\n");
        }
    }

    if (save_students(students, count) != 0) {
        fprintf(stderr, "Error: could not save data.\n");
        return 1;
    }
    printf("Data saved. Goodbye!\n");
    return 0;
}