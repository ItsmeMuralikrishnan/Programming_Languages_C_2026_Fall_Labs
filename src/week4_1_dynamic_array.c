#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;

    printf("Enter number of elements: ");
    /* Reject non-numeric, zero or negative sizes */
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("\nInvalid size.\n");
        return 1;
    }

    /* Allocate n integers; always check for NULL */
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        printf("\nMemory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            /* Free before exiting to avoid a leak */
            free(arr);
            printf("\nInvalid input.\n");
            return 1;
        }
        sum += arr[i];
    }

    /* Cast to double so the average is not truncated */
    double average = (double)sum / n;

    printf("Sum = %lld\n", sum);
    printf("Average = %.2f\n", average);

    free(arr);
    return 0;
}