#include <stdio.h>
#include <stdlib.h>

/* Same struct as Task 2 */
struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int n;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("\nInvalid number.\n");
        return 1;
    }

    /* Allocate an array of n Student records */
    struct Student *students = malloc((size_t)n * sizeof(struct Student));
    if (students == NULL) {
        printf("\nMemory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        /* %49s limits the name to fit name[50] (no spaces allowed) */
        if (scanf("%49s %d %f", students[i].name,
                  &students[i].id, &students[i].grade) != 3) {
            free(students);
            printf("\nInvalid input.\n");
            return 1;
        }
    }

    /* One empty line, then the table */
    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
    float total = 0.0f;
    for (int i = 0; i < n; i++) {
        printf("%-6d %-11s %.1f\n", students[i].id,
               students[i].name, students[i].grade);
        total += students[i].grade;
    }

    /* Optional bonus, printed after the required table */
    printf("Average grade = %.2f\n", total / n);

    free(students);
    return 0;
}